#pragma once
#include <cstdint>
#include <iostream>
#include <vector>

class Command {
  public:
    virtual void apply(uint8_t * ptr) = 0;
};

class Right: public Command {
  public:
    void apply(uint8_t * ptr) override {
      ptr++;
    }
};

class Left: public Command {
  public:
    void apply(uint8_t * ptr) override {
      ptr--;
    }
};

class Plus: public Command {
  public:
    void apply(uint8_t * ptr) override {
      *ptr++;
    }
};

class Minus: public Command {
  public:
    void apply(uint8_t * ptr) override {
      *ptr--;
    }
};

class Write: public Command {
  public:
    void apply(uint8_t * ptr) override {
      std::cout << (*ptr) << std::endl;
    }
};

class Read: public Command {
  public:
    void apply(uint8_t * ptr) override {
      int number;
      std::cin >> number;
      *ptr = number;
    }
};

class While: public Command {
  public:
    While(std::vector<Command *> & body): body_(body) {}
    void apply(uint8_t * ptr) override {
      while (*ptr != 0) {
        for (Command * command : body_) {
          command->apply(ptr);
        }
      }
    }
  private:
    std::vector<Command *> body_;
};

Command * get_cmd(std::string::iterator & it, std::string::iterator & end) {
  if (*it == '[') {
    std::vector<Command *> body;
    while (it != end && *it != ']') {
      it++;
      Command * cmd = get_cmd(it, end);
      body.push_back(cmd);
    }
    if (it == end) {
      // vse ploho!!!!
      return nullptr;
    }
    return new While(body);
  }

  switch (*it) {
    case '>':
      return new Right();
    case '<':
      return new Left();
  }
  return nullptr;
}

// '[' -> while_cmd
// '.' -> write_cmd
Command * while_cmd(std::string::iterator & it, std::string::iterator & end) {
  
    std::vector<Command *> body;
    while (it != end && *it != ']') {
      it++;
      Command * cmd = get_cmd(it, end);
      body.push_back(cmd);
    }
    if (it == end) {
      // vse ploho!!!!
      return nullptr;
    }
    return new While(body);
}