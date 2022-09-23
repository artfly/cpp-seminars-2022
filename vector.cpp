#include <algorithm>
#include <cassert>
#include <iostream>

class vector {
public:

  vector(int capacity = 8): capacity_(capacity),
   size_(0), data_(new int[capacity]()) {
  }
  vector(vector & other): capacity_(other.capacity_),
    size_(other.size_), data_(new int[capacity_]) {
      std::copy(other.data_, other.data_ + size_, data_);
    }

  // v1 = v2 = v3;
  // v1 = v1;
  // v1 = v2.operator=(v3)
  // v1.operator=(v2.operator=(v3))
  // v1 = v2; => other(v2)
  vector & operator=(vector other) {
    // copy ctor, new data_ initialized
    capacity_ = other.capacity_;
    size_ = other.size_;
    // data_ -> other, other.data_ -> this
    std::swap(data_, other.data_);
    // if (&other != this) {
    //   delete[] data_;
    //   capacity_ = other.capacity_;
    //   size_ = other.size_;
    //   data_ = new int[capacity_];
    //   std::copy(other.data_, other.data_ + size_, data_);
    // }
    // return *this;
  }

  ~vector() { delete[] data_; }

  // adds element to the last avaialable position,
  // resizes vector if current capacity is reached
  void push_back(int num) {
    if (capacity_ == size_) {
      resize(capacity_ * 2);
    }
    data_[size_] = num;
    size_++;
  }

  int size() { return this->size_; }

  int & operator[](size_t idx) {
    // assert
  }

  void set(int num, int idx);
  int at(int idx);

private:
  int capacity_;
  int size_;
  int *data_;

  // resizes vector to given capacity
  void resize(int new_capacity) {
    int * tmp = new int[new_capacity];
    std::copy(data_, data_ + size_, tmp);
    delete[] data_;
    data_ = tmp;
    capacity_ = new_capacity;
  }
};

/*
  - default ctor A()
  - dtor ~A()
  - copy ctor A(A & other)
  - operator=(A & other)
  - move ctor A(A && tmp)
  - move operator=(A && tmp)
*/

class B {
  public:
    B() {
      std::cout << "B!" << std::endl;
    }
    ~B() {
      std::cout << "~B!" << std::endl;
    }
    B(B & other) {
      std::cout << "copy B!" << std::endl;
    }

    B & operator=(const B & other) {
      // this.i = other.i;
      // ....
      return *this;
    }
};

void foo() {
  B b;
  B b1(b);
}

class A {
  // private

  public:

    A() {
      std::cout << "A!" << std::endl;
    }

    ~A() {
      std::cout << "~A!" << std::endl;
    }

    A(A & other) {
      
      // a.a = other.a; ....
      std::cout << a << std::endl;
    }

    int a;
    int * pa;
    B b;
    B * pb;
};

class D {
 public:
  D() {
    std::cout << "D!" << std::endl; 
  } 
  D(int i) {
    std::cout << "D int!" << std::endl;
  }
  D & operator=(const D & other) {
    std::cout << "D assign!" << std::endl;
    return *this;
  }
};

class C {
  public:
  C(int i): d(D(i)), d1(D(42)) {
    // d = D(i);
    std::cout << "C!" << std::endl;
  }
  private:
    D d;
    D d1;
};

int main(int argc, char **argv) {
  C c(42);
  // A a;
  // assert(a.a == 0);
  // assert(a.pa == nullptr);
  // assert(a.pb == nullptr);

  // a.a = 42;
  // a.pa = &(a.a);
  // a.pb = &(a.b);

  // A a1(a);

  // assert(a1.a == 42);
  // assert(a1.pa == a.pa);
  // assert(a1.pb == a.pb);


  // vector v1(8);
  // // init...

  // vector v3(v1);

  // vector v2;
  // v2 = v1;
  // same values?

  // vector v;
  // v.size();
  // // size(&v)
  // vector v1;
  // v1.size();
}