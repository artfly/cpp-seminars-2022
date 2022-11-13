#pragma once

#include <functional>
#include <unordered_map>
#include <string>
#include <array>
#include <sstream>
#include <iostream>

#include "command.hpp"
#include "interpreter_error.hpp"
#include "data_it.hpp"

class Interpreter {

  public:
    typedef std::function<Command *(std::string::iterator &, const std::string::iterator &)> creator_t;

    static Interpreter & get_instance() {
      static Interpreter i;
      return i;
    }
  
    bool register_creator(char c, const creator_t & creator) {
      creators_[c] = creator;
      return true;
    }

    std::list<Command *> get_cmds(const std::string::iterator & begin, const std::string::iterator & end) {
      std::list<Command *> cmds;
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
        std::list<Command *> cmds = get_cmds(it, end);
        for (Command * cmd : cmds) {
          cmd->apply(it_);
          delete cmd;
        }
      } catch (interpreter_error & e) {
        std::cerr << e.what() << std::endl;
      }
    }

  private:
    Interpreter() = default;

    Interpreter(Interpreter & other) = delete;
    Interpreter & operator=(const Interpreter & other) = delete;

    std::unordered_map<char, creator_t> creators_;

    data_it it_;
};