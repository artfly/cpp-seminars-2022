#include "command.hpp"
#include "interpreter.hpp"

namespace {

  Command * while_cmd(std::string::iterator & it, std::string::iterator & end) {
    auto cl_bracket_it = std::find_if(it, end, [](char c) { return c == ']'; });
    if (cl_bracket_it == end) {
      throw interpreter_error("no closing brace for 'while' loop");
    }
    it++;
    std::vector<Command *> body = Interpreter::get_instance().get_cmds(it, cl_bracket_it);
    it = cl_bracket_it;
    return new While(body);
  }

  bool while_creator = Interpreter::get_instance().register_creator('[', while_cmd);

  // other commands...
}