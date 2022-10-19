#include "w_alloc.h"
#include "w_construct.h"
#include "mstring.h"

using namespace wxx;

int main(){
  // String s =  String("hello");
  String* p =  (String*)alloc::allocate(sizeof(String));
  // std::cout << *p << std::endl;
  construct(p,"nihao");
  std::cout << *p << std::endl;
  destroy(p);
  String* p1 = (String*)alloc::allocate(sizeof(String));
  construct(p1);
  std::cout << *p1 << std::endl;
  destroy(p1);
}