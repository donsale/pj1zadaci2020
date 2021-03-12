#include "IPrintable.h"

namespace zadatak5{
std::ostream &operator<<(std::ostream &stream, const IPrintable &obj) noexcept {
  obj.print(stream);
  return stream;
}
}  // namespace zadatak5