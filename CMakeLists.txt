cmake_minimum_required(VERSION 3.22.1)
project(CudaExploration LANGUAGES CXX CUDA)

set(CMAKE_CUDA_ARCHITECTURES 61)
set(CMAKE_CUDA_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_library(CudaLib
  src/Matrix.h
  src/synchronous_functions/matrix_utilities.hh
  src/synchronous_functions/add.hh
  src/synchronous_functions/subtract.hh
  src/synchronous_functions/multiply.hh
  src/synchronous_functions/divide.hh
  src/matrix_mul.cu
)

set_target_properties(CudaLib PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

target_include_directories(CudaLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(Tests
  tests/test_synchronous_addition.cc
  tests/test_synchronous_subtraction.cc
  tests/test_synchronous_division.cc
  tests/test_synchronous_multiplication.cc
  tests/test_synchronous_matrix_multiplication.cc
  tests/test_synchronous_matrix_utilities.cc
)

target_link_libraries(Tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(Tests)
