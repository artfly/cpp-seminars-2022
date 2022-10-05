#pragma once
#include <cstddef>

class vector {
 public:
 // expicit vector(): vector(DEFAULT_CAPACITY) {}
 // explicit vector(int capacity) {...}
  explicit vector(int capacity = DEFAULT_CAPACITY);

  vector(vector &other);

  vector &operator=(vector other);

  ~vector();

  void push_back(int num);

  int size();

  int &operator[](size_t idx);

  class iterator {
    public:
      iterator(const iterator & other) = default;
      iterator(int idx, vector & v): idx_(idx), v_(v) {}

      bool operator==(const iterator & other) const;
      bool operator!=(const iterator & other) const;

      int & operator*();

      // prefix ++it
      iterator & operator++();
      // postfix it++
      iterator /*???*/ operator++(int);

    private:
      int idx_;
      vector & v_;
  };

  iterator /*???*/ begin();

  iterator /*???*/ end();

 private:
  static const int DEFAULT_CAPACITY = 8;
  int capacity_;
  int size_;
  int *data_;

  void resize(int new_capacity);
};