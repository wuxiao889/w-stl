#include "w_vector.h"
#include "mstring.h"
#include "w_util.h"

int main(){
  wxx::vector<int> t(10);
  showContainer(t);

  wxx::vector<int> t1(10,5);
  showContainer(t1);

  auto v3(t1);
  showContainer(v3);

  wxx::vector<int> v4(t1.begin()+4,t1.end());
  showContainer(v4);

  wxx::vector<double> v5;
  std::cout << v5.capacity() << std::endl;
  v5.reserve(50);
  std::cout << v5.capacity() << std::endl;

  wxx::vector<wxx::String> vs;
  vs.reserve(3);
  vs.push_back(wxx::String("slj"));
  vs.push_back("nihao");
  showContainer(vs);

  wxx::vector<wxx::String> vs2(10,"hello");
  showContainer(vs2);

  vs = vs2;
  showContainer(vs);

  wxx::vector<wxx::String> vs3;
  vs3.pop_back();
  vs3.insert(vs3.begin(),"lskjl");
}