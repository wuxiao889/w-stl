#include "w_alloc.h"
#include "w_uninitialized.h"
#include "mstring.h"

using namespace wxx;

template <typename _ForwardIter>
void show_and_destroy(_ForwardIter __first, int n){
  _ForwardIter __cur = __first;
  int cnt = n;
  for(; cnt > 0 ; --cnt , ++__cur){
    std::cout << *__cur << " ";
  }
  std::cout << std::endl;
  destroy(__first, __first + n);
}

void case_copy_false(){
  String strs[5] = {"hello " , "world ", "nihao " , "conijiwa " , "abdc "};
  simple_alloc<String,alloc> alloc1;
  String* __s =  alloc1.allocate(5);

  uninitialized_copy(&strs[0],&strs[5],__s);
  show_and_destroy(&__s[0],5);
  alloc1.deallocate(__s,5);
}

void case_copy_true(){
  int nums[5] = {1,2,3,4,5};
  simple_alloc<int,alloc> alloc2;
  int *pn = alloc2.allocate(5);

  uninitialized_copy(&nums[0],&nums[5],pn);
  show_and_destroy(pn,5);
  alloc2.deallocate(pn,5);
}

void case_fill_true(){
  simple_alloc<int,alloc> allocer;
  int* pn = allocer.allocate(5);

  uninitialized_fill(pn,pn+5,4);
  show_and_destroy(pn,5);

  uninitialized_fill_n(pn,5,10);
  show_and_destroy(pn,5);
  allocer.deallocate(pn,5);
}

void case_fill_false(){
  simple_alloc<String,alloc> allocer;
  String* ps =  allocer.allocate(5);

  uninitialized_fill(ps, ps+5, String("nihao"));
  show_and_destroy(ps,5);

  uninitialized_fill_n(ps, 5, String("hello"));
  show_and_destroy(ps,5);
  allocer.deallocate(ps,5);
}

int main(){
  case_copy_false();
  case_copy_true();
  case_fill_true();
  case_fill_false();
}