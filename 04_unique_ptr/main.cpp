#include "memory.hpp"
#include <iomanip>
#include <iostream>

int main() {
  Memory::pointer_n_t<3, double> a;

  a = Memory::createC<double>(2, 2, 2);

  Memory::freeC(a);

  // No matching constructor for initialization of 'Memory::SmartArray<3,
  // double>' Memory::SmartArray<3, double> c(2,2,2,3);

  // In template: static_assert failed due to requirement '4 < 4' "dimension
  // must be smaller than 4" Memory::SmartArray<4, double> c(2,2,2,3);

  Memory::SmartArray<3, double> c(2, 2, 2);
  std::cout << "c = " << c.data << std::endl;

  int w = 0;
  for (int k = 0; k < 2; ++k) {
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 2; ++j) {
        c[i][j][k] = w++;
      }
    }
  }

  Memory::SmartArray<3, double> d(std::move(c));
  std::cout << "Move construct d = " << d.data << std::endl;


  // c[0][0][0] = 1;  //segmentation fault
  for (int k = 0; k < 2; ++k) {
    std::cout << "Page " << k << std::endl;
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 2; ++j) {
        std::cout << std::setw(3) << d[i][j][k] << "  ";
      }
      std::cout << std::endl;
    }
  }


   Memory::SmartArray<3, double> g = std::move(d);
   std::cout << "Move assignment g = " << d.data << std::endl;
}