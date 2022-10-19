#ifndef __W_UTIL_H
#define __W_UTIL_H

#include <iostream>
#include "w_iterator.h"

template <typename _InputIter>
void showContainer(_InputIter __first, _InputIter __last){
  for( ; __first != __last; ++__first)
    std::cout << *__first << " ";
  std::cout << std::endl;
}

template <typename _Tp>
void showContainer(const _Tp& __container){
  typedef typename _Tp::const_iterator iterator;
  // auto __first = __container.begin();
  iterator __first = __container.begin();
  iterator __last = __container.end();
  showContainer(__first,__last);
}

#endif // !__W_UTIL_H