#include "command.hpp"

// TODO:
// 1. start writing 2nd lab
// 2. finish commands in brainfuck interpreter (including '[', ']')

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
  std::string cmds;
  uint8_t data[30000] = {};
  uint8_t * ptr = data;
  while (true) {
    std::cin >> cmds;
    interpret(cmds, ptr);
  }
  return 0;
}