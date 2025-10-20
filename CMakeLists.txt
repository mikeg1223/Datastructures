cmake_minimum_required(VERSION 3.14)
project(data_structures)

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(
  DataStructures
  INTERFACE
)

target_include_directories(
  DataStructures INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(
  DSTest
  test.cpp
)

target_link_libraries(
  DSTest PUBLIC
  GTest::gtest_main
  DataStructures
)

include(GoogleTest)
gtest_discover_tests(DSTest)
