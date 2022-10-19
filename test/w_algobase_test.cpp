#include "w_algobase.h"
#include <iostream>

int main(){
  using namespace wxx;
  int nums[5] = {1,2,3,4,5};
  int* p = new int[5];
  copy(&nums[0],&nums[5],p);
  for(int i = 0 ; i < 5 ; i++){
    std::cout << *(p + i) << " ";
  }
  std::cout << std::endl;
  fill_n(p,5,1);
  for(int i = 0 ; i < 5 ; i++){
    std::cout << *(p + i) << " ";
  }
  std::cout << std::endl;
  copy_backward(&nums[0],&nums[5],p+5);
  for(int i = 0 ; i < 5 ; i++){
    std::cout << *(p + i) << " ";
  }
  std::cout << std::endl;

  std::cout << min(4,5,[](int a ,int b){return a > b;}) << std::endl;
  struct MyStruct
  {
    inline bool operator()(int a ,int b){
      return a > b;
    }
  };
  std::cout << min(4,5,MyStruct()) << std::endl;

  
}