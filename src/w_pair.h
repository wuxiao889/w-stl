#ifndef __W_PAIR_H
#define __W_PAIR_H

namespace wxx {

template <typename _T1, typename _T2>
struct pair {
  typedef _T1 first_type;
  typedef _T2 second_type;

  first_type first;
  second_type second;

  pair() : first(_T1()), second(_T2()) {}
  pair(const _T1& __a, const _T2& __b) : first(__a), second(__b) {}
};

template <typename _T1, typename _T2>
inline bool 
operator<(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
  return __x.first < __y.first ||
         (!(__y.first < __x.first) && __x.second < __y.second);
}

template <typename _T1, typename _T2>
inline bool 
operator==(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
  return __x.first == __y.first && __x.second == __y.second;
}

template <typename _T1, typename _T2>
inline pair<_T1, _T2> 
make_pair(const _T1& __x, const _T2& __y){
  return pair<_T1, _T2>(__x, __y);
}


}  // namespace wxx
#endif  // !__W_PAIR_H
