#ifndef __W_ALLOC_H
#define __W_ALLOC_H

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

#define __THROW_BAD_ALLOC                    \
  std::cerr << "out of memory" << std::endl; \
  exit(1)

namespace wxx {

template <typename T, typename Alloc>
class simple_alloc {
 public:
  static T* allocate(size_t n) {
    return 0 == n ? 0 : (T*)(Alloc::allocate(n * sizeof(T)));
  }
  static T* allocate(void) { return (T*)(Alloc::allocate(sizeof(T))); }
  static void deallocate(T* p, size_t n) {
    if (0 != n) Alloc::deallocate(p, n * sizeof(T));
  }
  static void deallocate(T* p) { Alloc::deallocate(p, sizeof(T)); }
};

using __malloc_alloc_oom_handler_func = void (*)();

template <int __inst>
class __malloc_alloc_template {
 private:
  static void* _S_oom_malloc(size_t);
  static void* _S_oom_realloc(void*, size_t);
  static __malloc_alloc_oom_handler_func __malloc_alloc_oom_handler;

 public:
  static void* allocate(size_t n) {
    void* result = malloc(n);
    if (nullptr == result) result = _S_oom_malloc(n);
    return result;
  }

  static void deallocate(void* p, size_t) { free(p); }

  static void* reallocate(void* p, size_t /* old_sz */, size_t new_sz) {
    void* result = realloc(p, new_sz);
    if (nullptr == result) result = _S_oom_realloc(p, new_sz);
    return result;
  }

  // __set_malloc_handler 参数是 void (*__f)()
  // 返回值 void(*)()
  // static void (* __set_malloc_handler(void (*__f)()))()
  static __malloc_alloc_oom_handler_func __set_malloc_handler(
      __malloc_alloc_oom_handler_func f) {
    __malloc_alloc_oom_handler_func old = __malloc_alloc_oom_handler;
    __malloc_alloc_oom_handler = f;
    return old;
  }
};

template <int __inst>
__malloc_alloc_oom_handler_func __malloc_alloc_template<__inst>::__malloc_alloc_oom_handler = nullptr;

template <int __inst>
void* __malloc_alloc_template<__inst>::_S_oom_malloc(size_t n) {
  __malloc_alloc_oom_handler_func my_malloc_handler;
  void* result;
  for (;;) {
    my_malloc_handler = __malloc_alloc_oom_handler;
    if (nullptr == my_malloc_handler) {
      __THROW_BAD_ALLOC;
    }
    (*my_malloc_handler)();
    result = malloc(n);
    if (result) return result;
  }
}

template <int __inst>
void* __malloc_alloc_template<__inst>::_S_oom_realloc(void* p, size_t n) {
  __malloc_alloc_oom_handler_func my_malloc_handler;
  void* result;
  for (;;) {
    my_malloc_handler = __malloc_alloc_oom_handler;
    if (nullptr == my_malloc_handler) {
      __THROW_BAD_ALLOC;
    }
    (*my_malloc_handler)();
    result = realloc(p, n);
    if (result) return result;
  }
}

typedef __malloc_alloc_template<0> malloc_alloc;

#ifdef __USE_MALLOC
typedef malloc_alloc alloc;
// typedef malloc_alloc single_client_alloc;
#endif

static const int _ALIGN = 8;
static const int _MAX_BYTES = 128;
static const int _NFREELISTS = 16;

template <bool __threads, int __inst>
class __default_alloc_template {
  
  union _Obj {
    union _Obj* _M_free_list_link;
    char _M_client_data[1];
  };

  static size_t _S_round_up(size_t __byte) {
    return (__byte + (size_t)_ALIGN - 1) & ~((size_t)_ALIGN - 1);
  }

  static size_t _S_freelist_index(size_t __byte) {
    return ((__byte + (size_t)_ALIGN - 1) / (size_t)_ALIGN - 1);
  }

  static void* _S_refill(size_t __n);

  static char* _S_chunk_alloc(size_t __size, int& __nobjs);

  static char* _S_start_free;
  static char* _S_end_free;
  static size_t _S_heap_size;
  static _Obj* volatile _S_free_list[];

 public:
  static void* allocate(size_t __n) {
    void* __ret = 0;
    if (__n > (size_t)_MAX_BYTES) {
      __ret = malloc_alloc::allocate(__n);
    } else {
      _Obj* volatile* __my_free_list = _S_free_list + _S_freelist_index(__n);
      _Obj* __result = *__my_free_list;
      if (__result == nullptr)
        __ret = _S_refill(_S_round_up(__n));
      else {
        *__my_free_list = __result->_M_free_list_link;
        __ret = __result;
      }
    }
    return __ret;
  }

  static void deallocate(void* __p, size_t __n) {
    if (__n > (size_t)_MAX_BYTES)
      malloc_alloc::deallocate(__p, __n);
    else {
      _Obj* volatile* __my_free_list = _S_free_list + _S_freelist_index(__n);
      _Obj* __q = (_Obj*)__p;
      __q->_M_free_list_link = *__my_free_list;
      *__my_free_list = (_Obj*)__p;
    }
  }

