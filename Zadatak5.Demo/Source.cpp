#include <iostream>

#include "BufferedCollection.h"

using namespace zadatak5;

int main() {
  BufferedCollection<int> bc(5);
  try {
    bc.Add(15);
    bc.Add(5);
    bc.Add(10);
    bc.Remove(5);
  } catch (const std::exception& ex) {
    std::cout << ex.what() << std::endl;
  }

  std::cout << bc << std::endl;
  std::cout << bc.sum() << std::endl;

  try {
    int a = bc[25]; // pristup van opsega
  } catch (const std::exception& ex) {
    std::cout << ex.what() << std::endl;
  }

  return 0;
}