cmake_minimum_required(VERSION 3.10)

project(my_project)

set(CMAKE_CXX_STANDARD 17)
set(ABSL_PROPAGATE_CXX_STD ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/eff443c6ef5eb6ab598bfaae27f9427fdb4f6af7.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Process Abseil's CMake build system
#enable_testing()

add_executable(
  netdev
  netdev.cc
  main.cc
)

#target_link_libraries(
#  netdev
#  GTest::gtest_main
#)

#include(GoogleTest)
#gtest_discover_tests(eth_test)
