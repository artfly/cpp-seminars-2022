#include <cstddef>

template <class T>
class vector {
public:
    vector() : capacity_(1), size_(0), data_(new T[1]()) {}

    explicit vector(const size_t size);

    vector(const vector<T> & other);

    ~vector() { delete[] data_; }

    // adds element to the last available position,
    // resizes vector if the current capacity is reached
    void push_back(const T elem);

    size_t size() const { return this->size_; }

    void set(const T elem, size_t idx) { data_[idx] = elem; }

    T & at(const size_t idx) const { return data_[idx]; }

    vector<T> & operator=(const vector<T> & other);

private:
    T * data_;
    size_t size_;
    size_t capacity_;

    // resizes vector to given capacity
    void resize(const size_t new_capacity); 
};
