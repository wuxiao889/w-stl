#include <iostream>
#include "w_function.h"

int main(){
  using namespace wxx;
  std::cout << less<int>()(1,0) << std::endl;
  std::cout << bind1st(less<int>(),1)(0) << std::endl;
  std::cout << bind2nd(less<int>(),1)(0) << std::endl;
}