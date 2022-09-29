#include "vector.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>

vector::vector(int capacity)
    : capacity_(capacity), size_(0), data_(new int[capacity]) {}

vector::vector(vector &other)
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

void vector::push_back(int num) {
  if (capacity_ == size_) {
    resize(capacity_ * 2);
  }
  data_[size_] = num;
  size_++;
}

int vector::size() { return this->size_; }

int &vector::operator[](size_t idx) {
  // TODO
}

void vector::resize(int new_capacity) {
  int *tmp = new int[new_capacity];
  std::copy(data_, data_ + size_, tmp);
  delete[] data_;
  data_ = tmp;
  capacity_ = new_capacity;
}

int main(int argc, char **argv) { vector v; }