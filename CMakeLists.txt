cmake_minimum_required(VERSION 3.18)
cmake_policy(SET CMP0048 NEW)
project(cpp_function_pointers_oop VERSION 0.1)

include(common.cmake)

set(CPP_SRCS  # all non-main source files
  int_array.cpp
)

foreach(sourcefile ${CPP_SRCS})
  string(REPLACE ".cpp" "_test.cpp" testfile ${sourcefile})
  string(REPLACE ".cpp" "" testexecutable ${testfile})
  message(STATUS "${sourcefile} + ${testfile} => ${testexecutable}")
  add_executable(${testexecutable} ${sourcefile} ${testfile})
  target_link_libraries(${testexecutable} PRIVATE Catch2::Catch2WithMain)
  add_test(NAME ${testexecutable}
           COMMAND ${testexecutable})
endforeach()

add_executable(main main.cpp int_array.cpp)