  static void* reallocate(void* __p, size_t __old_sz, size_t __new_sz) {
    void* __result;
    size_t __copy_sz;
    if (__old_sz > (size_t)_MAX_BYTES && __new_sz > (size_t)_MAX_BYTES) {
      return realloc(__p, __new_sz);
    }
    if (_S_round_up(__old_sz) == _S_round_up(__new_sz)) return __p;
    __result = allocate(__new_sz);
    __copy_sz = __new_sz > __old_sz ? __old_sz : __new_sz;
    memcpy(__result, __p, __copy_sz);
    deallocate(__p, __old_sz);
    return __result;
  }
};

#ifndef __USE_MALLOC
typedef __default_alloc_template<true, 0> alloc;
#endif  // !__USE_MALLOC

template <bool __threads, int __inst>
inline bool operator==(const __default_alloc_template<__threads, __inst>&,
                       const __default_alloc_template<__threads, __inst>&) {
  return true;
}

template <bool __threads, int __inst>
char* __default_alloc_template<__threads, __inst>::_S_chunk_alloc(
    size_t __size, int& __nobjs) {
  char* __result;
  size_t __total_bytes = __size * __nobjs;
  size_t __bytes_left = _S_end_free - _S_start_free;

  if (__bytes_left > __total_bytes) {
// 剩余区块足够20个__size
#ifdef WDEBUG
    std::cout << "__bytes_left > __total_bytes "
              << " __size: " << __size << " __bytes_left: " << __bytes_left
              << " __total_bytes: " << __total_bytes << std::endl;
#endif  // DEBUG
    __result = _S_start_free;
    _S_start_free += __total_bytes;
    return __result;
  } else if (__bytes_left >= __size) {
// 剩余不够20但能容纳至少一个，将内存池剩余区块尽可能分配出去
#ifdef WDEBUG
    std::cout << "__bytes_left >= __size "
              << " __size: " << __size << " __bytes_left: " << __bytes_left
              << " __total_bytes: " << __total_bytes << std::endl;
#endif  // DEBUG
    __nobjs = (int)(__bytes_left / __size);
    __total_bytes = __size * __nobjs;
    __result = _S_start_free;
    _S_start_free += __total_bytes;
    return __result;
  } else {
#ifdef WDEBUG
    std::cout << "__bytes_left < __size" << std::endl;
#endif  // DEBUG
    // 内存池剩余大小一个size也不够
    size_t __bytes_to_get = 2 * __total_bytes + _S_round_up(_S_heap_size >> 4);
    if (__bytes_left > 0) {
      _Obj* volatile* __my_free_list = _S_free_list + _S_round_up(__bytes_left);
      ((_Obj*)_S_start_free)->_M_free_list_link = *__my_free_list;
      *__my_free_list = (_Obj*)_S_start_free;
    }
    _S_start_free = (char*)(malloc(__bytes_to_get));
    if (_S_start_free == nullptr) {
      size_t __i;
      _Obj* volatile* __my_free_list;
      _Obj* __p;
      for (__i = __size; __i <= (size_t)_MAX_BYTES; __i += (size_t)_ALIGN) {
        __my_free_list = _S_free_list + _S_freelist_index(__i);
        __p = *__my_free_list;
        if (__p != nullptr) {
          *__my_free_list = __p->_M_free_list_link;
          _S_start_free = (char*)(__p);
          _S_end_free = _S_start_free + __i;
          return _S_chunk_alloc(__size, __nobjs);
        }
      }
      _S_end_free = nullptr;
      _S_start_free = (char*)(malloc_alloc::allocate(__bytes_to_get));
    }
    _S_heap_size += __bytes_to_get;
    _S_end_free = _S_start_free + __bytes_to_get;
    return _S_chunk_alloc(__size, __nobjs);
  }
}

template <bool __threads, int __inst>
void* __default_alloc_template<__threads, __inst>::_S_refill(size_t __n) {
  int __nobjs = 20;
  char* __chunk = _S_chunk_alloc(__n, __nobjs);
  _Obj* volatile* __my_free_list;
  _Obj* __result;
  _Obj* __current_obj;
  _Obj* __next_obj;
  int __i;

  if (__nobjs == 1) return __chunk;
  __my_free_list = _S_free_list + _S_freelist_index(__n);
  // 不同类型指针之间转换不能用static_cast ,
  // 如果清除自己在做什么应该用 reinterptre_cast
  __result = (_Obj*)(__chunk);
  *__my_free_list = __next_obj = (_Obj*)(__chunk + __n);

  for (__i = 1; ; __i++) {
    __current_obj = __next_obj;
    __next_obj = (_Obj*)((char*)__next_obj + __n);
    if (__nobjs - 1 == __i) {
      __current_obj->_M_free_list_link = nullptr;
      break;
    } else {
      __current_obj->_M_free_list_link = __next_obj;
    }
  }
  return __result;
}

template <bool __threads, int __inst>
char* __default_alloc_template<__threads, __inst>::_S_start_free = nullptr;

template <bool __threads, int __inst>
char* __default_alloc_template<__threads, __inst>::_S_end_free = nullptr;

template <bool __threads, int __inst>
size_t __default_alloc_template<__threads, __inst>::_S_heap_size = 0;

template <bool __threads, int __inst>
typename __default_alloc_template<__threads, __inst>::
_Obj* volatile __default_alloc_template<__threads, __inst>::_S_free_list[_NFREELISTS] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

}  // namespace wxx
#endif  // !__W_ALLOC_H
