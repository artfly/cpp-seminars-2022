#include "command.hpp"
#include <unordered_map>
#include <array>
// TODO:
// 1. start writing 2nd lab
// 2. finish commands in brainfuck interpreter (including '[', ']')

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

    void interpret(std::string::iterator & it, std::string::iterator & end) {
      while (it != end) {
        creator_t creator = creators_[*it];
        Command * command = creator(it, end);
        command->apply(ptr_);
        it++;
      }
    }
  private:
    // TODO: init ptr_
    Interpreter() {}
    Interpreter(Interpreter & other) = delete;
    std::unordered_map<char, creator_t> creators_;
    static const int ARRAY_SIZE_ = 20000;
    std::array<uint8_t, ARRAY_SIZE_> data_; 
    uint8_t * ptr_;
};

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

void interpret(std::string & cmds, uint8_t * ptr) {
  auto it = cmds.begin();
  while (it != cmds.end()) {
    Command * command = get_cmd(it, cmds.end());
    if (command == nullptr) {
      std::cerr << "unknown command: '" << cmd << "'" << std::endl;
      continue;
    }
    command->apply(ptr);
    it++;
  }
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
  Interpreter & i = Interpreter::get_instance();
  std::string cmds;
  while (true) {
    std::cin >> cmds;
    i.interpret(cmds.begin(), cmds.end());
  }


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