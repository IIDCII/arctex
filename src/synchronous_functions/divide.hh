#include "../Matrix.h"
#include "../synchronous_functions/matrix_utilities.hh"
#include <exception>
#include <stdexcept>

using std::exception;

template <typename T>
[[nodiscard]] Matrix<T> *synchronousDivision(Matrix<T> *matrix1, Matrix<T> *matrix2);

template <typename T>
void divideIntoResult(Matrix<T> *matrix1, Matrix<T> *matrix2, Matrix<T> *result) {
  const unsigned int matrix_size = matrix1->rows * matrix1->columns;
  for (size_t i = 0; i < matrix_size; i++) {
    if (matrix2->values[i] == 0) {
      throw std::runtime_error("Division by Zero");
    }
    result->values[i] = matrix1->values[i] / matrix2->values[i];
  }
}

template <typename T>
[[nodiscard]] Matrix<T> *synchronousDivision(Matrix<T> *matrix1, Matrix<T> *matrix2) {
  if (!dimensionsEqual(matrix1, matrix2))
    throw exception();
  Matrix<T> *result = allocateMatrix<T>(matrix1->rows, matrix1->columns);
  divideIntoResult(matrix1, matrix2, result);
  return result;
}
