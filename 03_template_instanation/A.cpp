#include "A.hpp"
#include <iostream>

template <typename T> A<T>::A(T i) {
  if (std::is_integral<T>::value) {
    construct<true>();
  } else {
    construct<false>();
  }
}
template<typename T>
template<bool U>
void A<T>::construct() {
    if constexpr(U) {
        std::cout << "is int" <<std::endl;
    } else {
        std::cout << "is not int " << std::endl;
    }
}

template class A<double>;
template class A<int>;
