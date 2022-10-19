#include "w_alloc.h"
#include <iostream>

int main(){
  wxx::simple_alloc<int,wxx::alloc> myalloc;
  int * p =  myalloc.allocate();
  myalloc.deallocate(p);
}