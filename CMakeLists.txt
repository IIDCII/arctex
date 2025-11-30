cmake_minimum_required(VERSION 3.22.1)
project(CudaExploration LANGUAGES CXX CUDA)

set(CMAKE_CUDA_ARCHITECTURES 61)
set(CMAKE_CUDA_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_path(CUNIT_INCLUDE_DIR NAMES CUnit/Basic.h)
find_library(CUNIT_LIBRARY NAMES cunit)

if(NOT CUNIT_INCLUDE_DIR OR NOT CUNIT_LIBRARY)
  message(FATAL_ERROR "CUnit not found")
endif()

add_library(CudaLib
    src/Matrix.cuh
    src/synchronous_functions/synchronous_functions.cuh
    src/matrix_mul.cu
)

set_target_properties(CudaLib PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

target_include_directories(CudaLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(Tests
        tests/tests.cu
)

target_link_libraries(Tests PRIVATE CudaLib ${CUNIT_LIBRARY})

target_include_directories(Tests PRIVATE ${CUNIT_INCLUDE_DIR})
