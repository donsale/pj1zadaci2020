#pragma once
#include <compare>

#include "IPrintable.h"

namespace zadatak3 {
class IComparable : virtual public IPrintable {
  friend std::partial_ordering operator<=>(const IComparable&,
                                           const IComparable&);

 public:
  virtual ~IComparable() {}

 protected:
  virtual std::partial_ordering compareTo(const IComparable&) const = 0;
};
}  // namespace zadatak3
