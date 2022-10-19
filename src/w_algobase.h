#ifndef __W_ALGOBASE__
#define __W_ALGOBASE__

#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <new>

#include "w_iterator.h"
#include "w_type_traits.h"

namespace wxx {

template <typename _Tp>
inline void 
swap(_Tp& __a, _Tp& __b) {
  _Tp __tmp = __a;
  __a = __b;
  __b = __tmp;
}

template <typename _Tp>
inline const _Tp& 
min(const _Tp& __a, const _Tp& __b){
  return __a < __b ? __a : __b;
}

template <typename _Tp>
inline const _Tp& 
max(const _Tp& __a, const _Tp& __b){
  return __a > __b ? __a : __b;
}

template <typename _Tp, typename _Compare>
inline const _Tp& 
min(const _Tp& __a, const _Tp& __b, _Compare __comp){
  return __comp(__a,__b) ? __a : __b; 
}

template <typename _Tp, typename _Compare>
inline const _Tp& 
max(const _Tp& __a, const _Tp& __b, _Compare __comp){
  return __comp(__a,__b) ? __b : __a; 
}

template <typename _InputIter, typename _OutputIter, typename _Distance>
inline _OutputIter 
__copy(_InputIter __first, _OutputIter __last, _OutputIter __result, input_iterator_tag, _Distance*){
  for( ; __first != __last; ++__result, ++__first){
    *__result = *__first;
  }
  return __result;
}

template <typename _RandomAccessIter, typename _OutputIter, typename _Distance>
inline _OutputIter 
__copy(_RandomAccessIter __first, _RandomAccessIter __last, _OutputIter __result, random_access_iterator_tag, _Distance*){
  for(_Distance __n = __last - __first; __n > 0; --__n){
    *__result = *__first;
    ++__first;
    ++__result;
  }
  return __result;
}

template <typename _Tp>
inline _Tp*
__copy_trivial(const _Tp* __first, const _Tp* __last, _Tp* __result){
  memmove(__result, __first, sizeof(_Tp) * (__last - __first));
  return __result + (__last - __first);
}

template <typename _InputIter, typename _OutputIter>
inline _OutputIter 
copy(_InputIter __first, _InputIter __last, _OutputIter __result){
  return __copy(__first, __last, __result, iterator_category(__first), distance_type(__first));
}

#define __W_DECLARE_COPY_TRIVIAL(_Tp)                                       \
  inline _Tp*                                                               \
  __copy_trivial(const _Tp* __first, const _Tp* __last, _Tp* __result){     \
  memmove(__result, __first, sizeof(_Tp) * (__last - __first));             \
  return __result + (__last - __first);                                     \
}

__W_DECLARE_COPY_TRIVIAL(char)
__W_DECLARE_COPY_TRIVIAL(unsigned char)
__W_DECLARE_COPY_TRIVIAL(signed char)
__W_DECLARE_COPY_TRIVIAL(short)
__W_DECLARE_COPY_TRIVIAL(unsigned short)
__W_DECLARE_COPY_TRIVIAL(int)
__W_DECLARE_COPY_TRIVIAL(unsigned int)
__W_DECLARE_COPY_TRIVIAL(long)
__W_DECLARE_COPY_TRIVIAL(unsigned long)
__W_DECLARE_COPY_TRIVIAL(float)
__W_DECLARE_COPY_TRIVIAL(double)
__W_DECLARE_COPY_TRIVIAL(long double)

template <typename _BI1, typename _BI2, typename _Distance>
inline _BI2
__copy_backward(_BI1 __first, _BI1 __last, _BI2 __result, bidirectional_iterator_tag, _Distance*){
  while(__first != __last)
    *--__result = *--__last;
  return __result;
}

template <typename _RI1, typename _RI2, typename _Distance>
inline _RI2
__copy_backward(_RI1 __first, _RI1 __last, _RI2 __result, random_access_iterator_tag, _Distance*){
  for(_Distance __n = __last - __first; __n > 0; --__n)
    *--__result = *--__last;
  return __result;
}

template <typename _BI1, typename _BI2, typename _Distance>
inline _BI2
copy_backward(_BI1 __first, _BI1 __last, _BI2 __result){
  return __copy_backward(__first, __last, __result, iterator_category(__first), _Distance(__first));
}

template <typename _FI, typename _Tp>
void fill(_FI __first, _FI __last, const _Tp& __value){
  for( ; __first != __last; ++__first)
    *__first = __value;
}

template <typename _OI, typename _Size, typename _Tp>
_OI fill_n(_OI __first, _Size __n, const _Tp& __value){
  for( ; __n > 0; --__n, ++__first)
    *__first = __value;
  return __first;
}

// inline void fill(unsigned char )

}  // namespace wxx

#endif  // !__W_ALGOBASE__
