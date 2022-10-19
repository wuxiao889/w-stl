#include "w_iterator.h"

#include <iostream>
#include <unordered_map>
#include <vector>
#include "mstring.h"
#include "boost/type_index.hpp"
#include "w_type_traits.h"

using boost::typeindex::type_id_with_cvr;
using namespace wxx;

template <typename T>
struct MyIter : iterator<random_access_iterator_tag, T> {
  // typedef T value_type;
  // typedef T &reference;
  // typedef ptrdiff_t difference_type;
  // typedef random_access_iterator_tag iterator_category;
  // typedef T *pointer;
  MyIter(T *p = nullptr) : ptr(p), cnt_(nullptr) {
    if (p) {
      cnt_ = new int(1);
    }
  }

  MyIter(const MyIter &src) : ptr(src.ptr), cnt_(src.cnt_) {
    if (ptr) {
      ++*cnt_;
    }
  }

  MyIter &operator=(const MyIter &src) {
    if (this == &src) {
      return *this;
    }
    if (ptr) {
      --*cnt_;
      if (*cnt_ == 0) {
        delete ptr;
        delete cnt_;
      }
    }
    ptr = src.ptr;
    cnt_ = src.cnt_;
    if (ptr) {
      ++*cnt_;
    }
    return *this;
  }

  MyIter(MyIter &&src) : ptr(src.ptr), cnt_(src.cnt_) {
    src.ptr = nullptr;
    src.cnt_ = nullptr;
  }

  MyIter &operator=(MyIter &&src) {
    if (this == &src) {
      return *this;
    }
    if (ptr) {
      --*cnt_;
      if (*cnt_ == 0) {
        delete ptr;
        delete cnt_;
      }
    }
    ptr = src.ptr;
    cnt_ = src.cnt_;
    src.ptr = nullptr;
    src.cnt_ = nullptr;
    return *this;
  }

  T &operator*() const { return *ptr; }
  T *operator->() const { return ptr; }

  explicit operator bool() const { return ptr; }

  int user_cnt() const{
    return *cnt_;
  }

  ~MyIter() {
    if (ptr) {
      --*cnt_;
      if (*cnt_ == 0) {
        delete ptr;
        delete cnt_;
      }
    }
  }

 private:
  T *ptr;
  int *cnt_;
};

// 缺点是原生指针没有class
template <typename I>
typename I::value_type func(I ite) {
  return *ite;
}

template <typename I>
typename iterator_traits<I>::value_type func1(I ite) {
  typedef typename iterator_traits<I>::value_type value_type;
  std::cout << "value_type: " << type_id_with_cvr<value_type>().pretty_name()
            << std::endl;
  return *ite;
}

void iterator_category_test();

void func1_test();

void distance_test();

int main() {
  func1_test();
  iterator_category_test();
  distance_test();
}

void func1_test() {
  MyIter<int> ite(new int(8));
  MyIter<int> ite2;
  ite2 = ite;
  int *p = new int(1);
  const int *cp = p;
  std::cout << func(ite) << std::endl;
  std::cout << func1(ite) << std::endl;
  std::cout << func1(p) << std::endl;
  std::cout << func1(cp) << std::endl;
  delete p;
}

void iterator_category_test() {
  int *p = new int(1);
  const int *cp = p;
  std::cout << type_id_with_cvr<decltype(iterator_category(p))>().pretty_name()
            << std::endl;
  std::cout << type_id_with_cvr<decltype(iterator_category(cp))>().pretty_name()
            << std::endl;
  std::cout << type_id_with_cvr<decltype(iterator_category(
                   std::unordered_map<int, int>::iterator()))>()
                   .pretty_name()
            << std::endl;
  std::cout << type_id_with_cvr<decltype(iterator_category(
                   std::vector<std::string>::iterator()))>()
                   .pretty_name()
            << std::endl;
  // (__iterator_category)(std::vector<int>::iterator());
  // std::__iterator_category(std::vector<int>::iterator());
  delete p;
}

void distance_test() {
  int nums[5]{1, 2, 3, 4, 5};
  int *p = &nums[0];
  // int *p = &nums;
  std::cout << distance(nums, nums + 5) << std::endl;
  std::unordered_map<int, int> map{{1, 1}, {2, 2}};
  std::cout << type_id_with_cvr<decltype(iterator_category(map.begin()))>()
                   .pretty_name()
            << std::endl;

  // 不同命名空间的 tag 无法traits
  // std::cout << wxx::distance(map.begin(),map.end()) << std::endl;

  std::cout << std::distance(map.begin(), map.end()) << std::endl;
  std::cout << p << std::endl;
  advance(p, 2);
  std::cout << p << std::endl;

  std::cout << type_id_with_cvr<
                   __type_traits<int>::has_trivial_assignment_constructor>()
                   .pretty_name()
            << std::endl;
  std::cout << type_id_with_cvr<
                   __type_traits<double>::has_trivial_assignment_constructor>()
                   .pretty_name()
            << std::endl;
  std::cout
      << type_id_with_cvr<
             __type_traits<double *>::has_trivial_assignment_constructor>()
             .pretty_name()
      << std::endl;
  std::cout
      << type_id_with_cvr<
             __type_traits<MyIter<int>>::has_trivial_assignment_constructor>()
             .pretty_name()
      << std::endl;

  std::cout << type_id_with_cvr<decltype(is_POD(1))>().pretty_name()
            << std::endl;
            
  std::cout << type_id_with_cvr<decltype(is_POD(MyIter<int>()))>().pretty_name()
            << std::endl;

  std::cout << type_id_with_cvr<decltype(is_POD(wxx::String()))>().pretty_name()
            << std::endl;
}