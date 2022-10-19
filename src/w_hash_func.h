#ifndef __W_HASH_FUNC_H
#define __W_HASH_FUNC_H

#include <stddef.h>

namespace wxx {

template <typename _Key>
struct hash {};

inline size_t __hash_string(const char* __s) {
  unsigned long __h = 0;
  for (; *__s; ++__s) __h = 5 * __h + *__s;
  return __h;
}

template <>
struct hash<char*> {
  size_t operator()(const char* __s) const { return __hash_string(__s); }
};

template <>
struct hash<const char*> {
  size_t operator()(const char* __s) const { return __hash_string(__s); }
};

#define __W_TIRVIAL_HASH__(_Tp)                     \
  template<>                                        \
  struct hash<_Tp>{                                 \
    size_t operator()(_Tp __x) const {return __x;}  \
  };

__W_TIRVIAL_HASH__(char)

__W_TIRVIAL_HASH__(unsigned char)

__W_TIRVIAL_HASH__(signed char)

__W_TIRVIAL_HASH__(short)

__W_TIRVIAL_HASH__(int)

__W_TIRVIAL_HASH__(unsigned int)

__W_TIRVIAL_HASH__(long)

__W_TIRVIAL_HASH__(unsigned long)

}  // namespace wxx
#endif  // !__W_HASH_FUNC_H