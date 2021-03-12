#pragma once
#include <vector>

#include "ComparableVectorN.h"
#include "VectorSetN.h"

namespace zadatak2 {

class OrderedVectorSetN {
  friend bool operator==(const OrderedVectorSetN&, const VectorSetN&);
  friend bool operator==(const VectorSetN&, const OrderedVectorSetN&);
  friend std::ostream& operator<<(std::ostream&, const OrderedVectorSetN&);

 public:
  OrderedVectorSetN(
      size_t, int,
      double (*norm)(const VectorN&) = ComparableVectorN::EuclideanDistance);
  OrderedVectorSetN(
      int, const std::initializer_list<ComparableVectorN>&,
      double (*norm)(const VectorN&) = ComparableVectorN::EuclideanDistance);

  OrderedVectorSetN& operator+=(const ComparableVectorN& v);
  OrderedVectorSetN& operator-=(const ComparableVectorN& v);

  bool operator==(const OrderedVectorSetN&) const;
  operator VectorSetN() const;
  bool isLinearlyIndependent() const;

 private:
  VectorSetN set;
  double (*norm)(const VectorN&);
};
}  // namespace zadatak2