#include "smart_ptr.hpp"
#include <iostream>

struct A {
    A() {
        std::cout << "A!" << std::endl;
    }

    ~A() {
        std::cout << "~A!" << std::endl;
    }

    A(const A & other) {
        std::cout << "Acopy!" << std::endl;
    }

    A & operator=(const A & other) {
        std::cout << "A=!" << std::endl;
        return *this;
    }

    void foo() {
        std::cout << "foo!" << std::endl;
    }
};

void test1() {
    shared_ptr<A> s1;
    shared_ptr<A> s2;
}

void test2() {
    // A!
    A * a = new A();
    shared_ptr<A> s1(a);
    shared_ptr<A> s2(s1);
    // ~A!
}

void test3() {
    // A!
    A * a = new A();
    shared_ptr<A> s1(a);
    shared_ptr<A> s2(a);
    // ~A!
    // Error: double free!
}

void test4() {
    // A!
    A * a = new A();
    // A!
    A * a1 = new A();
    shared_ptr<A> s1(a);
    shared_ptr<A> s2(a1);
    // ~A!
    a1 = a;
    // ~A!
}

void test5() {
    // A!
    A * a = new A();
    shared_ptr<A> s1(a);
    s1.release();
    // memory leak: a is not destructed
}

void test6() {
    // A!
    A * a = new A();
    shared_ptr<A> s1(a);
    // ~A!
    s1.reset(nullptr);
    // A!
    A * a1 = new A();
    shared_ptr<A> s2(a1);
    shared_ptr<A> s3(s2);
    s2.reset(nullptr);
    // Hello!
    std::cout << "Hello!" << std::endl;
    // ~A
}

void test7() {
    // A!
    A * a = new A();
    shared_ptr<A> s1(a);
    A * a1 = s1.get();
    // true
    std::cout << std::boolalpha << (a == a1) << std::endl;
    // ~A!
}

void test8() {
    // A!
    A * a = new A();
    shared_ptr<A> s1(a);
    // Acopy!
    A copy(*s1);
    // ~A!
    // ~A!
}

void test9() {
    // A!
    A * a = new A();
    shared_ptr<A> s1(a);
    // foo!
    s1->foo();
    // ~A!
}

template<typename T, typename V>
void two_shared_ptrs(std::shared_ptr<T> sp1, std::shared_ptr<V> sp2) {
}

template<typename T, typename V>
void test() {
    shared_ptr(new T()), shared_ptr(new V());
}

int main() {
    return 0;
}