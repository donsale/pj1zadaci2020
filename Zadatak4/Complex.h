#pragma once
#include <cmath>
#include <iostream>

namespace zadatak4 {
class Complex {
  double re;
  double im;

  friend std::ostream& operator<<(std::ostream&, const Complex&) noexcept;

 public:
  Complex(double x = 0, double y = 0) noexcept;

  Complex operator+(const Complex&) const noexcept;
  Complex operator-(const Complex&) const noexcept;
  Complex operator*(const Complex&) const noexcept;
  Complex operator/(const Complex&) const noexcept;

  double Abs() const noexcept;
  double Argument() const noexcept;
  Complex Conjugate() const noexcept;
  Complex Pow(size_t pow) const noexcept;
};
}  // namespace zadatak4
