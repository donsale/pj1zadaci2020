#pragma once
#include "IComparable.h"
#include "IPrintable.h"

namespace zadatak3 {
class Complex : virtual public IComparable, virtual public IPrintable {
  double re;
  double im;

 protected:
  virtual std::partial_ordering compareTo(const IComparable&) const override;
  virtual void print(std::ostream&) const override;

 public:
  Complex(double x = 0, double y = 0);

  Complex operator+(const Complex&) const;
  Complex operator-(const Complex&) const;
  Complex operator*(const Complex&) const;
  Complex operator/(const Complex&) const;

  double Abs() const;
  double Argument() const;
  Complex Conjugate() const;
  Complex Pow(int pow) const;

  operator double() const;
};
}  // namespace zadatak3
