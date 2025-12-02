#include "../src/synchronous_functions/add.hh"
#include "../src/synchronous_functions/matrix_utilities.hh"
#include <gtest/gtest.h>

class SynchronousAdditionTest : public ::testing::Test {
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

TEST_F(SynchronousAdditionTest, AddZeroMatrices) {
  constexpr int zero = 0;

  fillMatrix(matrixA, zero);
  fillMatrix(matrixB, zero);
  fillMatrix(expected, zero);

  Matrix<int> *result = synchronousAddition(matrixA, matrixB);
  bool isEqual = matrixEqual(result, expected);
  EXPECT_TRUE(isEqual);

  freeMatrix(result);
}

TEST_F(SynchronousAdditionTest, AddOneMatrices) {
  constexpr int one = 1;
  fillMatrix(matrixA, one);
  fillMatrix(matrixB, one);
  fillMatrix(expected, one + one);

  Matrix<int> *result = synchronousAddition(matrixA, matrixB);
  bool isEqual = matrixEqual(result, expected);
  EXPECT_TRUE(isEqual);

  freeMatrix(result);
}

TEST_F(SynchronousAdditionTest, AddMinusOneMatrices) {
  constexpr int minusOne = 1;
  fillMatrix(matrixA, minusOne);
  fillMatrix(matrixB, minusOne);
  fillMatrix(expected, minusOne + minusOne);

  Matrix<int> *result = synchronousAddition(matrixA, matrixB);
  bool isEqual = matrixEqual(result, expected);
  EXPECT_TRUE(isEqual);

  freeMatrix(result);
}

TEST_F(SynchronousAdditionTest, AddDifferentValueMatrices) {
  constexpr int one = 1;
  constexpr int two = 2;
  fillMatrix(matrixA, one);
  fillMatrix(matrixB, two);
  fillMatrix(expected, one + two);

  Matrix<int> *result = synchronousAddition(matrixA, matrixB);
  bool isEqual = matrixEqual(result, expected);
  EXPECT_TRUE(isEqual);

  freeMatrix(result);
}

TEST_F(SynchronousAdditionTest, AddCustomValueMatrices) {
  matrixA->values[0] = 1, matrixA->values[1] = 4, matrixA->values[2] = 3, matrixA->values[3] = 5;
  matrixB->values[0] = 7, matrixB->values[1] = 8, matrixB->values[2] = 0, matrixB->values[3] = 9;
  expected->values[0] = 1 + 7, expected->values[1] = 4 + 8, expected->values[2] = 3 + 0, expected->values[3] = 5 + 9;

  Matrix<int> *result = synchronousAddition(matrixA, matrixB);
  bool isEqual = matrixEqual(result, expected);
  EXPECT_TRUE(isEqual);

  freeMatrix(result);
}
TEST_F(SynchronousAdditionTest, AddNonSquareMatrices) {
  constexpr int one = 1, rows = 2, columns = 4;
  Matrix<int> *nonSquareA = allocateMatrix<int>(rows, columns);
  fillMatrix(nonSquareA, one);
  Matrix<int> *nonSquareB = allocateMatrix<int>(rows, columns);
  fillMatrix(nonSquareB, one);
  Matrix<int> *nonSquareExpected = allocateMatrix<int>(rows, columns);
  fillMatrix(nonSquareExpected, one + one);

  Matrix<int> *result = synchronousAddition(nonSquareA, nonSquareB);
  bool isEqual = matrixEqual(result, nonSquareExpected);
  EXPECT_TRUE(isEqual);

  freeMatrix(nonSquareA);
  freeMatrix(nonSquareB);
  freeMatrix(nonSquareExpected);
  freeMatrix(result);
}

TEST_F(SynchronousAdditionTest, ThrowErrorOnDifferentColumnDimension) {
  constexpr unsigned int rows = 2;
  Matrix<int> *nonSquareA = allocateMatrix<int>(rows, 10);
  Matrix<int> *nonSquareB = allocateMatrix<int>(rows, 5);

  auto errorStatement = [&]() -> void { auto matrixThatNeverArrives = synchronousAddition(nonSquareA, nonSquareB); };
  EXPECT_THROW(errorStatement(), exception);

  freeMatrix(nonSquareA);
  freeMatrix(nonSquareB);
}

TEST_F(SynchronousAdditionTest, ThrowErrorOnDifferentRowDimension) {
  constexpr unsigned int columns = 2;
  Matrix<int> *nonSquareA = allocateMatrix<int>(10, columns);
  Matrix<int> *nonSquareB = allocateMatrix<int>(5, columns);

  auto errorStatement = [&]() -> void { auto matrixThatNeverArrives = synchronousAddition(nonSquareA, nonSquareB); };
  EXPECT_THROW(errorStatement(), exception);

  freeMatrix(nonSquareA);
  freeMatrix(nonSquareB);
}

TEST_F(SynchronousAdditionTest, AddIsAssociative) {
  fillMatrix(matrixA, 1);
  fillMatrix(matrixB, 2);

  Matrix<int> *APlusB = synchronousAddition(matrixA, matrixB);
  Matrix<int> *BPlusA = synchronousAddition(matrixB, matrixA);
  bool isEqual = matrixEqual(APlusB, BPlusA);
  EXPECT_TRUE(isEqual);

  freeMatrix(APlusB);
  freeMatrix(BPlusA);
}

Matrix<int> *leftCommutativeAddition(Matrix<int> *A, Matrix<int> *B, Matrix<int> *C) {
  Matrix<int> *APlusB = synchronousAddition(A, B);
  Matrix<int> *result = synchronousAddition(APlusB, C);
  freeMatrix(APlusB);
  return result;
}

Matrix<int> *rightCommutativeAddition(Matrix<int> *A, Matrix<int> *B, Matrix<int> *C) {
  Matrix<int> *BPlusC = synchronousAddition(B, C);
  Matrix<int> *result = synchronousAddition(A, BPlusC);
  freeMatrix(BPlusC);
  return result;
}

TEST_F(SynchronousAdditionTest, AddIsCommutative) {
  fillMatrix(matrixA, 1);
  fillMatrix(matrixB, 2);
  fillMatrix(matrixC, 3);

  Matrix<int> *leftCommutative = leftCommutativeAddition(matrixA, matrixB, matrixC);
  Matrix<int> *rightCommutative = rightCommutativeAddition(matrixA, matrixB, matrixC);

  bool isEqual = matrixEqual(leftCommutative, rightCommutative);
  EXPECT_TRUE(isEqual);

  freeMatrix(leftCommutative);
  freeMatrix(rightCommutative);
}
