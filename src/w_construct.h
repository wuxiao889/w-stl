#ifndef __W_CONSTRUCT_H
#define __W_CONSTRUCT_H

#include <new>

#include "w_iterator.h"
#include "w_type_traits.h"

namespace wxx {

template <typename _T1, typename _T2>
inline void construct(_T1* __p, const _T2& __value) {
  _Construct(__p, __value);
}

template <typename _T1, typename _T2>
inline void _Construct(_T1* __p, const _T2& __value) {
  // 用定位new构造
  new ((void*)__p) _T1(__value);
}

template <typename _T1>
inline void construct(_T1* __p) {
  _Construct(__p);
}

template <typename _T1>
inline void _Construct(_T1* __p) {
  new ((void*)__p) _T1();
}

template <typename _T1>
inline void destroy(_T1* __p) {
  _Destroy(__p);
}

template <typename _Tp>
inline void _Destroy(_Tp* __pointer) {
  __pointer->~_Tp();
}

template <typename _ForwardIterator>
void __destroy_aux(_ForwardIterator , _ForwardIterator , __true_type) {}

template <typename _ForwardIterator>
void __destroy_aux(_ForwardIterator __first, _ForwardIterator __last, __false_type) {
  for (; __first != __last; ++__first) {
    destroy(&*__first);
  }
}

template <typename _ForwardIterator, typename _Tp>
void __destroy(_ForwardIterator __first, _ForwardIterator __last, _Tp*) {
  typedef typename __type_traits<_Tp>::has_trivial_destructor _Trivial_destructor;
  __destroy_aux(__first, __last, _Trivial_destructor());
}

template <typename _ForwardIterator>
inline void _Destroy(_ForwardIterator __first, _ForwardIterator __last) {
  __destroy(__first, __last, value_type(__first));
}

template <typename _ForwardIterator>
inline void destroy(_ForwardIterator __first, _ForwardIterator __last) {
  _Destroy(__first, __last);
}

// 内建类型指针，什么也不要做
#define _W_HAS_TRIVIAL_DESTRUCTOR(T) \
  inline void _Destroy(T*, T*) {}

_W_HAS_TRIVIAL_DESTRUCTOR(char) 

_W_HAS_TRIVIAL_DESTRUCTOR(int) 

_W_HAS_TRIVIAL_DESTRUCTOR(long) 

_W_HAS_TRIVIAL_DESTRUCTOR(float)

_W_HAS_TRIVIAL_DESTRUCTOR(double) 

}  // namespace wxx

#endif  // !__W_CONSTRUCT_H
