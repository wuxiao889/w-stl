#ifndef __MYSTRING_
#define __MYSTRING_

#include <cstring>
#include <iostream>

namespace wxx {

#define PF __PRETTY_FUNCTION__

class String {
 public:
  static size_t DCtor;
  static size_t Ctor;
  static size_t CCtor;
  static size_t CAsgn;
  static size_t MCtor;
  static size_t MAsgn;
  static size_t Dtor;

 private:
  char *data_;
  size_t len_;

 public:
  String(const char *cstr = 0);

  String(const String &str);

  String &operator=(const String &str);

#ifndef NOPECSTR
  String &operator=(const char *cstr);
#endif

#ifndef NMOVE
  String(String &&str) noexcept;

  String &operator=(String &&rhs) noexcept;
#endif

  ~String();

  size_t size() const;

  char &operator[](size_t i);

  const char &operator[](size_t i) const;

  const char *c_str() const { return data_; }

  static void print_cnt();
  static void clear_cnt();

};

size_t String::DCtor = 0;
size_t String::Ctor = 0;
size_t String::CCtor = 0;
size_t String::CAsgn = 0;
size_t String::MCtor = 0;
size_t String::MAsgn = 0;
size_t String::Dtor = 0;

inline String::String(const char *cstr) {
  ++Ctor;
#ifdef WDEBUG
  std::cout << PF << std::endl;
#endif
  if (cstr) {
    data_ = new char[strlen(cstr) + 1];
    strcpy(data_, cstr);
  } else {
    data_ = new char[1];
    *data_ = '\0';
  }
}

inline String::~String() {
  ++Dtor;
#ifdef WDEBUG
  std::cout << PF << std::endl;
#endif
  if (data_) {
    delete[] data_;
    data_ = nullptr;
  }
}

inline String::String(const String &str) {
  ++CCtor;
#ifdef WDEBUG
  std::cout << PF << std::endl;
#endif
  data_ = new char[strlen(str.data_) + 1];
  strcpy(data_, str.data_);
}

#ifndef NMOVE
inline String::String(String &&str) noexcept : data_(str.data_) {
  ++MCtor;
#ifdef WDEBUG
  std::cout << PF << std::endl;
#endif
  str.data_ = nullptr;  // 不安全，strlen cout 会崩溃
  // str.data_ = new char[1];
  // *str.data_ = '\0';
}

inline String &String::operator=(String &&rhs) noexcept {
  ++MAsgn;
#ifdef WDEBUG
  std::cout << PF << std::endl;
#endif
  if (&rhs != this) {
    delete[] data_;
    data_ = rhs.data_;
    rhs.data_ = nullptr;
    // rhs.data_ = new char[1];
    // *rhs.data_ = '\0';
  }
  return *this;
}
#endif

inline String &String::operator=(const String &str) {
  ++CAsgn;
#ifdef WDEBUG
  std::cout << PF << std::endl;
#endif
  if (this != &str) {
    delete[] data_;
    data_ = new char[strlen(str.data_) + 1];
    strcpy(data_, str.data_);
  }
  return *this;
}

#ifndef NOPECSTR
/*
str1 = "111";
先调用 const char* 构造临时对象
然后调用 operator=(const String&)
最后要析构临时对象
 */
inline String &String::operator=(const char *cstr) {
#ifdef WDEBUG
  std::cout << PF << std::endl;
#endif
  if (this->data_ != cstr) {
    delete[] data_;
    data_ = new char[strlen(cstr) + 1];
    strcpy(data_, cstr);
  }
  return *this;
}
#endif

inline size_t String::size() const { return strlen(data_); }

inline char &String::operator[](size_t i) {
  if (i >= size()) throw("out of range");
  return data_[i];
}

inline const char &String::operator[](size_t i) const {
  if (i >= size()) throw("out of range");
  return data_[i];
}

inline std::ostream &operator<<(std::ostream &os, const String &str) {
  os << "\"" << str.c_str() << "\"";
  return os;
}

inline String operator+(const String &lhs, const String &rhs) {
  std::cout << PF << std::endl;
  char *ptmp = new char[lhs.size() + rhs.size() + 1];
  strcpy(ptmp, lhs.c_str());
  strcat(ptmp, rhs.c_str());
  String s(ptmp);
  delete[] ptmp;
  return s;
  // String stmp;
  // stmp.~String();
  // stmp.data_ = new char[lhs.size() + rhs.size() + 1];
  // strcpy(stmp.data_, lhs.c_str());
  // strcat(stmp.data_, rhs.c_str());
  // return stmp;
}

inline bool operator<(const String &lhs, const String &rhs) {
  return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

inline bool operator> (const String& lhs, const String& rhs) { return rhs < lhs; }

inline bool operator<=(const String& lhs, const String& rhs) { return !(lhs > rhs); }

inline bool operator>=(const String& lhs, const String& rhs) { return !(lhs < rhs); }

inline bool operator==(const String &lhs, const String &rhs) {
  return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

void String::print_cnt() {
  // cout << boost::typeindex::type_id_with_cvr<T>().pretty_name() << endl;
  std::cout << "CCtor=" << CCtor << " MCtor=" << MCtor << " CAsgn=" << CAsgn
            << " MAsgn=" << MAsgn << " DCtor=" << DCtor << " Ctor=" << Ctor
            << " Dtor=" << Dtor << std::endl;
}

void String::clear_cnt() {
  CCtor = MCtor = CAsgn = MAsgn = DCtor = Ctor = Dtor = 0;
}

}  // namespace wxx

// include不要写在namespace里
#include <hash_fun.h>

namespace std {

using wxx::String;

template <>
struct hash<String> {
  size_t operator()(const String &s) const noexcept {
    return hash<string>()(string(s.c_str()));
  }
};

}  // namespace std

#endif