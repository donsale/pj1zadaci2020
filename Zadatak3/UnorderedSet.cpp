#include "UnorderedSet.h"

namespace zadatak3 {
UnorderedSet::UnorderedSet(size_t capacity)
    : currentSize(0), capacity(capacity), arr(new IPrintable *[capacity]) {}

UnorderedSet::UnorderedSet(const std::initializer_list<IPrintable *> &list)
    : UnorderedSet(list.size()) {
  for (auto &v : list) this->add(v);
}

UnorderedSet::~UnorderedSet() { dispose(); }

UnorderedSet::UnorderedSet(const UnorderedSet &other) { copy(other); }

UnorderedSet::UnorderedSet(UnorderedSet &&other) noexcept {
  move(std::move(other));
}

UnorderedSet &UnorderedSet::operator=(const UnorderedSet &other) {
  if (this != &other) {
    dispose();
    copy(other);
  }
  return *this;
}
UnorderedSet &UnorderedSet::operator=(UnorderedSet &&other) noexcept {
  if (this != &other) {
    dispose();
    move(std::move(other));
  }
  return *this;
}
void UnorderedSet::add(IPrintable *other) {
  if (currentSize == capacity) {
    size_t newCapacity = capacity + capacityIncrease(capacity);
    if (newCapacity > capacity) {
      IPrintable **newArr = new IPrintable *[newCapacity];
      std::copy(arr, arr + currentSize, newArr);

      delete[] arr;
      capacity = newCapacity;
      arr = newArr;
    }
  }
  if (currentSize < capacity && !contains(other)) arr[currentSize++] = other;
}

void UnorderedSet::remove(const IPrintable *toRemove) {
  for (size_t i = 0; i < currentSize; i++)
    if (arr[i] == toRemove) {
      for (size_t j = i; j < currentSize - 1; j++) arr[j] = arr[j + 1];
      currentSize--;
      break;
    }
}

IPrintable *UnorderedSet::operator[](size_t index) { return getElement(index); }

const IPrintable *UnorderedSet::operator[](size_t index) const {
  return getElement(index);
}

void UnorderedSet::print(std::ostream &stream) const {
  std::for_each(arr, arr + currentSize,
                [](const IPrintable *p) { std::cout << *p; });
}

size_t UnorderedSet::capacityIncrease(size_t oldCapacity) const { return 0; }

void UnorderedSet::copy(const UnorderedSet &other) {
  currentSize = other.currentSize;
  capacity = other.capacity;

  arr = new IPrintable *[capacity];
  std::copy(other.arr, other.arr + other.currentSize, arr);
}

void UnorderedSet::move(UnorderedSet &&other) {
  currentSize = other.currentSize;
  capacity = other.capacity;

  arr = other.arr;
  other.arr = nullptr;
}

void UnorderedSet::dispose() {
  delete[] arr;
  arr = nullptr;
}

bool UnorderedSet::contains(const IPrintable *other) const {
  for (size_t i = 0; i < currentSize; i++)
    if (arr[i] == other) return true;

  return false;
}

IPrintable *UnorderedSet::getElement(size_t index) const {
  if (index >= 0 && index < currentSize) return arr[index];
  return nullptr;
}

}  // namespace zadatak3
