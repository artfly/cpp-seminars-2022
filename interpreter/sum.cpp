#include <iostream>

class Foo {
  public:
  int i = 42;
  virtual int plus(int a, int b) {
    return a + b;
  }

  virtual int minus(int a, int b) {
    return - a - b;
  }
};

class Bar: public Foo {
  public:
   
   int plus(int a, int b) {
     return a - b;
   }
};

Foo * get_foo() {
  return new Bar();
}

void baz(int i) {}

int main(int argc, char ** argv) {  
  return 0;
}
