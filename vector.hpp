#pragma once
#include <cstddef>

class vector {
 public:
  vector(int capacity = 8);

  vector(vector &other);

  vector &operator=(vector other);

  ~vector();

  void push_back(int num);

  int size();

  int &operator[](size_t idx);

  class iterator {
    public:
      iterator(iterator & other) = default;

      bool operator==(iterator & other) const;
      bool operator!=(iterator & other) const;

      int & operator*();

      // prefix ++it
      iterator & operator++();
      // postfix it++
      iterator /*???*/ operator++(int);

    private:
      int idx_;
      vector & v;
  };

  iterator /*???*/ begin();

  iterator /*???*/ end();

 private:
  int capacity_;
  int size_;
  int *data_;

  void resize(int new_capacity);
};