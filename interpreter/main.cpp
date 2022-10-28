#include <iostream>

// TODO:
// 1. start writing 2nd lab
// 2. finish commands in brainfuck interpreter (including '[', ']')

class Command {
  public:
    virtual void apply(uint8_t * ptr) = 0;
};

class Right: public Command {
  public:
    void apply(uint8_t * ptr) override {
      std::cout << "right command!" << std::endl;
      ptr++;
    }
};

class Left: public Command {
  public:
    void apply(uint8_t * ptr) override {
      std::cout << "left command!" << std::endl;
      ptr--;
    }
};

// ...

Command * get_cmd(const char c) {
  switch (c) {
    case '>':
      return new Right();
    case '<':
      return new Left();
  }
  return nullptr;
}

void interpret(const std::string & cmds, uint8_t * ptr) {
  for (const char cmd : cmds) {
    Command * command = get_cmd(cmd);
    if (command == nullptr) {
      std::cerr << "unknown command: '" << cmd << "'" << std::endl;
      continue;
    }
    command->apply(ptr);
    delete command;

    switch (cmd) {
      case '>':
        ptr++;
        break;
      case '<':
        ptr--;
        break;
      case '+':
        (*ptr)++;
        break;
      case '-':
        (*ptr)--;
        break;
      case '.':
        std::cout << unsigned(*ptr) << std::endl;
        break;
      case ',':
        int number;
        std::cin >> number;
        *ptr = number;
        break;
      // case '[':
      // case ']':
        // TODO
        break;
      default:
        std::cerr << "unknown command: '" << cmd << "'" << std::endl;
    }
  }
}

void as_c(const std::string & cmds) {
  for (const char cmd : cmds) {
    switch (cmd) {
      case '>':
        std::cout << "ptr++;" << std::endl;
        break;
      case '<':
        std::cout << "ptr--;" << std::endl;
        break;
      default:
        std::cout << "std::cerr << \"unknown command: '\" << cmd << \"'\" << std::endl;" << std::endl;
    }
  }
}
/*

as_c():

input:
..>

output:
std::cout << unsigned(*ptr) << std::endl;
std::cout << unsigned(*ptr) << std::endl;
ptr++;

*/


int main(int argc, char ** argv) {
  // argv[1] == -p => as_c()
  // if (argc == 2) {
  //   // -p
  //   std::string cmds;
  //   while (true) {
  //     std::cin >> cmds;
  //     as_c(cmds);
  //   }
  //   return 0;
  // }
  // std::string cmds;
  uint8_t data[30000] = {};
  uint8_t * ptr = data;
  // while (true) {
  //   std::cin >> cmds;
  //   interpret(cmds, ptr);
  // }

  Left left;
  Command & c2 = left;
  c2.apply(ptr);
  Command * c3 = new Left();
  c3->apply(ptr);

  return 0;
}