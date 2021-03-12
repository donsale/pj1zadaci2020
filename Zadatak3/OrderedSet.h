#pragma once
#include "IComparable.h"
#include "UnorderedSet.h"

namespace zadatak3 {
class OrderedSet : virtual public UnorderedSet {
 public:
  OrderedSet(size_t);
  OrderedSet(const std::initializer_list<IPrintable *> &);

  virtual void add(IPrintable *) override;

  virtual IComparable *operator[](size_t index) override;
  virtual const IComparable *operator[](size_t index) const override;

  // Podaci se cuvaju u sortiranom poretku pa se oslanjamo na to za sortiran
  // ispis
  // virtual void print(std::ostream &) const override;
};

}  // namespace zadatak3
