#include "../src/synchronous_functions/matrix_utilities.hh"
#include "../src/synchronous_functions/multiply.hh"
#include <gtest/gtest.h>

class SynchronousMultiplicationTest : public ::testing::Test {
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

TEST_F(SynchronousMultiplicationTest, MultiplyZeroMatrices) {
  constexpr int zero = 0;

  fillMatrix(matrixA, zero);
  fillMatrix(matrixB, zero);
  fillMatrix(expected, zero * zero);

  Matrix<int> *result = synchronousMultiplication(matrixA, matrixB);
  bool isEqual = matrixEqual(result, expected);
  EXPECT_TRUE(isEqual);

  freeMatrix(result);
}

TEST_F(SynchronousMultiplicationTest, MultiplyOneMatrices) {
  constexpr int one = 1;
  fillMatrix(matrixA, one);
  fillMatrix(matrixB, one);
  fillMatrix(expected, one * one);

  Matrix<int> *result = synchronousMultiplication(matrixA, matrixB);
  bool isEqual = matrixEqual(result, expected);
  EXPECT_TRUE(isEqual);

  freeMatrix(result);
}

TEST_F(SynchronousMultiplicationTest, MultiplyMinusOneMatrices) {
  constexpr int minusOne = 1;
  fillMatrix(matrixA, minusOne);
  fillMatrix(matrixB, minusOne);
  fillMatrix(expected, minusOne * minusOne);

  Matrix<int> *result = synchronousMultiplication(matrixA, matrixB);
  bool isEqual = matrixEqual(result, expected);
  EXPECT_TRUE(isEqual);

  freeMatrix(result);
}

TEST_F(SynchronousMultiplicationTest, MultiplyDifferentValueMatrices) {
  constexpr int one = 1;
  constexpr int two = 2;
  fillMatrix(matrixA, one);
  fillMatrix(matrixB, two);
  fillMatrix(expected, one * two);

  Matrix<int> *result = synchronousMultiplication(matrixA, matrixB);
  bool isEqual = matrixEqual(result, expected);
  EXPECT_TRUE(isEqual);

  freeMatrix(result);
}

TEST_F(SynchronousMultiplicationTest, MultiplyCustomValueMatrices) {
  matrixA->values[0] = 1, matrixA->values[1] = 4, matrixA->values[2] = 3, matrixA->values[3] = 5;
  matrixB->values[0] = 7, matrixB->values[1] = 8, matrixB->values[2] = 0, matrixB->values[3] = 9;

  for (size_t i = 0; i < 4; i++) {
    expected->values[i] = matrixA->values[i] * matrixB->values[i];
  }

  Matrix<int> *result = synchronousMultiplication(matrixA, matrixB);
  bool isEqual = matrixEqual(result, expected);
  EXPECT_TRUE(isEqual);

  freeMatrix(result);
}

TEST_F(SynchronousMultiplicationTest, MultiplyNonSquareMatrices) {
  constexpr int one = 1, rows = 2, columns = 4;
  Matrix<int> *nonSquareA = allocateMatrix<int>(rows, columns);
  fillMatrix(nonSquareA, one);
  Matrix<int> *nonSquareB = allocateMatrix<int>(rows, columns);
  fillMatrix(nonSquareB, one);
  Matrix<int> *nonSquareExpected = allocateMatrix<int>(rows, columns);
  fillMatrix(nonSquareExpected, one * one);

  Matrix<int> *result = synchronousMultiplication(nonSquareA, nonSquareB);
  bool isEqual = matrixEqual(result, nonSquareExpected);
  EXPECT_TRUE(isEqual);

  freeMatrix(nonSquareA);
  freeMatrix(nonSquareB);
  freeMatrix(nonSquareExpected);
  freeMatrix(result);
}

TEST_F(SynchronousMultiplicationTest, ThrowErrorOnDifferentColumnDimension) {
  constexpr unsigned int rows = 2;
  Matrix<int> *nonSquareA = allocateMatrix<int>(rows, 10);
  Matrix<int> *nonSquareB = allocateMatrix<int>(rows, 5);

  auto errorStatement = [&]() -> void {
    auto matrixThatNeverArrives = synchronousMultiplication(nonSquareA, nonSquareB);
  };
  EXPECT_THROW(errorStatement(), exception);

  freeMatrix(nonSquareA);
  freeMatrix(nonSquareB);
}

TEST_F(SynchronousMultiplicationTest, ThrowErrorOnDifferentRowDimension) {
  constexpr unsigned int columns = 2;
  Matrix<int> *nonSquareA = allocateMatrix<int>(10, columns);
  Matrix<int> *nonSquareB = allocateMatrix<int>(5, columns);

  auto errorStatement = [&]() -> void {
    auto matrixThatNeverArrives = synchronousMultiplication(nonSquareA, nonSquareB);
  };
  EXPECT_THROW(errorStatement(), exception);

  freeMatrix(nonSquareA);
  freeMatrix(nonSquareB);
}

TEST_F(SynchronousMultiplicationTest, MultiplyIsAssociative) {
  fillMatrix(matrixA, 1);
  fillMatrix(matrixB, 2);

  Matrix<int> *ATimesB = synchronousMultiplication(matrixA, matrixB);
  Matrix<int> *BTimesA = synchronousMultiplication(matrixB, matrixA);
  bool isEqual = matrixEqual(ATimesB, BTimesA);
  EXPECT_TRUE(isEqual);

  freeMatrix(ATimesB);
  freeMatrix(BTimesA);
}

Matrix<int> *leftCommutativeMultiplication(Matrix<int> *A, Matrix<int> *B, Matrix<int> *C) {
  Matrix<int> *ATimesB = synchronousMultiplication(A, B);
  Matrix<int> *result = synchronousMultiplication(ATimesB, C);
  freeMatrix(ATimesB);
  return result;
}

Matrix<int> *rightCommutativeMultiplication(Matrix<int> *A, Matrix<int> *B, Matrix<int> *C) {
  Matrix<int> *BTimesC = synchronousMultiplication(B, C);
  Matrix<int> *result = synchronousMultiplication(A, BTimesC);
  freeMatrix(BTimesC);
  return result;
}

TEST_F(SynchronousMultiplicationTest, MultiplyIsCommutative) {
  fillMatrix(matrixA, 1);
  fillMatrix(matrixB, 2);
  fillMatrix(matrixC, 3);

  Matrix<int> *leftCommutative = leftCommutativeMultiplication(matrixA, matrixB, matrixC);
  Matrix<int> *rightCommutative = rightCommutativeMultiplication(matrixA, matrixB, matrixC);

  bool isEqual = matrixEqual(leftCommutative, rightCommutative);
  EXPECT_TRUE(isEqual);

  freeMatrix(leftCommutative);
  freeMatrix(rightCommutative);
}
