#ifndef __W_UNINITIALIZED__
#define __W_UNINITIALIZED__

#include "w_type_traits.h"
#include "w_construct.h"
#include "w_algobase.h"
#include "w_pair.h"
#include <cstring>
#include <utility>

namespace wxx {

template <typename _InputIter, typename _ForwardIter>
inline _ForwardIter 
__uninitialized_copy_aux(_InputIter __first, _InputIter __last, _ForwardIter __result, __true_type) {
  return copy(__first, __last, __result);
}

template <typename _InputIter, typename _ForwardIter>
inline _ForwardIter 
__uninitialized_copy_aux(_InputIter __first, _InputIter __last, _ForwardIter __result, __false_type) {
  _ForwardIter __cur = __result;
  try{
    for( ; __first != __last; ++__first , ++__cur)
      _Construct(&*__cur,*__first);
    return __cur;
  }
  catch (...){
    _Destroy(__result, __cur);
    throw;
  }
}

template <typename _InputIter, typename _ForwardIter , typename _Tp>
inline _ForwardIter 
__uninitialized_copy(_InputIter __first, _InputIter __last, _ForwardIter __result, _Tp*) {
  typedef typename __type_traits<_Tp>::is_POD_type _Is_POD;
  return __uninitialized_copy_aux(__first, __last, __result, _Is_POD());
}

template <typename _InputIter, typename _ForwardIter>
inline _ForwardIter 
uninitialized_copy(_InputIter __first, _InputIter __last, _ForwardIter __result) {
  return __uninitialized_copy(__first, __last, __result, value_type(__result));
}

inline char* 
uninitialized_copy(const char* __first, const char* __last, char* __result){
  memmove(__result, __first, __last - __first);
  return __result + (__last - __first);
}

template <typename _InputIter, typename _Size, typename _ForwardIter>
pair<_InputIter,_ForwardIter>
__uninitialized_copy_n(_InputIter __first, _Size __count, _ForwardIter __restult, input_iterator_tag){
  _ForwardIter __cur = __restult;
  try{
    for( ; __count > 0; --__count, ++__first, ++__cur){
      _Construct(&*__cur,*__first);
    }
    return pair<_InputIter, _ForwardIter>(__first, __cur);
  }
  catch (...){
    _Destroy(__restult, __cur);
    throw;
  }
}

template <typename _RandomAccessIter, typename _Size, typename _ForwardIter>
inline pair<_RandomAccessIter, _ForwardIter>
__uninitialized_copy_n(_RandomAccessIter __first, _Size __count, _ForwardIter __result, random_access_iterator_tag) {
  _RandomAccessIter __last = __first + __count;
  return pair<_RandomAccessIter, _ForwardIter>(
      __last,
      uninitialized_copy(__first, __last, __result));
}

template <typename _InputIter, typename _Size, typename _ForwardIter>
inline pair<_InputIter, _ForwardIter>
uninitialized_copy_n(_InputIter __first, _Size __count, _ForwardIter __result){
  return __uninitialized_copy_n(__first, __count, __result, iterator_category(__result));
}

template <typename _ForwardIter, typename _Tp>
inline void
__uninitialized_fill_aux(_ForwardIter __first, _ForwardIter __last, const _Tp& __x, __true_type) {
  fill(__first, __last, __x);
}

template <typename _ForwardIter, typename _Tp>
inline void 
__uninitialized_fill_aux(_ForwardIter __first, _ForwardIter __last, const _Tp& __x, __false_type) {
  _ForwardIter __cur = __first;
  try{
    for( ; __cur != __last; ++__cur)
      _Construct(&*__cur, __x);
  }
  catch (...){
    _Destroy(__first, __cur);
    throw;
  }
}

template <typename _ForwardIter, typename _Tp>
inline void 
__uninitialized_fill(_ForwardIter __first, _ForwardIter __last, const _Tp& __x, _Tp*) {
  typedef typename __type_traits<_Tp>::is_POD_type _Is_POD;
  __uninitialized_fill_aux(__first, __last, __x, _Is_POD());
}

template <typename _ForwardIter, typename _Tp>
inline void 
uninitialized_fill(_ForwardIter __first, _ForwardIter __last, const _Tp& __x) {
  __uninitialized_fill(__first, __last, __x, value_type(__first));
}

template <typename _ForwardIter, typename _Size, typename _Tp>
inline _ForwardIter
__uninitialized_fill_n(_ForwardIter __first, _Size __count, const _Tp& __x , __true_type){
  return fill_n(__first, __count, __x);
}

template <typename _ForwardIter, typename _Size, typename _Tp>
inline _ForwardIter
__uninitialized_fill_n(_ForwardIter __first, _Size __count, const _Tp& __x , __false_type){
  _ForwardIter __cur = __first;
  try{
    for( ; __count > 0; --__count, ++__cur)
      _Construct(&*__cur, __x);
    return __cur;
  }catch(...){
    _Destroy(__first, __cur);
    throw;
  }
}

template <typename _ForwardIter, typename _Size, typename _Tp>
inline _ForwardIter
uninitialized_fill_n(_ForwardIter __first, _Size __count, const _Tp& __x){
  typedef typename __type_traits<_Tp>::is_POD_type _Is_POD;
  return __uninitialized_fill_n(__first, __count, __x, _Is_POD());
}

}  // namespace wxx
#endif  // !__W_UNINITIALIZED__