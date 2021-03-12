#include "Array.h"

namespace zadatak1 {

Array::Array(int n) : n(n), arr(new unsigned char[n]()) {}

Array::Array(int n, const std::initializer_list<int>& values) : Array(n) {
  int i = 0;
  int e;
  for (auto value : values) {
    this->getElementAt(i++, e) = value;
  }
}

Array::~Array() {
  delete[] arr;
  arr = nullptr;
}

Array::Array(const Array& other) : Array(other.n) {
  int e;
  for (int i = 0; i < n; i++)
    this->getElementAt(i, e) = other.getElementAt(i, e);
}

Array::Array(Array&& other) : n(other.n), arr(other.arr) {
  other.arr = nullptr;
}

int Array::getSize() const { return this->n; }

// Prva cifra u nizu je najlakša
int Array::CompareTo(const Array& arr) const {
  int thisLen = this->getSize();
  int otherLen = arr.getSize();

  int len = thisLen;
  int e;

  if (thisLen > otherLen) {
    len = otherLen;
    for (int i = otherLen; i < thisLen; i++) {
      if (this->getElementAt(i, e) != 0) return 1;
    }
  } else if (thisLen < otherLen) {
    len = thisLen;
    for (int i = thisLen; i < otherLen; i++) {
      if (arr.getElementAt(i, e) != 0) return -1;
    }
  }

  for (int i = len - 1; i >= 0; i--)
    if (this->getElementAt(i, e) > arr.getElementAt(i, e))
      return 1;
    else if (this->getElementAt(i, e) < arr.getElementAt(i, e))
      return -1;

  return 0;
}

unsigned char& Array::getElementAt(int index, int& errorCode) {
  return GetElement(index, errorCode);
}

const unsigned char& Array::getElementAt(int index, int& errorCode) const {
  return GetElement(index, errorCode);
}

unsigned char& Array::GetElement(int index, int& errorCode) const {
  if (index >= 0 && index < this->n) {
    errorCode = Array::OK;
    return arr[index];
  } else {
    errorCode = Array::OUT_OF_BOUNDS;
    return arr[0];
  }
}

}  // namespace zadatak1
