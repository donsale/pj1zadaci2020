#include "ComparableVectorN.h"

namespace zadatak2 {
ComparableVectorN::ComparableVectorN() : norm(nullptr) {}

ComparableVectorN::ComparableVectorN(const VectorN& vec)
    : ComparableVectorN(vec, ComparableVectorN::EuclideanDistance) {}

ComparableVectorN::ComparableVectorN(const VectorN& v,
                                     double (*n)(const VectorN&))
    : vec(v), norm(n) {}

std::partial_ordering ComparableVectorN::operator<=>(
    const ComparableVectorN& cvec) const {
  if (norm == cvec.norm) {
    if (norm(vec) == norm(cvec.vec)) return std::partial_ordering::equivalent;
    if (norm(vec) > norm(cvec.vec)) return std::partial_ordering::greater;
    if (norm(vec) < norm(cvec.vec)) return std::partial_ordering::less;
  }

  return std::partial_ordering::unordered;
}

ComparableVectorN::operator VectorN() const { return VectorN(vec); }

double ComparableVectorN::EuclideanDistance(const VectorN& v) {
  double sum = 0;
  for (size_t i = 0; i < v.getSize(); i++) sum += std::pow(v[i], 2);
  return std::sqrt(sum);
}
}  // namespace zadatak2