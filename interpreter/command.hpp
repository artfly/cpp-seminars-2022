#pragma once
#include <cstdint>
#include <iostream>

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