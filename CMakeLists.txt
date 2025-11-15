cmake_minimum_required(VERSION 4.0)
project(CudaExploration LANGUAGES CXX CUDA)

set(CMAKE_CUDA_STANDARD 23)

find_path(CUNIT_INCLUDE_DIR NAMES CUnit/Basic.h)
find_library(CUNIT_LIBRARY NAMES cunit)

if (NOT CUNIT_INCLUDE_DIR OR NOT CUNIT_LIBRARY)
  message(FATAL_ERROR "CUnit not found")
endif ()

add_library(CudaLib
  matrix_mul.cu
  Matrix.cuh
  synchronous_functions/synchronous_functions.cuh
)

set_target_properties(CudaLib PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

target_include_directories(CudaLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(Tests
  tests/tests_main.cu
)

target_link_libraries(Tests PRIVATE CudaLib ${CUNIT_LIBRARY})

target_include_directories(Tests PRIVATE ${CUNIT_INCLUDE_DIR})