#ifndef __W_TYPE_TRAITS__
#define __W_TYPE_TRAITS__

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
#define __wxx_has_true_type_traits(T)  \
template <>                             \
struct __type_traits<T>                 \
{                                       \
  typedef __true_type has_trivial_default_constructor; \
  typedef __true_type has_trivial_copy_constructor;    \
  typedef __true_type has_trivial_assignment_constructor;  \
  typedef __true_type has_trivial_destructor;  \
  typedef __true_type is_POD_type;   \
};

__wxx_has_true_type_traits(char)

__wxx_has_true_type_traits(signed char)

__wxx_has_true_type_traits(unsigned char)

__wxx_has_true_type_traits(short)

__wxx_has_true_type_traits(unsigned short)

__wxx_has_true_type_traits(int)

__wxx_has_true_type_traits(unsigned int)

__wxx_has_true_type_traits(long)

__wxx_has_true_type_traits(unsigned long)

__wxx_has_true_type_traits(float)

__wxx_has_true_type_traits(double)

template <typename T>
inline typename __type_traits<T>::is_POD_type
is_POD(const T &){
  return typename __type_traits<T>::is_POD_type();
}

} // namespace wxx

#endif // !__WXX_TYPE_TRAITS__
