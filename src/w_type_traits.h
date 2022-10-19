#ifndef __W_TYPE_TRAITS_H
#define __W_TYPE_TRAITS_H

namespace wxx {

struct __true_type {};
struct __false_type {};

template <typename T>
struct __type_traits
{
  typedef __true_type this_dummy_member_must_be_first;
  typedef __false_type has_trivial_default_constructor;
  typedef __false_type has_trivial_copy_constructor;
  typedef __false_type has_trivial_assignment_constructor;
  typedef __false_type has_trivial_destructor;
  typedef __false_type is_POD_type; 
};

// 对指针类的的偏特化
template <typename T>
struct __type_traits<T*>
{
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_copy_constructor;
  typedef __true_type has_trivial_assignment_constructor;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type; 
};

// 特化
#define __W_HAS_TRUE_TYPE_TRAITS(T)  \
template <>                             \
struct __type_traits<T>                 \
{                                       \
  typedef __true_type has_trivial_default_constructor; \
  typedef __true_type has_trivial_copy_constructor;    \
  typedef __true_type has_trivial_assignment_constructor;  \
  typedef __true_type has_trivial_destructor;  \
  typedef __true_type is_POD_type;   \
};

__W_HAS_TRUE_TYPE_TRAITS(char)

__W_HAS_TRUE_TYPE_TRAITS(signed char)

__W_HAS_TRUE_TYPE_TRAITS(unsigned char)

__W_HAS_TRUE_TYPE_TRAITS(short)

__W_HAS_TRUE_TYPE_TRAITS(unsigned short)

__W_HAS_TRUE_TYPE_TRAITS(int)

__W_HAS_TRUE_TYPE_TRAITS(unsigned int)

__W_HAS_TRUE_TYPE_TRAITS(long)

__W_HAS_TRUE_TYPE_TRAITS(unsigned long)

__W_HAS_TRUE_TYPE_TRAITS(float)

__W_HAS_TRUE_TYPE_TRAITS(double)

template <typename T>
inline typename __type_traits<T>::is_POD_type
is_POD(const T &){
  return typename __type_traits<T>::is_POD_type();
}


} // namespace wxx
#endif // !__WXX_TYPE_TRAITS__
