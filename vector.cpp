#include "vector.hpp"

template <class T>
vector<T>::vector(const vector<T> & other) {
    data_ = new T[other.capacity_]();
    capacity_ = other.capacity_;
    size_ = other.size();
    for (size_t i = 0; i < other.size(); i++) {
        data_[i] = other.at(i);
    }
}

template <class T>
vector<T>::vector(const size_t size) : size_(size) {
    size_t capacity = size_t(1) << (sizeof(size_t) * 8 - 1);
    while (!(capacity & size) && capacity) {
        capacity >>= 1;
    }
    capacity <<= 1;
    capacity_ = capacity;
    data_ = new T[capacity]();
}

template <class T>
void vector<T>::push_back(const T elem) {
    if (size_ == capacity_) resize(2 * capacity_);
    data_[size_] = elem;
    size_++;
}

template <class T>
vector<T> & vector<T>::operator=(const vector<T> & other) {
    if (size_ > 0) {
        delete[] data_;
    }
    data_ = new T[other.capacity_]();
    capacity_ = other.capacity_;
    size_ = other.size_;
    for (size_t i = 0; i < other.size(); i++) {
        data_[i] = other.at(i);
    }
    return *this;
}

template <class T>
void vector<T>::resize(const size_t new_capacity) {
    if (new_capacity <= capacity_) return;

    T * new_data = new T[new_capacity]();
    for (size_t i = 0; i < size_; i++) {
        new_data[i] = data_[i];
    }
    capacity_ = new_capacity;
    delete[] data_;
    data_ = new_data;

}
