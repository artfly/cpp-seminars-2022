#pragma once

#include <cstdint>
#include <iostream>
#include <list>
#include <algorithm>
#include <sstream>

#include "data_it.hpp"

class Command {
  public:
    virtual void apply(data_it & it) = 0;
    virtual ~Command() {}
};

class Right: public Command {
  public:
    void apply(data_it & it) override {
      ++it;
    }
};

class Left: public Command {
  public:
    void apply(data_it & it) override {
      --it;
    }
};

class Plus: public Command {
  public:
    void apply(data_it & it) override {
      (*it)++;
    }
};

class Minus: public Command {
  public:
    void apply(data_it & it) override {
      (*it)--;
    }
};

class Write: public Command {
  public:
    void apply(data_it & it) override {
      std::cout << unsigned(*it) << std::endl;
    }
};

class Read: public Command {
  public:
    void apply(data_it & it) override {
      int number;
      std::cin >> number;
      *it = number;
    }
};

class While: public Command {
  public:
    While(const std::list<Command *> & body): body_(body) {}

    ~While() override {
      for (Command * command : body_) {
          delete command;
      }
    }

    void apply(data_it & it) override {
      while (*it != 0) {
        for (Command * command : body_) {
          command->apply(it);
        }
      }
    }
  private:
    std::list<Command *> body_;
};