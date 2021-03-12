#pragma once
#include <iostream>

namespace zadatak3 {
class IPrintable {
  friend std::ostream& operator<<(std::ostream&, const IPrintable&);

 public:
  virtual ~IPrintable() {}

 protected:
  virtual void print(std::ostream&) const = 0;
};
}  // namespace zadatak3
