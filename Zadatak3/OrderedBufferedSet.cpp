#include "OrderedBufferedSet.h"

namespace zadatak3 {
OrderedBufferedSet::OrderedBufferedSet(size_t capacityIncrease)
    : UnorderedSet(0), OrderedSet(0), BufferedSet(capacityIncrease) {}

OrderedBufferedSet::OrderedBufferedSet(
    size_t capacityIncrease, const std::initializer_list<IPrintable*>& list)
    : OrderedBufferedSet(capacityIncrease) {
  for (auto& v : list) {
    OrderedSet::add(v);
  }
}

}  // namespace zadatak3
