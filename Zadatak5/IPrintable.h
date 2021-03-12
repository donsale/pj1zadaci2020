#pragma once
#include <iostream>

namespace zadatak5 {
class IPrintable {
  friend std::ostream& operator<<(std::ostream&, const IPrintable&) noexcept;

 public:
  virtual ~IPrintable() {}

 protected:
  virtual void print(std::ostream&) const noexcept = 0;
};
}  // namespace zadatak5
