#include "Complex.h"
#include "IComparable.h"
#include "OrderedBufferedSet.h"
#include "OrderedSet.h"

using namespace zadatak3;

int main() {
  Complex x(1.5, 1);
  Complex x1(2, 2);
  Complex x2(3, 3);

  IPrintable *arr[] = {&x2, &x1, &x};

  std::cout << "Complex with IPrintable pointer:" << std::endl;
  for (auto v : arr) {
    std::cout << *v;
  }
  std::cout << std::endl;

  IComparable *arrC[] = {&x2, &x1, &x};

  std::sort(arrC, arrC + 3,
            [](IComparable *x1, IComparable *x2) { return *x1 < *x2; });

  std::cout << "Complex with IComparable pointer:" << std::endl;
  for (auto &v : arrC) {
    std::cout << *v;
  }

  std::cout << std::endl;

  UnorderedSet uset{&x1, &x2, &x};
  IPrintable *printablePointer = &uset;

  std::cout << "UnorderedSet:" << std::endl;
  std::cout << uset << std::endl;
  std::cout << "UnorderedSet with IPrintable pointer:" << std::endl;
  std::cout << *printablePointer << std::endl;

  OrderedSet oset{&x1, &x2, &x};
  UnorderedSet *unorderedPointer = &oset;
  printablePointer = &oset;

  Complex x4(6, 6);
  unorderedPointer->remove(&x);
  unorderedPointer->add(&x4);

  std::cout << "OrderedSet:" << std::endl;
  std::cout << oset << std::endl;
  std::cout << "OrderedSet with UnorderedSet pointer:" << std::endl;
  std::cout << *unorderedPointer << std::endl;
  std::cout << "OrderedSet with IPrintable pointer:" << std::endl;
  std::cout << *printablePointer << std::endl;

  size_t bufferSize = 5;
  BufferedSet bset(bufferSize, {&x1, &x2, &x});
  unorderedPointer = &bset;
  printablePointer = &bset;

  unorderedPointer->remove(&x1);

  std::cout << "BufferedSet:" << std::endl;
  std::cout << bset << std::endl;
  std::cout << "BufferedSet with UnorderedSet pointer:" << std::endl;
  std::cout << *unorderedPointer << std::endl;
  std::cout << "BufferedSet with IPrintable pointer:" << std::endl;
  std::cout << *printablePointer << std::endl;

  OrderedBufferedSet obset(bufferSize, {&x1, &x2, &x});
  OrderedSet *orderedPointer = &obset;
  BufferedSet *bufferedPointer = &obset;

  bufferedPointer->remove(&x1);
  orderedPointer->add(&x4);

  unorderedPointer = &obset;
  printablePointer = &obset;

  std::cout << "OrderedBufferedSet:" << std::endl;
  std::cout << obset << std::endl;
  std::cout << "OrderedBufferedSet with UnorderedSet pointer:" << std::endl;
  std::cout << *unorderedPointer << std::endl;
  std::cout << "OrderedBufferedSet with IPrintable pointer:" << std::endl;
  std::cout << *printablePointer << std::endl;
  std::cout << "OrderedBufferedSet with OrderedSet pointer:" << std::endl;
  std::cout << *orderedPointer << std::endl;
  std::cout << "OrderedBufferedSet with BufferedSet pointer:" << std::endl;
  std::cout << *bufferedPointer << std::endl;

  return 0;
}