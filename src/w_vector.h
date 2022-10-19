#ifndef __W_VECTOR1__
#define __W_VECTOR1__

#include "w_alloc.h"
#include "w_uninitialized.h"
#include "w_algobase.h"

namespace wxx {

template <typename _Tp, typename _Alloc>
class _Vector_base {
 protected:
  _Tp* _M_start;
  _Tp* _M_finish;
  _Tp* _M_end_of_storage;
  typedef simple_alloc<_Tp, _Alloc> _M_data_allocator;

  _Tp* _M_allocate(size_t __n) { return _M_data_allocator::allocate(__n); }

  void _M_deallocate(_Tp* __p, size_t __n) {
    _M_data_allocator::deallocate(__p, __n);
  }

 public:
  typedef _Alloc allocator_type;
  allocator_type get_allocator() const { return allocator_type(); }

  _Vector_base(const _Alloc& = allocator_type())
      : _M_start(nullptr), _M_finish(nullptr), _M_end_of_storage(nullptr) {}

  _Vector_base(size_t __n, const _Alloc& = allocator_type())
      : _M_start(nullptr), _M_finish(nullptr), _M_end_of_storage(nullptr) {
    _M_start = _M_allocate(__n);
    _M_finish = _M_start;
    _M_end_of_storage = _M_start + __n;
  }

  ~_Vector_base() { _M_deallocate(_M_start, _M_end_of_storage - _M_start); }
};

template <typename _Tp, typename _Alloc = alloc>
class vector : protected _Vector_base<_Tp, _Alloc> {
 private:
  typedef _Vector_base<_Tp, _Alloc> _Base;

 public:
  typedef _Tp value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type* iterator;
  typedef const value_type* const_iterator;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  typedef typename _Base::allocator_type allocator_type;
  allocator_type get_allocator() const { return _Base::get_allocator(); }

 public:
  iterator begin() { return this->_M_start; }
  const_iterator begin() const { return this->_M_start; }
  iterator end() { return this->_M_finish; }
  const_iterator end() const { return this->_M_finish; }
  size_type size() const { return size_type(end() - begin()); }
  size_type capacity() const {
    return size_t(this->_M_end_of_storage - begin());
  }
  bool empty() const { return begin() == end(); }

  reference front() { return *begin();}
  const_reference front() const { return *begin();}
  reference back() { return *(end()-1);}
  const_reference back() const { return *(end()-1);}

  reference operator[](size_type __n) { return *(begin() + __n); }
  const_reference operator[](size_type __n) const { return *(begin() + __n); }

  // default ctor
  explicit vector(const allocator_type& __a = allocator_type()) : _Base(__a) {}

  explicit vector(size_type __n, const allocator_type& __a = allocator_type())
      : _Base(__n, __a) {
    this->_M_finish = uninitialized_fill_n(this->_M_start, __n, _Tp());
  }

  vector(size_type __n, const _Tp& __value,
         const allocator_type& __a = allocator_type())
      : _Base(__n, __a) {
    this->_M_finish = uninitialized_fill_n(this->_M_start, __n, __value);
  }

  vector(const vector<_Tp, _Alloc>& __src)
      : _Base(__src.size(), __src.get_allocator()) {
    this->_M_finish =
        uninitialized_copy(__src.begin(), __src.end(), this->_M_start);
  }

  vector(const _Tp* __first, const _Tp* __last,
         const allocator_type& __a = allocator_type())
      : _Base(__last - __first, __a) {
    this->_M_finish = uninitialized_copy(__first, __last, this->_M_start);
  }
  // vector 先析构对象 然后base归还内存
  ~vector() { destroy(this->_M_start, this->_M_finish); }

  vector<_Tp, _Alloc>& operator=(const vector<_Tp, _Alloc>& __x);

  /*
    Increase the capacity of the vector (the total number of elements that the vector can hold without requiring reallocation) 
    to a value that's greater or equal to new_cap. If new_cap is greater than the current capacity(), new storage is allocated, 
    otherwise the function does nothing.

    reserve() does not change the size of the vector.
    If new_cap is greater than capacity(), all iterators, including the past-the-end iterator, 
    and all references to the elements are invalidated. Otherwise, no iterators or references are invalidated.
  */
  void reserve(size_type __n) {
    if (capacity() < __n) {
      const size_type __old_size = size();
      iterator __tmp =
          _M_allocate_and_copy(__n, this->_M_start, this->_M_finish);
      destroy(this->_M_start, this->_M_finish);
      this->_M_deallocate(this->_M_start,
                          this->_M_end_of_storage - this->_M_start);
      this->_M_start = __tmp;
      this->_M_finish = __tmp + __old_size;
      this->_M_end_of_storage = this->_M_start + __n;
    }
  }

  void swap(vector<_Tp, _Alloc>& __x){
    wxx::swap(this->_M_start, __x._M_start);
    wxx::swap(this->_M_finish, __x._M_finish);
    wxx::swap(this->_M_end_of_storage, __x._M_end_of_storage);
  }

  void push_back(const _Tp& __x){
    if(this->_M_finish != this->_M_end_of_storage){
      construct(this->_M_finish, __x);
      ++this->_M_finish;
    }else{
      _M_insert_aux(end(), __x);
    }
  }



 private:
  iterator _M_allocate_and_copy(size_type __n, iterator __first, iterator __last) {
    iterator __result = this->_M_allocate(__n);
    try {
      uninitialized_copy(__first, __last, __result);
      return __result;
    } catch (...) {
      this->_M_deallocate(__result, __n);
      throw;
    }
  }

  void _M_insert_aux(iterator __pos, const _Tp& __x){
    
  }

};

}  // namespace wxx

#endif  // !__WTL_VECTOR1__