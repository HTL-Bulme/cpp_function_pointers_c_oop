cmake_minimum_required(VERSION 3.18)
cmake_policy(SET CMP0048 NEW)
project(cpp_c_strings VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion")


include(CTest)
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.5.1 # or a later release
)
FetchContent_MakeAvailable(Catch2)

set(CPP_SRCS  # all non-main source files
  create_arrays.cpp
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

add_executable(main main.cpp create_arrays.cpp int_array.cpp)
