#include "../Matrix.h"
#include "../synchronous_functions/matrix_utilities.hh"
#include <cstddef>
#include <cstdio>
#include <exception>

using std::exception;

template <typename T>
[[nodiscard]] Matrix<T> *synchronousMatrixMultiplication(Matrix<T> *matrix1, Matrix<T> *matrix2);

template <typename T>
[[nodiscard]] T dotProduct(Matrix<T> *matrix1, Matrix<T> *matrix2, size_t row, size_t column) {
  T sum = 0;
  size_t indexMatrix1 = row * matrix1->columns;
  size_t indexMatrix2 = column;

  for (unsigned int i = 0; i < matrix1->columns; i++) {
    sum += matrix1->values[indexMatrix1] * matrix2->values[indexMatrix2];
    indexMatrix1 += 1;
    indexMatrix2 += matrix2->columns;
  }

  return sum;
}

template <typename T>
[[nodiscard]] Matrix<T> *innerMatrixMultiplication(Matrix<T> *matrix1, Matrix<T> *matrix2) {
  Matrix<T> *result = allocateMatrix<T>(matrix1->rows, matrix2->columns);
  size_t index = 0;
  for (int row = 0; row < result->rows; row++) {
    for (int column = 0; column < result->columns; column++, index++) {
      result->values[index] = dotProduct(matrix1, matrix2, row, column);
    }
  }
  return result;
}

template <typename T>
[[nodiscard]] Matrix<T> *synchronousMatrixMultiplication(Matrix<T> *matrix1, Matrix<T> *matrix2) {
  if (!isMultiplicableDimensions(matrix1, matrix2))
    throw exception();
  return innerMatrixMultiplication(matrix1, matrix2);
}
