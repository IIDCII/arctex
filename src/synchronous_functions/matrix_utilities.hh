#ifndef CUDAEXPLORATION_BASIC_FUNCTIONS_CUH
#define CUDAEXPLORATION_BASIC_FUNCTIONS_CUH

#include "../Matrix.h"
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <sstream>

template <typename T>
void fillMatrix(Matrix<T> *matrix, T value);

template <typename T>
bool dimensionsEqual(const Matrix<T> *matrix1, const Matrix<T> *matrix2);

template <typename T>
bool isMultiplicableDimensions(const Matrix<T> *matrix1, const Matrix<T> *matrix2);

template <typename T>
bool matrixEqual(const Matrix<T> *matrix1, const Matrix<T> *matrix2);

template <typename T>
void freeMatrix(Matrix<T> *matrix);

template <typename T>
bool isMatrixFilled(Matrix<T> *matrix, T value);

template <typename T>
std::string matrixToString(Matrix<T> *matrix);

template <typename T>
void printMatrix(Matrix<T> *matrix);

template <typename T>
std::string matrixToString(Matrix<T> *matrix) {
  std::stringstream stringStream;
  size_t index = 0;
  for (unsigned int row = 0; row < matrix->rows; row++) {
    for (unsigned int column = 0; column < matrix->columns; column++, index++) {
      stringStream << matrix->values[index] << ' ';
    }
    stringStream << '\n';
  }
  return stringStream.str();
}

template <typename T>
void printMatrix(Matrix<T> *matrix) {
  std::cout << matrixToString(matrix) << std::endl;
}

template <typename T>
void fillMatrix(Matrix<T> *matrix, T value) {
  for (size_t i = 0; i < matrix->rows * matrix->columns; i++) {
    matrix->values[i] = value;
  }
}

template <typename T>
bool dimensionsEqual(const Matrix<T> *matrix1, const Matrix<T> *matrix2) {
  return matrix1->rows == matrix2->rows && matrix1->columns == matrix2->columns;
}

template <typename T>
bool isMultiplicableDimensions(const Matrix<T> *matrix1, const Matrix<T> *matrix2) {
  return matrix1->columns == matrix2->rows;
}

namespace {
template <typename T>
bool valuesEqual(const Matrix<T> *matrix1, const Matrix<T> *matrix2) {
  const size_t matrix_size = matrix1->rows * matrix1->columns;
  for (size_t i = 0; i < matrix_size; i++) {
    if (matrix1->values[i] != matrix2->values[i])
      return false;
  }
  return true;
}
} // namespace

template <typename T>
bool matrixEqual(const Matrix<T> *matrix1, const Matrix<T> *matrix2) {
  if (matrix1 == matrix2)
    return true;
  return dimensionsEqual(matrix1, matrix2) && valuesEqual(matrix1, matrix2);
}

template <typename T>
bool isMatrixFilled(Matrix<T> *matrix, T value) {
  for (size_t i = 0; i < matrix->rows * matrix->columns; i++) {
    if (matrix->values[i] != value) {
      return false;
    }
  }
  return true;
}

template <typename T>
Matrix<T> *allocateMatrix(unsigned int rows, unsigned int columns) {
  auto *mat = static_cast<Matrix<T> *>(malloc(sizeof(Matrix<T>)));
  const size_t number_of_elements = rows * columns;
  mat->values = static_cast<T *>(malloc(number_of_elements * sizeof(T)));
  mat->rows = rows;
  mat->columns = columns;
  return mat;
}

template <typename T>
void freeMatrix(Matrix<T> *matrix) {
  free(matrix->values);
  free(matrix);
}
#endif // CUDAEXPLORATION_BASIC_FUNCTIONS_CUH
