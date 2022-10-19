#include "w_pair.h"

#include <bits/stl_pair.h>

#include <iostream>

int main() {
  using namespace wxx;
  auto p1 = make_pair(3, 1);
  auto p2 = make_pair(2, 1);
  std::cout << (p1 < p2) << std::endl;
  return 0;
}