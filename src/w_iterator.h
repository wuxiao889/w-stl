#ifndef __W_ITERATOR__
#define __W_ITERATOR__

#include <stddef.h>

namespace wxx {

// 五种迭代器型别
struct input_iterator_tag {};
struct oupput_iterator_tag {};
struct forward_iterator_tag : input_iterator_tag {};
struct bidirectional_iterator_tag : forward_iterator_tag {};
struct random_access_iterator_tag : bidirectional_iterator_tag {};

template <typename Category, typename T, typename Distance = ptrdiff_t,
          typename Pointer = T *, typename Reference = T &>
struct iterator {
  typedef Category iterator_category;
  typedef T value_type;
  typedef Distance difference_type;
  typedef Pointer pointer;
  typedef Reference reference;
};

// 如果你希望你定义的容器能与stl水乳交融，一定要定义这五种型别，“特性萃取机”traits会忠实地将原汁原味萃取出来。
template <typename T> struct iterator_traits {
  typedef typename T::iterator_category iterator_category;
  typedef typename T::value_type value_type;
  typedef typename T::difference_type difference_type;
  typedef typename T::pointer pointer;
  typedef typename T::reference reference;
};

// 针对指针的偏特化版
// 通过 class template partial specialition 无论是原生指针，还是class-type
// iterator 都可以让 traits 提取出相应型别
template <typename T> struct iterator_traits<T *> {
  typedef T value_type;
  typedef ptrdiff_t difference_type;
  typedef T &reference_type;
  typedef T *pointer;
  typedef random_access_iterator_tag iterator_category;
};

// 上述会提取出int const而我们需要int
// const T*
// const 是顶层const, 已经有了const会忽略参数类型const
template <typename T> struct iterator_traits<const T *> {
  typedef T value_type;
  typedef ptrdiff_t difference_type;
  typedef const T &reference_type;
  typedef const T *pointer;
  typedef random_access_iterator_tag iterator_category;
};

template <class Iter>
inline constexpr typename iterator_traits<Iter>::iterator_category
iterator_category(const Iter &) {
  return typename iterator_traits<Iter>::iterator_category();
}

template <class Iter>
inline constexpr typename iterator_traits<Iter>::difference_type *
distance_type(const Iter &) {
  return static_cast<typename iterator_traits<Iter>::difference_type *>(0);
}

template <class Iter>
inline constexpr typename iterator_traits<Iter>::value_type *
value_type(const Iter &) {
  return static_cast<typename iterator_traits<Iter>::value_type *>(0);
}

template <typename InputIterator>
inline constexpr typename iterator_traits<InputIterator>::difference_type
__distance(InputIterator first, InputIterator last, input_iterator_tag) {
  typename iterator_traits<InputIterator>::difference_type n = 0;
  while (first != last) {
    ++first;
    ++n;
  }
  return n;
}

template <typename RandomAccessIterator>
inline constexpr typename iterator_traits<RandomAccessIterator>::difference_type
__distance(RandomAccessIterator first, RandomAccessIterator last,
           random_access_iterator_tag) {
  return last - first;
}

// 在编译期确定重载函数版本
template <typename InputIterator>
inline constexpr typename iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last) {
  return __distance(first, last, iterator_category(first));
}

template <typename InputIterator, typename Distance>
inline void
__advance(InputIterator &i, Distance n, input_iterator_tag) {
  while (n--)
    ++i;
}

template <typename BidirectionalIterator, typename Distance>
inline void
__advance(BidirectionalIterator &i, Distance n, bidirectional_iterator_tag) {
  if (n >= 0)
    while (n--)
      ++i;
  else
    while (n++)
      --i;
}

template <typename RandomAccessIterator, typename Distance>
inline void
__advance(RandomAccessIterator &i, Distance n, random_access_iterator_tag) {
  i += n;
}

template <typename InputIterator, typename Distance>
inline void
advance(InputIterator &i, Distance n) {
  return __advance(i, n, iterator_category(i));
}

} // namespace wxx

#endif