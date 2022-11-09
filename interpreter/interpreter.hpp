#pragma once

#include <functional>
#include <unordered_map>
#include <string>
#include <array>

#include "command.hpp"

class Interpreter {

  public:
    typedef std::function<Command *(std::string::iterator, std::string::iterator)> creator_t;

    static Interpreter & get_instance() {
      static Interpreter i;
      return i;
    }
  
    bool register_creator(char c, creator_t & creator) {
      creators_[c] = creator;
      return true;
    }

    void interpret(const std::string::iterator & begin, const std::string::iterator & end) {
      auto it = begin;
      while (it != end) {
        creator_t creator = creators_[*it];
        Command * command = creator(it, end);
        command->apply(ptr_);
        it++;
      }
    }

  private:
    Interpreter() = default;

    Interpreter(Interpreter & other) = delete;
    Interpreter & operator=(const Interpreter & other) = delete;

    std::unordered_map<char, creator_t> creators_;

    static const int ARRAY_SIZE_ = 20000;
    std::array<uint8_t, ARRAY_SIZE_> data_; 

    uint8_t * ptr_;
};