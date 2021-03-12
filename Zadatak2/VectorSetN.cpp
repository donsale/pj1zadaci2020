#include "VectorSetN.h"

namespace zadatak2 {
std::ostream &operator<<(std::ostream &stream, const VectorSetN &set) {
  std::for_each(set.arr, set.arr + set.currentSize,
                [&stream](VectorN &vec) { stream << vec << std::endl; });

  return stream;
}

VectorSetN::VectorSetN(size_t n, int dimension)
    : capacity(n), currentSize(0), dimension(dimension), arr(new VectorN[n]) {}

VectorSetN::VectorSetN(int dimension,
                       const std::initializer_list<VectorN> &list)
    : VectorSetN(list.size(), dimension) {
  for (auto &value : list)
    if (value.getSize() == dimension) *this += value;
}

VectorSetN::~VectorSetN() { dispose(); }

VectorSetN::VectorSetN(const VectorSetN &other) { copy(other); }

VectorSetN::VectorSetN(VectorSetN &&other) noexcept { move(std::move(other)); }

VectorSetN &VectorSetN::operator=(const VectorSetN &other) {
  if (this != &other) {
    dispose();
    copy(other);
  }
  return *this;
}

VectorSetN &VectorSetN::operator=(VectorSetN &&other) noexcept {
  if (this != &other) {
    dispose();
    move(std::move(other));
  }
  return *this;
}

VectorSetN &VectorSetN::operator+=(const VectorN &vec) {
  if (dimension == vec.getSize() && !contains(vec) && currentSize < capacity) {
    arr[currentSize++] = vec;
  }

  return *this;
}

VectorSetN &VectorSetN::operator-=(const VectorN &vec) {
  bool found = false;
  for (size_t i = 0; i < currentSize; i++)
    if (arr[i] == vec) {
      for (size_t j = i; j < currentSize - 1; j++) arr[j] = arr[j + 1];
      found = true;
    }
  if (found) currentSize--;
  return *this;
}

bool VectorSetN::operator==(const VectorSetN &b) const {
  if (currentSize != b.currentSize) return false;

  for (size_t i = 0; i < currentSize; i++)
    if (!b.contains(arr[i]) || !this->contains(b.arr[i])) return false;

  return true;
}

size_t VectorSetN::getSize() const { return currentSize; }

VectorN *VectorSetN::getArray() const { return arr; }

VectorSetN VectorSetN::filter(
    const std::function<bool(const VectorN &)> &fun) const {
  VectorSetN tmp(currentSize, dimension);
  for (size_t i = 0; i < currentSize; i++)
    if (fun(arr[i])) tmp += arr[i];

  return tmp;
}

VectorSetN VectorSetN::map(
    const std::function<VectorN(const VectorN &)> &fun) const {
  VectorSetN tmp(currentSize, dimension);
  for (size_t i = 0; i < currentSize; i++) tmp += fun(arr[i]);

  return tmp;
}

bool VectorSetN::isLinearlyIndependent() const {
  if (currentSize > dimension) return false;
  size_t rank = rankOfMatrix();
  return rank == currentSize;
}

bool VectorSetN::contains(const VectorN &vec) const {
  for (size_t i = 0; i < currentSize; i++)
    if (arr[i] == vec) return true;

  return false;
}

// Kod preuzet sa https://www.geeksforgeeks.org/program-for-rank-of-matrix/
size_t VectorSetN::rankOfMatrix() const {
  size_t rows = dimension;
  size_t columns = currentSize;

  double *mat = new double[rows * columns];
  for (size_t i = 0; i < rows; i++)
    for (size_t j = 0; j < columns; j++) {
      mat[i * columns + j] = arr[j].getElement(i);
    }

  size_t rank = columns;

  for (size_t row = 0; row < rank; row++) {
    if (mat[row * columns + row]) {
      for (size_t col = 0; col < rows; col++) {
        if (col != row) {
          double mult = mat[col * columns + row] / mat[row * columns + row];
          for (size_t i = 0; i < rank; i++)
            mat[col * columns + i] -= mult * mat[row * columns + i];
        }
      }
    }

    else {
      bool reduce = true;

      for (size_t i = row + 1; i < rows; i++) {
        if (mat[i * columns + row]) {
          for (size_t k = 0; k < rank; k++) {
            double tmp = mat[row * columns + k];
            mat[row * columns + k] = mat[i * columns + k];
            mat[i * columns + k] = tmp;
          }
          reduce = false;
          break;
        }
      }

      if (reduce) {
        rank--;

        for (size_t i = 0; i < row; i++)
          mat[i * columns + row] = mat[i * columns + rank];
      }

      row--;
    }
  }

  delete[] mat;
  return rank;
}

void VectorSetN::move(VectorSetN &&other) {
  currentSize = other.currentSize;
  capacity = other.capacity;
  dimension = other.dimension;
  arr = other.arr;
  other.arr = nullptr;
}

void VectorSetN::copy(const VectorSetN &other) {
  currentSize = other.currentSize;
  capacity = other.capacity;
  dimension = other.dimension;

  arr = new VectorN[capacity];
  std::copy(other.arr, other.arr + other.currentSize, arr);
}

void VectorSetN::dispose() {
  delete[] arr;
  arr = nullptr;
}
}  // namespace zadatak2