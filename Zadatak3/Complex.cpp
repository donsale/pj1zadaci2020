#include "Complex.h"

namespace zadatak3 {
Complex::Complex(double x, double y) : re(x), im(y) {}

std::partial_ordering Complex::compareTo(const IComparable &other) const {
  const Complex &obj = dynamic_cast<const Complex &>(other);
  return this->Abs() <=> obj.Abs();
}

void Complex::print(std::ostream &stream) const {
  stream << "(" << re << ", " << im << "i)" << std::endl;
}

Complex Complex::operator+(const Complex &rhs) const {
  return Complex(re + rhs.re, im + rhs.im);
}

Complex Complex::operator-(const Complex &rhs) const {
  return Complex(re - rhs.re, im - rhs.im);
}

Complex Complex::operator*(const Complex &rhs) const {
  return Complex(re * rhs.re - im * rhs.im, re * rhs.im + im * rhs.re);
}

Complex Complex::operator/(const Complex &rhs) const {
  double denominator = rhs.re * rhs.re + rhs.im * rhs.im;
  if (denominator == 0.0) return Complex(0, 0);
  return Complex((re * rhs.re + im * rhs.im) / denominator,
                 (im * rhs.re - re * rhs.im) / denominator);
}

double Complex::Abs() const { return std::sqrt(re * re + im * im); }

double Complex::Argument() const { return std::atan2(im, re); }

Complex Complex::Conjugate() const { return Complex(re, -im); }

Complex Complex::Pow(int pow) const {
  Complex tmp(re, im);
  for (size_t i = 1; i < pow; i++) tmp = tmp * (*this);
  return tmp;
}

Complex::operator double() const { return re; }

}  // namespace zadatak3