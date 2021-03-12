#include <iostream>

#include "BufferedCollection.h"
#include "Complex.h"

using namespace zadatak4;

int main() {
  std::weak_ptr<Complex> wptr;

  {
    std::shared_ptr<Complex> sptr(new Complex(2, 2));
    wptr = sptr;
  }

  try {
    BufferedCollection bc(5);
    bc.Add(wptr);
    std::weak_ptr<Complex> x2 = bc[0];  // pristupamo objektu koji je istekao
  } catch (const std::exception &ex) {
    std::cout << ex.what() << std::endl;
  }

  std::shared_ptr<Complex> sptr(new Complex(1, 1));

  try {
    BufferedCollection bc(5);
    bc.Add(sptr);
    std::weak_ptr<Complex> x2 = bc[15];  // pristup izvan opsega
  } catch (const std::exception &ex) {
    std::cout << ex.what() << std::endl;
  }
  BufferedCollection bc(5);
  bc.Add(wptr);
  try {
    BufferedCollection bcc(bc);
  } catch(const std::exception& ex) {
    std::cout << ex.what() << std::endl;
  }

  return 0;
}
