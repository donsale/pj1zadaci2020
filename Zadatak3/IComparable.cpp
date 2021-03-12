#include "IComparable.h"

namespace zadatak3 {
std::partial_ordering operator<=>(const IComparable &obj1,
                                  const IComparable &obj2) {
  return obj1.compareTo(obj2);
}
}  // namespace zadatak3