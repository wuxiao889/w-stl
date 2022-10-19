
#include "w_numeric.h"

#include <assert.h>

#include <algorithm>
#include <boost/type_index.hpp>
#include <iostream>
#include <numeric>
#include <vector>

#include "w_util.h"
#include "w_vector.h"

int main() {
  using namespace wxx;
  vector<int> nums(10);
  fill(nums.begin(), nums.end(), 5);
  std::cout << accumulate(nums.begin(), nums.end(), 0) << std::endl;

  // std::vector<int> nums2(nums.begin(),nums.end());
  // std::cout <<
  // boost::typeindex::type_id_with_cvr<decltype(nums2.get_allocator())>().pretty_name()
  // << std::endl; std::accumulate(nums.begin(),nums.end(),0);

  int f[5] = {1, 2, 3, 4, 5};
  vector<int> prefix(5);
  vector<int> adjacent(5);
  auto ret = partial_sum(f, f + 5, prefix.begin());
  auto ret1 = adjacent_difference(f, f + 5, adjacent.begin());
  assert(ret == prefix.end());
  assert(ret1 == adjacent.end());
  showContainer(prefix);
  showContainer(adjacent);
  partial_sum(adjacent.begin(),adjacent.end(),adjacent.begin());
  showContainer(adjacent);

  int pf[5]{};
  auto ret2 = partial_sum(prefix.begin(),prefix.end(),pf);
  assert(ret2 == pf + 5);
  for(auto i : pf) std::cout << i << " ";
  std::cout << std::endl;

  int pf1[5]{};
  itoa(pf1,pf1+5,1);
  for(auto i : pf1) std::cout << i << " ";
  std::cout << std::endl;
}