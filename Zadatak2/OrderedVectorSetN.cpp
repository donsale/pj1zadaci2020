#include "OrderedVectorSetN.h"

namespace zadatak2 {

bool operator==(const OrderedVectorSetN &lhs, const VectorSetN &rhs) {
  return lhs.set == rhs;
}

bool operator==(const VectorSetN &lhs, const OrderedVectorSetN &rhs) {
  return rhs == lhs;
}

std::ostream &operator<<(std::ostream &stream, const OrderedVectorSetN &oset) {
  stream << oset.set;
  return stream;
}

OrderedVectorSetN::OrderedVectorSetN(size_t capacity, int dimension,
                                     double (*norm)(const VectorN &))
    : set(VectorSetN(capacity, dimension)), norm(norm) {}

OrderedVectorSetN::OrderedVectorSetN(
    int dimension, const std::initializer_list<ComparableVectorN> &list,
    double (*norm)(const VectorN &))
    : OrderedVectorSetN(list.size(), dimension, norm) {
  for (auto &value : list) *this += value;
}

OrderedVectorSetN &OrderedVectorSetN::operator+=(const ComparableVectorN &v) {
  set += v;
  std::sort(set.getArray(), set.getArray() + set.getSize(),
            [this](const VectorN &a, const VectorN &b) {
              return ComparableVectorN(a, norm) < ComparableVectorN(b, norm);
            });
  return *this;
}

OrderedVectorSetN &OrderedVectorSetN::operator-=(const ComparableVectorN &v) {
  set -= v;
  return *this;
}

bool OrderedVectorSetN::operator==(const OrderedVectorSetN &other) const {
  return set == other.set;
}

OrderedVectorSetN::operator VectorSetN() const { return set; }
bool OrderedVectorSetN::isLinearlyIndependent() const {
  return set.isLinearlyIndependent();
}
}  // namespace zadatak2