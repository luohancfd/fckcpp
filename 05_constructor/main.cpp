#include <iostream>
#include <vector>
class A {
public:
  A() {
      std::cout << "construct is called" << std::endl;
  }

  A(const A &other) {
       std::cout << "copy construct is called" << std::endl;
       }
  A(A &&other) {
      std::cout << "move construct is called" << std::endl;
    }
  A& operator=(const A &other) {
      std::cout << "copy assignment is called" << std::endl;
      if (&other == this) return *this;
       return *this;
       }
  A& operator=(A &&other) {
            std::cout << "move assignment is called" << std::endl;

      return other;
    }

};
using namespace std;

void test(A &a) { cout <<  std::endl; }

void test2(A a) { cout <<  std::endl; }

int main() {
  vector<A> vec;
  A a;
  cout << "test 0" << endl;
  test2(a);
  cout << "test 1" << endl;
  test(a);
  cout << "test 2" << endl;
  vec.push_back(a);
  cout << "capacity " << vec.capacity() << endl;
  cout << "test 3" << endl;
  vec.push_back(A());
  cout << "capacity " << vec.capacity() << endl;
  cout << "test 4" << endl;
  vec.push_back(std::move(A()));
  cout << "capacity " << vec.capacity() << endl;
  cout << "test 5" << endl;
  vec.push_back(a);
  cout << "capacity " << vec.capacity() << endl;

  cout <<endl <<" Wtf happended with the move constuct? should it use less constructor" <<endl<<endl;
  // prelocated
//https://stackoverflow.com/questions/26740523/vector-push-back-calling-copy-constructor-more-than-once

    vector<A> vec2;
    vec2.reserve(5);
  cout << "test 2" << endl;
  vec2.push_back(a);
  cout << "capacity " << vec.capacity() << endl;
  cout << "test 3" << endl;
  vec2.push_back(A());
  cout << "capacity " << vec.capacity() << endl;
  cout << "test 4" << endl;
  vec2.push_back(std::move(A()));
  cout << "capacity " << vec.capacity() << endl;
  cout << "test 5" << endl;
  vec2.push_back(a);
  cout << "capacity " << vec.capacity() << endl;

cout << endl << " although you can use emplace_back. It might be quicker to use reserve + assigment" <<endl << endl;
      vector<A> vec3;
    vec3.reserve(5);
  cout << "test 2" << endl;
  vec3[0] = a;
  cout << "capacity " << vec.capacity() << endl;
  cout << "test 3" << endl;
  vec3[1] = A();
  cout << "capacity " << vec.capacity() << endl;
  cout << "test 4" << endl;
  vec3[2] = std::move(A());
  cout << "capacity " << vec.capacity() << endl;
  cout << "test 5" << endl;
  vec3[3] = a;
  cout << "capacity " << vec.capacity() << endl;

cout << endl << " resize is not good compared with reserve" <<endl << endl;
      vector<A> vec4;
    vec4.resize(5);
  cout << "test 2" << endl;
  vec4[0] = a;
  cout << "capacity " << vec.capacity() << endl;
  cout << "test 3" << endl;
  vec4[1] = A();
  cout << "capacity " << vec.capacity() << endl;
  cout << "test 4" << endl;
  vec4[2] = std::move(A());
  cout << "capacity " << vec.capacity() << endl;
  cout << "test 5" << endl;
  vec4[3] = a;
  cout << "capacity " << vec.capacity() << endl;
  return 0;

// a better example https://en.cppreference.com/w/cpp/container/vector/emplace
}
