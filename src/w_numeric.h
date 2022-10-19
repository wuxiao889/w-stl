#ifndef __W_NUMERIC_H
#define __H_NUMERIC_H

#include "w_type_traits.h"
#include "w_iterator.h"
#include "w_algobase.h"

namespace wxx
{

template <typename _InputIter, typename _Tp>
_Tp accumulate(_InputIter __first, _InputIter __last, _Tp __init){
  for( ; __first != __last; ++__first)
    __init = __init + *__first;
  return __init;
}

template <typename _InputIter, typename _Tp, typename _BinaryOperation>
_Tp accumulate(_InputIter __first, _InputIter __last, _Tp __init, _BinaryOperation __binary_op){
  for( ; __first != __last; ++__first)
    __init = __binary_op(__init, *__first);
  return __init;
}


template <typename _InputIter, typename _OutputIter, typename _Tp>
_OutputIter __partial_sum(_InputIter __first, _InputIter __last, _OutputIter __result, _Tp*){
  _Tp __tmp = *__first;
  while(++__first != __last){
    __tmp = __tmp + *__first;
    *++__result = __tmp;
  }
  return ++__result;
}

template <typename _InputIter, typename _OutputIter>
_OutputIter partial_sum(_InputIter __first, _InputIter __last, _OutputIter __result){
  if(__first == __last)
    return __result;
  *__result = *__first;
  return __partial_sum(__first, __last, __result, value_type(__result));
}

template <typename _InputIter, typename _OutputIter, typename _Tp, typename _BinaryOperation>
_OutputIter __partial_sum(_InputIter __first, _InputIter __last, _OutputIter __result, _Tp*, _BinaryOperation __binary_op){
  _Tp __tmp = *__first;
  while(++__first != __last){
    __tmp = __binary_op(__tmp, *__first);
    *++__result = __tmp;
  }
  return ++__result;
}

template <typename _InputIter, typename _OutputIter, typename _BinaryOperation>
_OutputIter partial_sum(_InputIter __first, _InputIter __last, _OutputIter __result, _BinaryOperation __binary_op){
  if(__first == __last)
    return __result;
  *__result = *__first;
  return __partial_sum(__first, __last, __result, value_type(__result), __binary_op);
}

template <typename _InputIter, typename _OutputIter, typename _Tp>
_OutputIter __adjacent_difference(_InputIter __first, _InputIter __last, _OutputIter __result, _Tp*){
  _Tp __pre = *__first;
  while(++__first != __last){
    _Tp __cur = *__first;
    *++__result = __cur - __pre;
    __pre = __cur;
  }
  return ++__result;
}

template <typename _InputIter, typename _OutputIter>
_OutputIter adjacent_difference(_InputIter __first, _InputIter __last, _OutputIter __result){
  if(__first == __last)
    return __result;
  *__result = *__first;
  return __adjacent_difference(__first, __last, __result, value_type(__result));
}

template <typename _InputIter, typename _OutputIter, typename _Tp, typename _BinaryOperation>
_OutputIter __adjacent_difference(_InputIter __first, _InputIter __last, _OutputIter __result, _Tp*, _BinaryOperation __binary_op){
  _Tp __pre = *__first;
  while(++__first != __last){
    _Tp __cur = *__first;
    *++__result = __binary_op(__cur,__pre);
    __pre = __cur;
  }
  return ++__result;
}

template <typename _InputIter, typename _OutputIter, typename _BinaryOperation>
_OutputIter adjacent_difference(_InputIter __first, _InputIter __last, _OutputIter __result, _BinaryOperation __binary_op){
  if(__first == __last)
    return __result;
  *__result = *__first;
  return __adjacent_difference(__first, __last, __result, value_type(__result), __binary_op);
}

template <typename _InputIter, typename _Tp>
void itoa(_InputIter __first, _InputIter __last, _Tp __init){
  while(__first != __last)
    *__first++ = __init++;
}




}
#endif // !__W_NUMERIC_H