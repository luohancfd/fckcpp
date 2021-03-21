#include "A.hpp"

template<>
std::vector<std::string> A<double>::data = {"A", "B"};

template<>
std::vector<std::string> A<int>::data = {"A", "C"};

int main() {

    A<int> a;

    A<double> b;

}