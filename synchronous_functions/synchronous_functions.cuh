//
// Created by germain on 14/11/2025.
//
#ifndef CUDAEXPLORATION_BASIC_FUNCTIONS_CUH
#define CUDAEXPLORATION_BASIC_FUNCTIONS_CUH

#include "Matrix.cuh"


template<typename T>
void fill_matrix(Matrix<T> *matrix, T value) {
    for (size_t i = 0; i < matrix->rows * matrix->columns; i++) {
        matrix->values[i] = value;
    }
}

template<typename T>
bool dimensions_equal(const Matrix<T> *matrix1, const Matrix<T> *matrix2) {
    return matrix1->rows == matrix2->rows && matrix1->columns == matrix2->columns;
}

template<typename T>
bool values_equal(const Matrix<T> *matrix1, const Matrix<T> *matrix2) {
    const size_t matrix_size = matrix1->rows * matrix1->columns;
    for (size_t i = 0; i < matrix_size; i++) {
        if (matrix1->values[i] != matrix2->values[i]) return false;
    }
    return true;
}

template<typename T>
bool matrices_equal(const Matrix<T> *matrix1, const Matrix<T> *matrix2) {
    if (matrix1 == matrix2) return true;
    return dimensions_equal(matrix1, matrix2) && values_equal(matrix1, matrix2);
}

template<typename T>
bool matrix_filled(Matrix<T> *matrix, T value) {
    for (size_t i = 0; i < matrix->rows * matrix->columns; i++) {
        if (matrix->values[i] != value) {
            return false;
        }
    }
    return true;
}

template<typename T>
Matrix<T> *allocate_matrix(unsigned int rows, unsigned int columns) {
    auto *mat = static_cast<Matrix<T> *>(malloc(sizeof(Matrix<T>)));
    const size_t number_of_elements = rows * columns;
    mat->values = static_cast<T *>(malloc(number_of_elements * sizeof(T)));
    mat->rows = rows;
    mat->columns = columns;
    return mat;
}

template<typename T>
void free_matrix(Matrix<T> *matrix) {
    free(matrix->values);
    free(matrix);
}

template<typename T>
void add_into_result(Matrix<T> *matrix1, Matrix<T> *matrix2, Matrix<T> *result) {
    const unsigned int matrix_size = matrix1->rows * matrix1->columns;
    for (size_t i = 0; i < matrix_size; i++) {
        result->values[i] = matrix1->values[i] + matrix2->values[i];
    }
}

template<typename T>
[[nodiscard]] Matrix<T> *add_matrices_synchronously(Matrix<T> *matrix1, Matrix<T> *matrix2) {
    if (!dimensions_equal(matrix1, matrix2)) throw std::exception();
    Matrix<T> *result = allocate_matrix<T>(matrix1->rows, matrix1->columns);
    add_into_result(matrix1, matrix2, result);
    return result;
}
#endif //CUDAEXPLORATION_BASIC_FUNCTIONS_CUH
