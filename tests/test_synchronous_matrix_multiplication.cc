#include "../src/synchronous_functions/matrix_multiplication.hh"
#include "../src/synchronous_functions/matrix_utilities.hh"
#include <gtest/gtest.h>

class SynchronousMatrixMultiplicationTest : public ::testing::Test {
protected:
  static constexpr unsigned int rows = 2;
  static constexpr unsigned int columns = 2;

  Matrix<int> *matrixA;
  Matrix<int> *matrixB;
  Matrix<int> *matrixC;
  Matrix<int> *expected;

  void SetUp() override {
    matrixA = allocateMatrix<int>(rows, columns);
    matrixB = allocateMatrix<int>(rows, columns);
    matrixC = allocateMatrix<int>(rows, columns);
    expected = allocateMatrix<int>(rows, columns);
    fillMatrix(matrixA, 0);
    fillMatrix(matrixB, 0);
    fillMatrix(matrixC, 0);
    fillMatrix(expected, 0);
  }

  void TearDown() override {
    freeMatrix(matrixA);
    freeMatrix(matrixB);
    freeMatrix(matrixC);
    freeMatrix(expected);
  }
};

TEST_F(SynchronousMatrixMultiplicationTest, MultiplyZeroMatrices) {
  constexpr int zero = 0;

  fillMatrix(matrixA, zero);
  fillMatrix(matrixB, zero);
  fillMatrix(expected, zero);

  Matrix<int> *result = synchronousMatrixMultiplication(matrixA, matrixB);
  bool isEqual = matrixEqual(result, expected);
  EXPECT_TRUE(isEqual);

  freeMatrix(result);
}

TEST_F(SynchronousMatrixMultiplicationTest, MultiplySameValueMatrices) {
  constexpr int two = 2;

  fillMatrix(matrixA, two);
  fillMatrix(matrixB, two);
  fillMatrix(expected, 8);

  Matrix<int> *result = synchronousMatrixMultiplication(matrixA, matrixB);
  bool isEqual = matrixEqual(result, expected);
  EXPECT_TRUE(isEqual);

  freeMatrix(result);
}

TEST_F(SynchronousMatrixMultiplicationTest, CheckDimensionsOfSquareMatrices) {
  constexpr int zero = 0;

  fillMatrix(matrixA, zero);
  fillMatrix(matrixB, zero);

  Matrix<int> *result = synchronousMatrixMultiplication(matrixA, matrixB);
  bool isRowsCorrect = result->rows == matrixA->columns;
  bool isColumnsCorrect = result->columns == matrixB->rows;
  EXPECT_TRUE(isRowsCorrect);
  EXPECT_TRUE(isColumnsCorrect);

  freeMatrix(result);
}

TEST_F(SynchronousMatrixMultiplicationTest, CheckDimensionsOfNonSquareMatrices) {
  Matrix<int> *nonSquareMatrixA = allocateMatrix<int>(2, 5);
  Matrix<int> *nonSquareMatrixB = allocateMatrix<int>(5, 4);

  Matrix<int> *result = synchronousMatrixMultiplication(nonSquareMatrixA, nonSquareMatrixB);
  bool isRowsCorrect = result->rows == nonSquareMatrixA->rows;
  bool isColumnsCorrect = result->columns == nonSquareMatrixB->columns;

  EXPECT_TRUE(isRowsCorrect);
  EXPECT_TRUE(isColumnsCorrect);

  freeMatrix(nonSquareMatrixA);
  freeMatrix(nonSquareMatrixB);
  freeMatrix(result);
}

TEST_F(SynchronousMatrixMultiplicationTest, MultiplyDiagonalMatrices) {
  matrixA->values[0] = 2, matrixA->values[3] = 2;
  matrixB->values[0] = 3, matrixB->values[3] = 3;
  expected->values[0] = 6, expected->values[3] = 6;

  Matrix<int> *result = synchronousMatrixMultiplication(matrixA, matrixB);
  bool isEqual = matrixEqual(result, expected);
  EXPECT_TRUE(isEqual);

  freeMatrix(result);
}

TEST_F(SynchronousMatrixMultiplicationTest, ThrowErrorOnNonMatchingDimensions) {
  unsigned int dimension = 1, differentDimension = 2;
  Matrix<int> *nonSquareMatrixA = allocateMatrix<int>(1, dimension);
  Matrix<int> *nonSquareMatrixB = allocateMatrix<int>(differentDimension, 1);

  auto errorStatement = [&]() -> void {
    auto matrixThatNeverArrives = synchronousMatrixMultiplication(nonSquareMatrixA, nonSquareMatrixB);
  };
  EXPECT_THROW(errorStatement(), exception);

  freeMatrix(nonSquareMatrixA);
  freeMatrix(nonSquareMatrixB);
}
