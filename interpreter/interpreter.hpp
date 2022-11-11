#pragma once

#include <functional>
#include <unordered_map>
#include <string>
#include <array>
#include <sstream>

#include "command.hpp"

class Interpreter {

  public:
    typedef std::function<Command *(std::string::iterator &, std::string::iterator &)> creator_t;

    static Interpreter & get_instance() {
      static Interpreter i;
      return i;
    }
  
    bool register_creator(char c, const creator_t & creator) {
      creators_[c] = creator;
      return true;
    }

    std::vector<Command *> get_cmds(const std::string::iterator & begin, const std::string::iterator & end) {
      std::vector<Command *> cmds;
      for (auto it = begin; it < end; it++) {
        auto creator_it = creators_.find(*it);
        if (creator_it == creators_.end()) {
          std::stringstream ss; 
          ss << "no such command: '" << *it << "'";
          throw interpreter_error(ss.str());
        }
        creator_t creator = (*creator_it).second;
        Command * cmd = creator(it, end);
        cmds.push_back(cmd);
      }
      return cmds;
    }

    void interpret(const std::string::iterator & begin, const std::string::iterator & end) {
      auto it = begin;
      try {
        std::vector<Command *> cmds = get_cmds(begin, end);
        for (Command * cmd : cmds) {
          cmd->apply(ptr_);
        }
      } catch (interpreter_error & e) {
        std::cerr << e.what() << std::endl;
      }
      // TODO: delete commands
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