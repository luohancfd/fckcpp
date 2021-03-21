#include <type_traits>
#include <iostream>
template<typename T>
class A {
    public:
    A(T i);

    template<bool U>
    void construct();

    // template<> void construct<true>();
    // template<> void construct<false>();

};

