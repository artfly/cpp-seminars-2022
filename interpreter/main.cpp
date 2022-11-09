#include "command.hpp"
#include "interpreter.hpp"

int main(int argc, char ** argv) {
  Interpreter & i = Interpreter::get_instance();
  std::string cmds;
  while (true) {
    std::cin >> cmds;
    i.interpret(cmds.begin(), cmds.end());
  }
  return 0;
}