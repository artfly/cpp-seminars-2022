cmake_minimum_required(VERSION 3.12)
project(smart_ptr)

add_executable(smart_ptr smart_ptr.hpp main.cpp)

set_target_properties(
  smart_ptr
  PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
)

