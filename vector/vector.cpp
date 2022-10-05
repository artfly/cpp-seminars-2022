#include "vector.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <array>
#include <vector>
#include <list>

vector::vector(size_t capacity)
    : capacity_(capacity), size_(0), data_(new int[capacity]) {}

vector::vector(const vector &other)
    : capacity_(other.capacity_),
      size_(other.size_),
      data_(new int[capacity_]) {
  std::copy(other.data_, other.data_ + size_, data_);
}

vector &vector::operator=(vector other) {
  capacity_ = other.capacity_;
  size_ = other.size_;
  std::swap(data_, other.data_);
  return *this;
}

vector::~vector() { delete[] data_; }

void vector::push_back(size_t num) {
  if (capacity_ == size_) {
    resize(capacity_ * 2);
  }
  data_[size_] = num;
  size_++;
}

size_t vector::size() { return size_; }

int &vector::operator[](size_t idx) {
  assert(idx >= 0 && idx < size_);
  return data_[idx];
}

int vector::operator[](size_t idx) const {
  assert(idx >= 0 && idx < size_);
  return data_[idx];
}

void vector::resize(size_t new_capacity) {
  int *tmp = new int[new_capacity];
  std::copy(data_, data_ + size_, tmp);
  delete[] data_;
  data_ = tmp;
  capacity_ = new_capacity;
}

vector::iterator vector::begin() { 
  return vector::iterator(0, *this);
}

vector::iterator vector::end() {
  return vector::iterator(size_, *this);
}

// iterator

int & vector::iterator::operator*() {
  return v_[idx_];
}

vector::iterator & vector::iterator::operator++() {
  idx_++;
  return *this;
}

vector::iterator vector::iterator::operator++(int) {
  iterator tmp(*this);
  idx_++;
  return tmp;
}

bool vector::iterator::operator==(const vector::iterator & other) const {
  return &v_ == &other.v_ && idx_ == other.idx_;
}

bool vector::iterator::operator!=(const vector::iterator & other) const {
  return !(*this == other);
}
