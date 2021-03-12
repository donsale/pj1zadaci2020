#include "VectorN.h"

namespace zadatak2 {
const double VectorN::Error = 0;

std::ostream &operator<<(std::ostream &stream, const VectorN &vec) {
  for (size_t i = 0; i < vec.n; i++) stream << vec.arr[i] << " ";

  return stream;
}

std::istream &operator>>(std::istream &stream, VectorN &vec) {
  for (size_t i = 0; i < vec.n; i++) stream >> vec.arr[i];

  return stream;
}

VectorN operator*(double s, const VectorN &v) { return v * s; }

VectorN::VectorN() : n(0), arr(nullptr) {}

VectorN::VectorN(size_t n) : n(n), arr(new double[n]()) {}

VectorN::VectorN(double value) : VectorN({value}) {}

VectorN::VectorN(const std::initializer_list<double> &values)
    : VectorN(values.size()) {
  int i = 0;
  for (double value : values) this->arr[i++] = value;
}

VectorN::~VectorN() { dispose(); }

VectorN::VectorN(const VectorN &other) { copy(other); }

VectorN::VectorN(VectorN &&other) noexcept { move(std::move(other)); }

VectorN &VectorN::operator=(const VectorN &other) {
  if (this != &other) {
    dispose();
    copy(other);
  }
  return *this;
}

VectorN &VectorN::operator=(VectorN &&other) noexcept {
  if (this != &other) {
    dispose();
    move(std::move(other));
  }
  return *this;
}

size_t VectorN::getSize() const { return n; }

const double &VectorN::getElement(size_t index) const {
  if (index >= 0 && index < n) return arr[index];
  return Error;
}

const double &VectorN::operator[](size_t index) const {
  return getElement(index);
}

VectorN VectorN::operator+(const VectorN &other) const {
  return apply(other, [](double a, double b) { return a + b; });
}

VectorN VectorN::operator-(const VectorN &other) const {
  return apply(other, [](double a, double b) { return a - b; });
}

double VectorN::operator*(const VectorN &other) const {
  VectorN tmp = apply(other, [](double a, double b) { return a * b; });
  return std::accumulate(tmp.arr, tmp.arr + tmp.n, 0.0);
}

VectorN VectorN::operator*(double s) const {
  VectorN tmp = *this;
  for (size_t i = 0; i < n; i++) tmp.arr[i] *= s;
  return tmp;
}

bool VectorN::operator==(const VectorN &other) const {
  if (n != other.n)
    return false;
  else
    for (size_t i = 0; i < n; i++)
      if (arr[i] != other.arr[i]) return false;

  return true;
}

double VectorN::operator()(double x) const {
  double sum = 0;
  for (size_t i = 0; i < n; i++) sum += arr[i] * std::pow(x, i);

  return sum;
}

VectorN VectorN::ZeroVector(size_t n) {
  VectorN tmp(n);
  std::fill(tmp.arr, tmp.arr + n, 0);

  return tmp;
}

VectorN VectorN::apply(const VectorN &other,
                       const std::function<double(double, double)> &fun) const {
  if (n != other.n) return VectorN({});
  VectorN tmp(n);
  for (size_t i = 0; i < n; i++) tmp.arr[i] = fun(arr[i], other.arr[i]);
  return tmp;
}

void VectorN::move(VectorN &&other) {
  n = other.n;
  arr = other.arr;
  other.arr = nullptr;
}

void VectorN::copy(const VectorN &other) {
  n = other.n;
  arr = new double[n];
  std::copy(other.arr, other.arr + n, arr);
}

void VectorN::dispose() {
  delete[] arr;
  arr = nullptr;
}
}  // namespace zadatak2