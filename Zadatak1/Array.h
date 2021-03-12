#pragma once

#include <initializer_list>

namespace zadatak1 {

class Array {
 public:
  explicit Array(int n);
  Array(int n, const std::initializer_list<int>& values);
  ~Array();

  Array(const Array& other);
  Array(Array&& other);

  int getSize() const;
  int CompareTo(const Array& a) const;
  unsigned char& getElementAt(int index, int& error);
  const unsigned char& getElementAt(int index, int& error) const;

  enum ErrorCode { OK, OUT_OF_BOUNDS };

  Array& operator=(const Array&) = delete;
  Array& operator=(Array&&) = delete;

 private:
  int n;
  unsigned char* arr;
  unsigned char& GetElement(int index, int& errorCode) const;
};
}  // namespace zadatak1
