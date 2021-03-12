#include "BufferedSet.h"

namespace zadatak3 {

zadatak3::BufferedSet::BufferedSet(size_t capacityIncrease)
    : capacity(capacityIncrease), UnorderedSet(0) {}

BufferedSet::BufferedSet(size_t capacityIncrease,
                         const std::initializer_list<IPrintable*>& list)
    : UnorderedSet(list), capacity(capacityIncrease) {}

size_t zadatak3::BufferedSet::capacityIncrease(size_t oldCapacity) const {
  return capacity;
}
}  // namespace zadatak3
