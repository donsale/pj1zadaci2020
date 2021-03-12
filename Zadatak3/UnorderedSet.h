#pragma once
#include <algorithm>

#include "IPrintable.h"
namespace zadatak3 {
class UnorderedSet : virtual public IPrintable {
 public:
  UnorderedSet(size_t capacity);
  UnorderedSet(const std::initializer_list<IPrintable *> &);
  ~UnorderedSet();

  UnorderedSet(const UnorderedSet &);
  UnorderedSet(UnorderedSet &&) noexcept;

  UnorderedSet &operator=(const UnorderedSet &);
  UnorderedSet &operator=(UnorderedSet &&) noexcept;

  virtual void add(IPrintable *);
  virtual void remove(const IPrintable *);

  virtual IPrintable *operator[](size_t index);
  virtual const IPrintable *operator[](size_t index) const;

 protected:
  virtual size_t capacityIncrease(size_t oldCapacity) const;
  virtual void print(std::ostream &) const override;

  IPrintable **arr;
  size_t currentSize;
  size_t capacity;

  IPrintable *getElement(size_t index) const;

 private:
  void copy(const UnorderedSet &);
  void move(UnorderedSet &&);
  void dispose();
  bool contains(const IPrintable *) const;
};
}  // namespace zadatak3
