#ifndef __W_ALGOBASE_H
#define __W_ALGOBASE_H

#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <new>

#include "w_iterator.h"
#include "w_type_traits.h"
#include "w_pair.h"

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
__copy(_InputIter __first, _OutputIter __last, _OutputIter __result,
       input_iterator_tag, _Distance*){
  for( ; __first != __last; ++__result, ++__first){
    *__result = *__first;
  }
  return __result;
}

template <typename _RandomAccessIter, typename _OutputIter, typename _Distance>
inline _OutputIter 
__copy(_RandomAccessIter __first, _RandomAccessIter __last, _OutputIter __result,
       random_access_iterator_tag, _Distance*){
  for(_Distance __n = __last - __first; __n > 0; --__n){
    *__result = *__first;
    ++__first;
    ++__result;
  }
  return __result;
}

template <typename _Tp>
inline _Tp*
__copy_trivial(const _Tp* __first, const _Tp* __last,
               _Tp* __result){
  memmove(__result, __first, sizeof(_Tp) * (__last - __first));
  return __result + (__last - __first);
}

template <typename _InputIter, typename _OutputIter>
inline _OutputIter 
copy(_InputIter __first, _InputIter __last,
     _OutputIter __result){
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

template <typename _BidirectionalIter1, typename _BidirectionalIter2, typename _Distance>
inline _BidirectionalIter2
__copy_backward(_BidirectionalIter1 __first, _BidirectionalIter1 __last, 
                _BidirectionalIter2 __result, bidirectional_iterator_tag, _Distance*){
  while(__first != __last)
    *--__result = *--__last;
  return __result;
}

template <typename _RandomAccessIter, typename _BidirectionalIter, typename _Distance>
inline _BidirectionalIter
__copy_backward(_RandomAccessIter __first, _RandomAccessIter __last, 
                _BidirectionalIter __result, random_access_iterator_tag, _Distance*){
  for(_Distance __n = __last - __first; __n > 0; --__n)
    *--__result = *--__last;
  return __result;
}

template <typename _BidirectionalIter1, typename _BidirectionalIter2>
inline _BidirectionalIter2
copy_backward(_BidirectionalIter1 __first, _BidirectionalIter1 __last, _BidirectionalIter2 __result){
  return __copy_backward(__first, __last, __result, iterator_category(__first), distance_type(__first));
}

template <typename _ForwardIter, typename _Tp>
void fill(_ForwardIter __first, _ForwardIter __last, const _Tp& __value){
  for( ; __first != __last; ++__first)
    *__first = __value;
}

template <typename _OutputIter, typename _Size, typename _Tp>
_OutputIter fill_n(_OutputIter __first, _Size __n, const _Tp& __value){
  for( ; __n > 0; --__n, ++__first)
    *__first = __value;
  return __first;
}

inline void fill(signed char* __first, signed char* __last, const signed char& __c){
  signed char __tmp = __c;
  memset(__first, static_cast<unsigned char>(__tmp), __last - __first);
}

inline void fill(char* __first, char* __last, const char& __c){
  char __tmp = __c;
  memset(__first, __tmp, __last - __first);
}

template <class _Size>
inline char* fille_n(char* __first, _Size __n, const char& __c){
  fill(__first, __first + __n, __c);
  return __first + __n;
}

template <class _Size>
inline char* fille_n(signed char* __first, _Size __n, const signed char& __c){
  fill(__first, __first + __n, __c);
  return __first + __n;
}

template <typename _InputIter1, typename _InputIter2>
pair<_InputIter1, _InputIter2> 
mismatch(_InputIter1 __first1, _InputIter1 __last1, _InputIter2 __first2){
  while( __first1 != __last1 && *__first1 == *__first2 ){
    ++__first1;
    ++__first2;
  }
  return make_pair(__first1,__first2);
}

template <typename _InputIter1, typename _InputIter2>
inline bool 
equal(_InputIter1 __first1, _InputIter1 __last1, _InputIter2 __first2){
  for( ; __first1 != __last1 ; ++__first1, ++__first2)
    if(*__first1 != *__first2)
      return false;
  return true;
}

// template <typename _InputIter1, typename _InputIter2, typename _BinaryPredicate>
// inline bool equal(_InputIter1 __first1, _InputIter1 __last1,
//                   _InputIter2 __first2, _BinaryPredicate __binary_pred){
  
// }

template <typename _InputIter1, typename _InputIter2>
bool lexicographical_compare(_InputIter1 __first1, _InputIter1 __last1,
                             _InputIter2 __first2, _InputIter2 __last2){
  for( ; __first1 != __last1 && __first2 != __last2
       ; ++__first1, ++__first2){
    if(*__first1 < *__first2)
      return true;
    if(*__first1 > *__first2)
      return false;
  }
  return __first1 == __last1 && __first2 != __last2;
}

template <typename _InputIter1, typename _InputIter2, typename _Comp>
bool lexicographical_compare(_InputIter1 __first1, _InputIter1 __last1,
                             _InputIter2 __first2, _InputIter2 __last2,
                             _Comp __comp){
  for( ; __first1 != __last1 && __first2 != __last2
       ; ++__first1, ++__first2){
    if(__comp(*__first1,*__first2))
      return true;
    if(__comp(*__first2,*__first1))
      return false;
  }
  return __first1 == __last1 && __first2 != __last2;
}





}  // namespace wxx
#endif  // !__W_ALGOBASE_H
