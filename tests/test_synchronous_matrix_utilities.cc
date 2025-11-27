#include "../src/synchronous_functions/add.hh"
#include "../src/synchronous_functions/matrix_utilities.hh"
#include <gtest/gtest.h>

TEST(MatrixUtilities, FillTrivialMatrix) {
  constexpr int matrixSize = 0, value = 3;
  Matrix<int> *matrix = allocateMatrix<int>(matrixSize, matrixSize);

  fillMatrix(matrix, value);
  EXPECT_TRUE(isMatrixFilled(matrix, value));

  freeMatrix(matrix);
};

TEST(MatrixUtilities, FillSquareMatrix) {
  constexpr int matrixSize = 2, value = 3;
  Matrix<int> *matrix = allocateMatrix<int>(matrixSize, matrixSize);

  fillMatrix(matrix, value);
  EXPECT_TRUE(isMatrixFilled(matrix, value));

  freeMatrix(matrix);
}

TEST(MatrixUtilities, FillNonSquareMatrix) {
  constexpr int rows = 2, columns = 3, value = 3;
  Matrix<int> *matrix = allocateMatrix<int>(rows, columns);
  fillMatrix(matrix, value);

  EXPECT_TRUE(isMatrixFilled(matrix, value));

  freeMatrix(matrix);
};

TEST(MatrixUtilities, EqualityOfTrivialMatrices) {
  constexpr int matrixSize = 0;
  Matrix<int> *matrixA = allocateMatrix<int>(matrixSize, matrixSize);
  Matrix<int> *matrixB = allocateMatrix<int>(matrixSize, matrixSize);

  EXPECT_TRUE(matrixEqual(matrixA, matrixB));

  freeMatrix(matrixA);
  freeMatrix(matrixB);
};

TEST(MatrixUtilities, EqualityOfSquareMatrices) {
  constexpr int matrixSize = 2, value = 1;
  Matrix<int> *matrixA = allocateMatrix<int>(matrixSize, matrixSize);
  Matrix<int> *matrixB = allocateMatrix<int>(matrixSize, matrixSize);
  fillMatrix(matrixA, value);
  fillMatrix(matrixB, value);

  EXPECT_TRUE(matrixEqual(matrixA, matrixB));

  freeMatrix(matrixA);
  freeMatrix(matrixB);
};

TEST(MatrixUtilities, EqualityOfNonSquareMatrices) {
  constexpr int rows = 2, columns = 4, value = 1;
  Matrix<int> *matrixA = allocateMatrix<int>(rows, columns);
  Matrix<int> *matrixB = allocateMatrix<int>(rows, columns);
  fillMatrix(matrixA, value);
  fillMatrix(matrixB, value);

  EXPECT_TRUE(matrixEqual(matrixA, matrixB));

  freeMatrix(matrixA);
  freeMatrix(matrixB);
};

TEST(MatrixUtilities, EqualityOfDifferentRowDimensionMatrices) {
  constexpr int columns = 2, value = 1;
  Matrix<int> *matrixA = allocateMatrix<int>(10, columns);
  Matrix<int> *matrixB = allocateMatrix<int>(5, columns);
  fillMatrix(matrixA, value);
  fillMatrix(matrixB, value);

  EXPECT_FALSE(matrixEqual(matrixA, matrixB));

  freeMatrix(matrixA);
  freeMatrix(matrixB);
}

TEST(MatrixUtilities, EqualityIsReflexive) {
  Matrix<int> *matrixA = allocateMatrix<int>(5, 5);
  fillMatrix(matrixA, 1);

  EXPECT_TRUE(matrixEqual(matrixA, matrixA));

  freeMatrix(matrixA);
};

TEST(MatrixUtilities, EqualityIsSymmetric) {
  constexpr int rows = 5, columns = 5, value = 1;
  Matrix<int> *matrixA = allocateMatrix<int>(rows, columns);
  Matrix<int> *matrixB = allocateMatrix<int>(rows, columns);
  fillMatrix(matrixA, value);
  fillMatrix(matrixB, value);

  EXPECT_TRUE(matrixEqual(matrixA, matrixB));
  EXPECT_TRUE(matrixEqual(matrixB, matrixA));

  freeMatrix(matrixA);
  freeMatrix(matrixB);
};

TEST(MatrixUtilities, EqualityIsTransitive) {
  constexpr int rows = 5, columns = 5, value = 1;
  Matrix<int> *matrixA = allocateMatrix<int>(rows, columns);
  Matrix<int> *matrixB = allocateMatrix<int>(rows, columns);
  Matrix<int> *matrixC = allocateMatrix<int>(rows, columns);
  fillMatrix(matrixA, 1);
  fillMatrix(matrixB, 1);
  fillMatrix(matrixC, 1);

  EXPECT_TRUE(matrixEqual(matrixA, matrixB));
  EXPECT_TRUE(matrixEqual(matrixB, matrixC));
  EXPECT_TRUE(matrixEqual(matrixA, matrixC));

  freeMatrix(matrixA);
  freeMatrix(matrixB);
  freeMatrix(matrixC);
};
