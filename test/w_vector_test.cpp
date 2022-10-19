#include "w_vector.h"
#include "mstring.h"

int main(){
  wxx::vector<int> t(10);
  for(auto i : t){
    std::cout << i << " ";
  }
  std::cout << std::endl;

  wxx::vector<int> t1(10,5);
  for(auto i : t1){
    std::cout << i << " ";
  }
  std::cout << std::endl;

  auto v3(t1);
  for(auto i : v3){
    std::cout << i << " ";
  }
  std::cout << std::endl;
  wxx::vector<int> v4(t1.begin()+4,t1.end());
  for(auto i : v4){
    std::cout << i << " ";
  }
  std::cout << std::endl;

  wxx::vector<double> v5;
  std::cout << v5.capacity() << std::endl;
  v5.reserve(50);
  std::cout << v5.capacity() << std::endl;

  wxx::vector<wxx::String> vs;
  vs.reserve(50);
  
}