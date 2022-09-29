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

 private:
  int capacity_;
  int size_;
  int *data_;

  void resize(int new_capacity);
};