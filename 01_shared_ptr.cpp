#include <memory>
#include <iostream>
struct Foo {
    Foo(int i) : ptr{std::make_shared<int>(i)} {}
    std::shared_ptr<int> ptr;

    void set(int i) {
        ptr = std::make_shared<int>(i);
    }
};

int main() {
    Foo f1{0};  // regular construct
    Foo f2{f1}; // Using the implicitly generated copy ctor.
    Foo f3 = f1; // copy assignment

    std::cout << f1.ptr.get() << std::endl;
    std::cout << f2.ptr.get() << std::endl;
    std::cout << f3.ptr.get() << std::endl;

    Foo f4 = std::move(f1);     // move assignment
    std::cout << f4.ptr.get() << std::endl;
    std::cout << f1.ptr.get() << std::endl;
    std::cout << f2.ptr.get() << std::endl;

    f2.set(5);
    std::cout << f2.ptr.get() << std::endl;
    std::cout << f3.ptr.get() << std::endl;
/* Expected output, number doesn't matter
0x561d0c123ec0
0x561d0c123ec0
0x561d0c123ec0
0x561d0c123ec0
0
0x561d0c123ec0
0x561d0c1242f0
0x561d0c123ec0
*/
}