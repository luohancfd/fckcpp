#include <iostream>
#include <string>
#include <vector>
template<typename T>
class A {
    public:
    static std::vector<std::string> data;
    A() {
        for (auto &i : data) {
            std::cout << i << ",";
        }
        std::cout << std::endl;
    }
};


