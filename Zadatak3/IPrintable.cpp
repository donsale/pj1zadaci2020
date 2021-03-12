#include "IPrintable.h"

namespace zadatak3 {
std::ostream &operator<<(std::ostream &stream, const IPrintable &obj) {
  obj.print(stream);
  return stream;
}
}  // namespace zadatak3
