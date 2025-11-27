#include "../src/synchronous_functions/matrix_utilities.hh"
#include "../src/synchronous_functions/subtract.hh"
#include <gtest/gtest.h>

class SynchronousSubtractionTest : public ::testing::Test {
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
  }

  void TearDown() override {
    freeMatrix(matrixA);
    freeMatrix(matrixB);
    freeMatrix(matrixC);
    freeMatrix(expected);
  }
};

TEST_F(SynchronousSubtractionTest, AddZeroMatrices) {
  constexpr int zero = 0;
  fillMatrix(matrixA, zero);
  fillMatrix(matrixB, zero);

  Matrix<int> *result = synchronousSubtraction(matrixA, matrixB);
  EXPECT_TRUE(isMatrixFilled(result, zero - zero));

  freeMatrix(result);
}

TEST_F(SynchronousSubtractionTest, AddOneMatrices) {
  constexpr int one = 1;
  fillMatrix(matrixA, one);
  fillMatrix(matrixB, one);

  Matrix<int> *result = synchronousSubtraction(matrixA, matrixB);
  EXPECT_TRUE(isMatrixFilled(result, one - one));

  freeMatrix(result);
}

TEST_F(SynchronousSubtractionTest, AddMinusOneMatrices) {
  constexpr int minusOne = 1;
  fillMatrix(matrixA, minusOne);
  fillMatrix(matrixB, minusOne);

  Matrix<int> *result = synchronousSubtraction(matrixA, matrixB);
  EXPECT_TRUE(isMatrixFilled(result, minusOne - minusOne));

  freeMatrix(result);
}

TEST_F(SynchronousSubtractionTest, AddDifferentValueMatrices) {
  constexpr int one = 1;
  constexpr int two = 2;
  fillMatrix(matrixA, one);
  fillMatrix(matrixB, two);

  Matrix<int> *result = synchronousSubtraction(matrixA, matrixB);
  EXPECT_TRUE(isMatrixFilled(result, one - two));

  freeMatrix(result);
}

TEST_F(SynchronousSubtractionTest, AddCustomValueMatrices) {
  matrixA->values[0] = 1, matrixA->values[1] = 4, matrixA->values[2] = 3, matrixA->values[3] = 5;
  matrixB->values[0] = 7, matrixB->values[1] = 8, matrixB->values[2] = 0, matrixB->values[3] = 9;
  expected->values[0] = 1 - 7, expected->values[1] = 4 - 8, expected->values[2] = 3 - 0, expected->values[3] = 5 - 9;

  Matrix<int> *result = synchronousSubtraction(matrixA, matrixB);
  EXPECT_TRUE(matrixEqual(result, expected));

  freeMatrix(result);
}

TEST_F(SynchronousSubtractionTest, AddNonSquareMatrices) {
  constexpr int one = 1, rows = 2, columns = 4;
  Matrix<int> *nonSquareA = allocateMatrix<int>(rows, columns);
  Matrix<int> *nonSquareB = allocateMatrix<int>(rows, columns);
  fillMatrix(nonSquareA, one);
  fillMatrix(nonSquareB, one);

  Matrix<int> *result = synchronousSubtraction(nonSquareA, nonSquareB);
  EXPECT_TRUE(isMatrixFilled(result, one - one));

  freeMatrix(nonSquareA);
  freeMatrix(nonSquareB);
  freeMatrix(result);
}

TEST_F(SynchronousSubtractionTest, ThrowErrorOnDifferentColumnDimension) {
  constexpr unsigned int rows = 2;
  Matrix<int> *nonSquareA = allocateMatrix<int>(rows, 10);
  Matrix<int> *nonSquareB = allocateMatrix<int>(rows, 5);

  auto errorStatement = [&]() -> void {
    auto matrixThatNeverArrives = synchronousSubtraction(nonSquareA, nonSquareB);
  };
  EXPECT_THROW(errorStatement(), exception);

  freeMatrix(nonSquareA);
  freeMatrix(nonSquareB);
}

TEST_F(SynchronousSubtractionTest, ThrowErrorOnDifferentRowDimension) {
  constexpr unsigned int columns = 2;
  Matrix<int> *nonSquareA = allocateMatrix<int>(10, columns);
  Matrix<int> *nonSquareB = allocateMatrix<int>(5, columns);

  auto errorStatement = [&]() -> void {
    auto matrixThatNeverArrives = synchronousSubtraction(nonSquareA, nonSquareB);
  };
  EXPECT_THROW(errorStatement(), exception);

  freeMatrix(nonSquareA);
  freeMatrix(nonSquareB);
}
