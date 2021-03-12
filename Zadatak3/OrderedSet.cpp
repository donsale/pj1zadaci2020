#include "OrderedSet.h"

namespace zadatak3 {
OrderedSet::OrderedSet(size_t capacity) : UnorderedSet(capacity) {}

OrderedSet::OrderedSet(const std::initializer_list<IPrintable *> &list)
    : UnorderedSet(list.size()) {
  for (auto &v : list) add(v);
}

void OrderedSet::add(IPrintable *other) {
  UnorderedSet::add(other);
  std::sort(arr, arr + currentSize,
            [](const IPrintable *p1, const IPrintable *p2) {
              return dynamic_cast<const IComparable &>(*p1) <
                     dynamic_cast<const IComparable &>(*p2);
            });
}

IComparable *OrderedSet::operator[](size_t index) {
  return dynamic_cast<IComparable *>(UnorderedSet::getElement(index));
}

const IComparable *OrderedSet::operator[](size_t index) const {
  return dynamic_cast<IComparable *>(UnorderedSet::getElement(index));
}

}  // namespace zadatak3
