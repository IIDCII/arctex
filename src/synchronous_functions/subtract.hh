#include "../Matrix.h"
#include "matrix_utilities.hh"
#include <exception>

using std::exception;

template <typename T>
[[nodiscard]] Matrix<T> *synchronousSubtraction(Matrix<T> *matrix1, Matrix<T> *matrix2);

template <typename T>
void subtractIntoResult(Matrix<T> *matrix1, Matrix<T> *matrix2, Matrix<T> *result) {
  const unsigned int matrix_size = matrix1->rows * matrix1->columns;
  for (size_t i = 0; i < matrix_size; i++) {
    result->values[i] = matrix1->values[i] - matrix2->values[i];
  }
}

template <typename T>
[[nodiscard]] Matrix<T> *synchronousSubtraction(Matrix<T> *matrix1, Matrix<T> *matrix2) {
  if (!dimensionsEqual(matrix1, matrix2))
    throw exception();
  Matrix<T> *result = allocateMatrix<T>(matrix1->rows, matrix1->columns);
  subtractIntoResult(matrix1, matrix2, result);
  return result;
}
