#pragma once
#include <algorithm>
#include <vector>

#include "VectorN.h"

namespace zadatak2 {
class VectorSetN {
  friend std::ostream& operator<<(std::ostream&, const VectorSetN&);

 public:
  VectorSetN(size_t capacity, int dimension);
  VectorSetN(int dimension, const std::initializer_list<VectorN>&);
  ~VectorSetN();

  VectorSetN(const VectorSetN&);
  VectorSetN(VectorSetN&&) noexcept;

  VectorSetN& operator=(const VectorSetN&);
  VectorSetN& operator=(VectorSetN&&) noexcept;

  VectorSetN& operator+=(const VectorN&);
  VectorSetN& operator-=(const VectorN&);

  bool operator==(const VectorSetN&) const;

  size_t getSize() const;
  VectorN* getArray() const;
  VectorSetN filter(const std::function<bool(const VectorN&)>&) const;
  VectorSetN map(const std::function<VectorN(const VectorN&)>&) const;

  bool isLinearlyIndependent() const;

 private:
  VectorN* arr;
  unsigned int dimension;
  size_t capacity;
  size_t currentSize;

  bool contains(const VectorN&) const;
  size_t rankOfMatrix() const;

  void move(VectorSetN&&);
  void copy(const VectorSetN&);
  void dispose();
};
}  // namespace zadatak2