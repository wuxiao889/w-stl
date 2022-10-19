#ifndef __W_FUNCTION_H
#define __W_FUNCTION_H

namespace wxx {

template <typename _Arg, typename _Result>
struct unary_function {
  typedef _Arg argument_type;
  typedef _Result result_type;
};

template <typename _Arg1, typename _Arg2, typename _Result>
struct binary_function {
  typedef _Arg1 first_argument_type;
  typedef _Arg2 second_argument_type;
  typedef _Result result_type;
};

template <typename _Tp>
struct plus : public binary_function<_Tp, _Tp, _Tp> {
  _Tp operator()(const _Tp& __x, const _Tp& __y) const { return __x + __y; }
};

template <typename _Tp>
struct minus : public binary_function<_Tp, _Tp, _Tp> {
  _Tp operator()(const _Tp& __x, const _Tp& __y) const { return __x - __y; }
};

template <typename _Tp>
struct multiplies : public binary_function<_Tp, _Tp, _Tp> {
  _Tp operator()(const _Tp& __x, const _Tp& __y) const { return __x * __y; }
};

template <typename _Tp>
struct divides : public binary_function<_Tp, _Tp, _Tp> {
  _Tp operator()(const _Tp& __x, const _Tp& __y) const { return __x / __y; }
};

template <typename _Tp>
struct modulus : public binary_function<_Tp, _Tp, _Tp> {
  _Tp operator()(const _Tp& __x, const _Tp& __y) const { return __x % __y; }
};

template <typename _Tp>
struct negate : public unary_function<_Tp, _Tp> {
  _Tp operator()(const _Tp& __x) const { return -__x; }
};

template <typename _Tp>
struct equal_to : public binary_function<_Tp, _Tp, bool> {
  bool operator()(const _Tp& __x, const _Tp& __y) const { return __x == __y; }
};

template <typename _Tp>
struct not_equal_to : public binary_function<_Tp, _Tp, bool> {
  bool operator()(const _Tp& __x, const _Tp& __y) const { return __x != __y; }
};

template <typename _Tp>
struct greater : public binary_function<_Tp, _Tp, bool> {
  bool operator()(const _Tp& __x, const _Tp& __y) const { return __x > __y; }
};

template <typename _Tp>
struct less : public binary_function<_Tp, _Tp, bool> {
  bool operator()(const _Tp& __x, const _Tp& __y) const { return __x < __y; }
};

template <class _Tp>
struct greater_equal : public binary_function<_Tp, _Tp, bool> {
  bool operator()(const _Tp& __x, const _Tp& __y) const { return __x >= __y; }
};

template <class _Tp>
struct less_equal : public binary_function<_Tp, _Tp, bool> {
  bool operator()(const _Tp& __x, const _Tp& __y) const { return __x <= __y; }
};

template <class _Tp>
struct logical_and : public binary_function<_Tp, _Tp, bool> {
  bool operator()(const _Tp& __x, const _Tp& __y) const { return __x && __y; }
};

template <class _Tp>
struct logical_or : public binary_function<_Tp, _Tp, bool> {
  bool operator()(const _Tp& __x, const _Tp& __y) const { return __x || __y; }
};

template <class _Tp>
struct logical_not : public unary_function<_Tp, bool> {
  bool operator()(const _Tp& __x) const { return !__x; }
};

template <typename _Operation>
class binder1st
    : public unary_function<typename _Operation::second_argument_type,
                            typename _Operation::result_type> {
 protected:
  _Operation op;
  typename _Operation::first_argument_type value;

 public:
  binder1st(const _Operation& __x,
            const typename _Operation::first_argument_type& __y)
      : op(__x), value(__y) {}

  typename _Operation::result_type 
  operator()(const typename _Operation::second_argument_type& __x) const {
    return op(value, __x);
  }
};

template <typename _Operation, typename _Tp>
inline binder1st<_Operation>
bind1st(const _Operation& __fn, const _Tp& __x){
  typedef typename _Operation::first_argument_type _Arg1_type;
  return binder1st<_Operation>(__fn, _Arg1_type(__x));
}

template <typename _Operation>
class binder2nd
    : public unary_function<typename _Operation::first_argument_type,
                            typename _Operation::result_type> {
 protected:
  _Operation op;
  typename _Operation::first_argument_type value;
  
 public:
  binder2nd(const _Operation& __x,
            const typename _Operation::second_argument_type& __y)
      : op(__x), value(__y) {}

  typename _Operation::result_type 
  operator()(const typename _Operation::first_argument_type& __x) const {
    return op(__x, value);
  }
};

template <typename _Operation, typename _Tp>
inline binder2nd<_Operation>
bind2nd(const _Operation& __fn, const _Tp& __x){
  typedef typename _Operation::second_argument_type _Arg2_type;
  return binder2nd<_Operation>(__fn, _Arg2_type(__x));
}


}  // namespace wxx

#endif  // !__W_FUNCTION_H