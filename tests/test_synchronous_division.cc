#include "../src/synchronous_functions/divide.hh"
#include "../src/synchronous_functions/matrix_utilities.hh"
#include <cstddef>
#include <gtest/gtest.h>
#include <stdexcept>

class SynchronousDivisionTest : public ::testing::Test {
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

TEST_F(SynchronousDivisionTest, DivideOneMatrices) {
  constexpr int one = 1;
  fillMatrix(matrixA, one);
  fillMatrix(matrixB, one);
  fillMatrix(expected, one / one);

  Matrix<int> *result = synchronousDivision(matrixA, matrixB);
  bool isEqual = matrixEqual(result, expected);
  EXPECT_TRUE(isEqual);

  freeMatrix(result);
}

TEST_F(SynchronousDivisionTest, DivideMinusOneMatrices) {
  constexpr int minusOne = 1;
  fillMatrix(matrixA, minusOne);
  fillMatrix(matrixB, minusOne);
  fillMatrix(expected, minusOne / minusOne);

  Matrix<int> *result = synchronousDivision(matrixA, matrixB);
  bool isEqual = matrixEqual(result, expected);
  EXPECT_TRUE(isEqual);

  freeMatrix(result);
}

TEST_F(SynchronousDivisionTest, DivideDifferentValueMatrices) {
  constexpr int one = 1;
  constexpr int two = 2;
  fillMatrix(matrixA, one);
  fillMatrix(matrixB, two);
  fillMatrix(expected, one / two);

  Matrix<int> *result = synchronousDivision(matrixA, matrixB);
  bool isEqual = matrixEqual(result, expected);
  EXPECT_TRUE(isEqual);

  freeMatrix(result);
}

TEST_F(SynchronousDivisionTest, DivideCustomValueMatrices) {
  matrixA->values[0] = 1, matrixA->values[1] = 4, matrixA->values[2] = 3, matrixA->values[3] = 5;
  matrixB->values[0] = 7, matrixB->values[1] = 8, matrixB->values[2] = 1, matrixB->values[3] = 9;

  for (size_t i = 0; i < 4; i++) {
    expected->values[i] = matrixA->values[i] / matrixB->values[i];
  }

  Matrix<int> *result = synchronousDivision(matrixA, matrixB);
  bool isEqual = matrixEqual(result, expected);
  EXPECT_TRUE(isEqual);

  freeMatrix(result);
}

TEST_F(SynchronousDivisionTest, DivideNonSquareMatrices) {
  constexpr int one = 1, rows = 2, columns = 4;
  Matrix<int> *nonSquareA = allocateMatrix<int>(rows, columns);
  fillMatrix(nonSquareA, one);
  Matrix<int> *nonSquareB = allocateMatrix<int>(rows, columns);
  fillMatrix(nonSquareB, one);
  Matrix<int> *nonSquareExpected = allocateMatrix<int>(rows, columns);
  fillMatrix(nonSquareExpected, one / one);

  Matrix<int> *result = synchronousDivision(nonSquareA, nonSquareB);
  bool isEqual = matrixEqual(result, nonSquareExpected);
  EXPECT_TRUE(isEqual);

  freeMatrix(nonSquareA);
  freeMatrix(nonSquareB);
  freeMatrix(nonSquareExpected);
  freeMatrix(result);
}

TEST_F(SynchronousDivisionTest, divisionByZeroThrowsError) {
  constexpr int zero = 0;

  fillMatrix(matrixA, zero);
  fillMatrix(matrixB, zero);

  auto errorStatement = [&]() -> void { auto matrixThatNeverArrives = synchronousDivision(matrixA, matrixB); };
  EXPECT_THROW(errorStatement(), std::runtime_error);
}

TEST_F(SynchronousDivisionTest, ThrowErrorOnDifferentColumnDimension) {
  constexpr unsigned int rows = 2;
  Matrix<int> *nonSquareA = allocateMatrix<int>(rows, 10);
  Matrix<int> *nonSquareB = allocateMatrix<int>(rows, 5);

  auto errorStatement = [&]() -> void { auto matrixThatNeverArrives = synchronousDivision(nonSquareA, nonSquareB); };
  EXPECT_THROW(errorStatement(), exception);

  freeMatrix(nonSquareA);
  freeMatrix(nonSquareB);
}

TEST_F(SynchronousDivisionTest, ThrowErrorOnDifferentRowDimension) {
  constexpr unsigned int columns = 2;
  Matrix<int> *nonSquareA = allocateMatrix<int>(10, columns);
  Matrix<int> *nonSquareB = allocateMatrix<int>(5, columns);

  auto errorStatement = [&]() -> void { auto matrixThatNeverArrives = synchronousDivision(nonSquareA, nonSquareB); };
  EXPECT_THROW(errorStatement(), exception);

  freeMatrix(nonSquareA);
  freeMatrix(nonSquareB);
}
