#include "Complex.h"

namespace zadatak4 {
Complex::Complex(double x, double y) noexcept : re(x), im(y) {}

Complex Complex::operator+(const Complex &rhs) const noexcept {
  return Complex(re + rhs.re, im + rhs.im);
}

Complex Complex::operator-(const Complex &rhs) const noexcept {
  return Complex(re - rhs.re, im - rhs.im);
}

Complex Complex::operator*(const Complex &rhs) const noexcept {
  return Complex(re * rhs.re - im * rhs.im, re * rhs.im + im * rhs.re);
}

Complex Complex::operator/(const Complex &rhs) const noexcept {
  double denominator = rhs.re * rhs.re + rhs.im * rhs.im;
  if (denominator == 0.0) return Complex(0, 0);
  return Complex((re * rhs.re + im * rhs.im) / denominator,
                 (im * rhs.re - re * rhs.im) / denominator);
}

double Complex::Abs() const noexcept { return std::sqrt(re * re + im * im); }

double Complex::Argument() const noexcept { return std::atan2(im, re); }

Complex Complex::Conjugate() const noexcept { return Complex(re, -im); }

Complex Complex::Pow(size_t pow) const noexcept {
  Complex tmp(re, im);
  for (size_t i = 1; i < pow; i++) tmp = tmp * (*this);
  return tmp;
}

std::ostream &operator<<(std::ostream &stream, const Complex &z) noexcept {
  stream << "(" << z.re << ", " << z.im << "i)" << std::endl;
  return stream;
}

}  // namespace zadatak4