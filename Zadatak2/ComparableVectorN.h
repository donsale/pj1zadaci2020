#pragma once

#include <cmath>
#include <compare>
#include <functional>

#include "VectorN.h"

namespace zadatak2 {
class ComparableVectorN {
 public:
  ComparableVectorN();
  ComparableVectorN(const VectorN &);
  ComparableVectorN(const VectorN &, double (*norm)(const VectorN &));
  bool operator==(const ComparableVectorN &) const = default;
  std::partial_ordering operator<=>(const ComparableVectorN &) const;

  operator VectorN() const;
  static double EuclideanDistance(const VectorN &);

 private:
  double (*norm)(const VectorN &);
  VectorN vec;
};
}  // namespace zadatak2