#pragma once

template<typename T>
class shared_ptr {
public:
    // creates new shared_ptr with the same underlying raw pointer, sets counter to 1
    explicit shared_ptr(T *ptr = nullptr);

    // creates shared_ptr with the same underlying raw pointer as 'other' has, increments counter
    shared_ptr(const shared_ptr &other);

    // decrements the counter for the old raw pointer, assigns the new one from 'other'
    shared_ptr &operator=(const shared_ptr &other);

    // destructs underlying raw pointer if there are no other shared_ptr that owns it
    // otherwise decrements the counter
    ~shared_ptr();

    // releases stored pointer, replaces it with nullptr.
    // counter is decremented, but raw pointer is not deleted (even if it was the last shared_ptr).
    T *release();

    // replaces current raw pointer with a new one
    // counter is decremented, raw pointer is deleted if it was the last shared_ptr
    void reset(T *new_ptr);

    // get the underlying raw pointer. counter is not changed
    T *get();

    // dereference underlying pointer
    T & operator*();

    // returns underlying pointer in order to access one of its members
    T *operator->();

private:

    T *ptr_;
    unsigned *cnt_;
};

template<typename T>
shared_ptr<T>::shared_ptr(T *ptr): ptr_(ptr), cnt_(new unsigned(1)) {}

template<typename T>
shared_ptr<T>::shared_ptr(const shared_ptr &other): ptr_(other.ptr_), cnt_(other.cnt_) {
    (*cnt_)++;
}

template<typename T>
shared_ptr<T> &shared_ptr<T>::operator=(const shared_ptr<T> &other) {
    if (&other== this) {
        return *this;
    }
    reset(other.cnt_);
    return *this;
}

template<typename T>
shared_ptr<T>::~shared_ptr() {
    (*cnt_)--;
    if (*cnt_ == 0) {
        delete cnt_;
        delete ptr_;
    }
}

template<typename T>
T *shared_ptr<T>::release() {
    if (*cnt_ != 1) {
        // shared pointer counter is used elsewhere, cannot reuse
        (*cnt_)--;
        cnt_ = new unsigned(1);
    }
    T *old = ptr_;
    ptr_ = nullptr;
    return old;
}

template<typename T>
void shared_ptr<T>::reset(T *new_ptr) {
    if (ptr_ == new_ptr) {
        return;
    }
    if (*cnt_ == 1) {
        // can reuse counter
        delete ptr_;
    } else {
        (*cnt_)--;
        cnt_ = new unsigned(1);
    }
    ptr_ = new_ptr;
}

template<typename T>
T *shared_ptr<T>::get() {
    return ptr_;
}

template<typename T>
T & shared_ptr<T>::operator*() {
    return *ptr_;
}

template<typename T>
T *shared_ptr<T>::operator->() {
    return ptr_;
}


