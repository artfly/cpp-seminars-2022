#include "command.hpp"
#include "interpreter.hpp"
#include "interpreter_error.hpp"

namespace {

  Command * add_creator(std::string::iterator & it, const std::string::iterator & end) {
      return new Plus();
  }

  bool add_cmd = Interpreter::get_instance().register_creator('+', add_creator);

  Command * sub_creator(std::string::iterator & it, const std::string::iterator & end) {
      return new Minus();
  }

  bool sub_cmd = Interpreter::get_instance().register_creator('-', sub_creator);

  Command * right_creator(std::string::iterator & it, const std::string::iterator & end) {
      return new Right();
  }

  bool right_cmd = Interpreter::get_instance().register_creator('>', right_creator);

  Command * left_creator(std::string::iterator & it, const std::string::iterator & end) {
      return new Left();
  }

  bool left_cmd = Interpreter::get_instance().register_creator('<', left_creator);

  Command * write_creator(std::string::iterator & it, const std::string::iterator & end) {
      return new Write();
  }

  bool write_cmd = Interpreter::get_instance().register_creator('.', write_creator);

  Command * read_creator(std::string::iterator & it, const std::string::iterator & end) {
      return new Read();
  }

  bool read_cmd = Interpreter::get_instance().register_creator(',', read_creator);

  Command * while_creator(std::string::iterator & it, const std::string::iterator & end) {
    auto cl_bracket_it = std::find_if(it, end, [](char c) { return c == ']'; });
    if (cl_bracket_it == end) {
      throw interpreter_error("no closing brace for 'while' loop");
    }
    it++;
    std::list<Command *> body = Interpreter::get_instance().get_cmds(it, cl_bracket_it);
    it = cl_bracket_it;
    return new While(body);
  }

  bool while_cmd = Interpreter::get_instance().register_creator('[', while_creator);
}