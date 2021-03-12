#pragma once
#include "BufferedSet.h"
#include "OrderedSet.h"

namespace zadatak3 {
class OrderedBufferedSet : public OrderedSet, public BufferedSet {
 public:
  OrderedBufferedSet(size_t);
  OrderedBufferedSet(size_t, const std::initializer_list<IPrintable *> &);
};
}  // namespace zadatak3
