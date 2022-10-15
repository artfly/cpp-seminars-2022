#include <iostream>

void interpret(const std::string & cmds, uint8_t * ptr) {
  for (const char cmd : cmds) {
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
      default:
        std::cerr << "unknown command: '" << cmd << "'" << std::endl;
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
  std::string cmds;
  uint8_t data[30000] = {};
  uint8_t * ptr = data;
  while (true) {
    std::cin >> cmds;
    interpret(cmds, ptr);
  }
  return 0;
}