#pragma once
#include <cstddef>

class vector {
 public:
  explicit vector(size_t capacity = DEFAULT_CAPACITY);

  vector(const vector &other);

  vector &operator=(vector other);

  ~vector();

  void push_back(size_t num);

  size_t size();

  int &operator[](size_t idx);
  int operator[](size_t idx) const;

  bool operator==(const vector & other) const;
  bool operator!=(const vector & other) const;

  class iterator {
    public:
      iterator(const iterator & other) = default;
      iterator(size_t idx, vector & v): idx_(idx), v_(v) {}

      bool operator==(const iterator & other) const;
      bool operator!=(const iterator & other) const;

      int & operator*();

      iterator & operator++();
      iterator operator++(int);

    private:
      size_t idx_;
      vector & v_;
  };

  iterator begin();
  iterator end();

 private:
  static const size_t DEFAULT_CAPACITY = 8;
  
  size_t capacity_;
  size_t size_;
  int *data_;

  void resize(size_t new_capacity);
};