#pragma once

#include <cstddef>
#include <array>

#include "interpreter_error.hpp"

class data_it {
 public:  
    data_it() = default;

    uint8_t & operator*() {
        return *_it;
    }

    data_it & operator++() {
        if (_it == _data.end()) throw interpreter_error("out of bounds: cannot access element after last");
        ++_it;
        return *this; 
    }

    data_it & operator--() {
        if (_it == _data.begin()) throw interpreter_error("out of bounds: cannot access element before first");
        --_it;
        return *this;
    }
 private:
    data_it(data_it & other) = delete;
    data_it & operator=(data_it & other) = delete;

    static const int ARRAY_SIZE_ = 20000;

    std::array<uint8_t, ARRAY_SIZE_> _data = {};
    std::array<uint8_t, ARRAY_SIZE_>::iterator _it = _data.begin();
};