#pragma once
#include "UnorderedSet.h"
namespace zadatak3 {
class BufferedSet : virtual public UnorderedSet {
 public:
  BufferedSet(size_t);
  BufferedSet(size_t, const std::initializer_list<IPrintable *> &);

 protected:
  virtual size_t capacityIncrease(size_t oldCapacity) const override;

 private:
  size_t capacity;
};
}  // namespace zadatak3
