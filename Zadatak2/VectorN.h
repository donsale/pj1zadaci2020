#pragma once
#include <cmath>
#include <functional>
#include <iostream>
#include <numeric>

namespace zadatak2 {
class VectorN {
  friend std::ostream& operator<<(std::ostream&, const VectorN&);
  friend std::istream& operator>>(std::istream&, VectorN&);
  friend VectorN operator*(double s, const VectorN&);

 public:
  VectorN();
  explicit VectorN(size_t n);
  VectorN(double n);
  VectorN(const std::initializer_list<double>& values);
  ~VectorN();

  VectorN(const VectorN& other);
  VectorN(VectorN&&) noexcept;

  VectorN& operator=(const VectorN&);
  VectorN& operator=(VectorN&&) noexcept;

  size_t getSize() const;
  const double& getElement(size_t index) const;
  const double& operator[](size_t index) const;

  VectorN operator+(const VectorN&) const;
  VectorN operator-(const VectorN&) const;
  double operator*(const VectorN&) const;
  VectorN operator*(double) const;

  bool operator==(const VectorN&) const;
  double operator()(double x) const;
  static VectorN ZeroVector(size_t n);

  const static double Error;

 private:
  double* arr;
  size_t n;
  VectorN apply(const VectorN&,
                const std::function<double(double, double)>&) const;

  void move(VectorN&&);
  void copy(const VectorN&);
  void dispose();
};
}  // namespace zadatak2