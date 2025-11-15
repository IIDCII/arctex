//
// Created by germain on 14/11/2025.
//

#pragma once

#include "synchronous_functions/synchronous_functions.cuh"


void test_fill_matrix() {
    constexpr int rows = 2, columns = 2, value = 3;
    auto *matrix = allocate_matrix<int>(rows, columns);

    fill_matrix(matrix, value);
    CU_ASSERT(matrix_filled(matrix, value))

    free_matrix(matrix);
}

void test_equality_same_values() {
    constexpr unsigned int rows = 5, columns = 5;
    constexpr int value = 1;
    auto *matrix1 = allocate_matrix<int>(rows, columns);
    auto *matrix2 = allocate_matrix<int>(rows, columns);

    fill_matrix(matrix1, value);
    fill_matrix(matrix2, value);

    CU_ASSERT(matrices_equal(matrix1, matrix2))
    CU_ASSERT(matrices_equal(matrix2, matrix1))

    free_matrix(matrix1);
    free_matrix(matrix2);
}

void test_equality_different_value() {
    constexpr unsigned int rows = 5, columns = 5;
    constexpr int value1 = 1, value2 = 2;
    auto *matrix1 = allocate_matrix<int>(rows, columns);
    auto *matrix2 = allocate_matrix<int>(rows, columns);

    fill_matrix(matrix1, value1);
    fill_matrix(matrix2, value2);

    CU_ASSERT(!matrices_equal(matrix1, matrix2))
    CU_ASSERT(!matrices_equal(matrix2, matrix1))

    free_matrix(matrix1);
    free_matrix(matrix2);
}

void test_equality_reflexively() {
    constexpr unsigned int rows = 5, columns = 5;
    constexpr int value = 1;
    auto *matrix1 = allocate_matrix<int>(rows, columns);
    fill_matrix(matrix1, value);

    CU_ASSERT(matrices_equal(matrix1, matrix1))

    free_matrix(matrix1);
}

void test_addition_zeros() {
    constexpr unsigned int rows = 5, columns = 5;
    constexpr int zero = 0;
    auto *matrix1 = allocate_matrix<int>(rows, columns);
    auto *matrix2 = allocate_matrix<int>(rows, columns);
    auto *expected = allocate_matrix<int>(rows, columns);
    fill_matrix(matrix1, zero);
    fill_matrix(matrix2, zero);
    fill_matrix(expected, zero);

    Matrix<int> *result = add_matrices_synchronously(matrix1, matrix2);
    CU_ASSERT(matrices_equal(result, expected))

    free_matrix(matrix1);
    free_matrix(matrix2);
    free_matrix(expected);
    free_matrix(result);
}

void test_addition_ones() {
    constexpr unsigned int rows = 5, columns = 5;
    constexpr int one = 1;
    auto *matrix1 = allocate_matrix<int>(rows, columns);
    auto *matrix2 = allocate_matrix<int>(rows, columns);
    auto *expected = allocate_matrix<int>(rows, columns);
    fill_matrix(matrix1, one);
    fill_matrix(matrix2, one);
    fill_matrix(expected, one + one);

    Matrix<int> *result = add_matrices_synchronously(matrix1, matrix2);
    CU_ASSERT(matrices_equal(result, expected))

    free_matrix(matrix1);
    free_matrix(matrix2);
    free_matrix(expected);
    free_matrix(result);
}

void test_addition_ones_and_twos() {
    constexpr unsigned int rows = 5, columns = 5;
    constexpr int one = 1, two = 2;
    auto *matrix1 = allocate_matrix<int>(rows, columns);
    auto *matrix2 = allocate_matrix<int>(rows, columns);
    auto *expected = allocate_matrix<int>(rows, columns);
    fill_matrix(matrix1, one);
    fill_matrix(matrix2, two);
    fill_matrix(expected, one + two);

    Matrix<int> *result = add_matrices_synchronously(matrix1, matrix2);
    CU_ASSERT(matrices_equal(result, expected))

    free_matrix(matrix1);
    free_matrix(matrix2);
    free_matrix(expected);
    free_matrix(result);
}

void test_addition_manual_values() {
    constexpr unsigned int rows = 2, columns = 2;
    auto *matrix1 = allocate_matrix<int>(rows, columns);
    auto *matrix2 = allocate_matrix<int>(rows, columns);
    auto *expected = allocate_matrix<int>(rows, columns);

    matrix1->values[0] = 1, matrix1->values[1] = 4;
    matrix1->values[2] = 3, matrix1->values[3] = 5;

    matrix2->values[0] = 7, matrix2->values[1] = 8;
    matrix2->values[2] = 0, matrix2->values[3] = 9;

    expected->values[0] = 1 + 7, expected->values[1] = 4 + 8;
    expected->values[2] = 3 + 0, expected->values[3] = 5 + 9;

    Matrix<int> *result = add_matrices_synchronously(matrix1, matrix2);
    CU_ASSERT(matrices_equal(result, expected))

    free_matrix(matrix1);
    free_matrix(matrix2);
    free_matrix(expected);
    free_matrix(result);
}

void test_addition_associative() {
    constexpr unsigned int rows = 5, columns = 5;
    constexpr int one = 1, two = 2;
    auto *matrix1 = allocate_matrix<int>(rows, columns);
    auto *matrix2 = allocate_matrix<int>(rows, columns);
    fill_matrix(matrix1, one);
    fill_matrix(matrix2, two);

    Matrix<int> *result1 = add_matrices_synchronously(matrix1, matrix2);
    Matrix<int> *result2 = add_matrices_synchronously(matrix2, matrix1);
    CU_ASSERT(matrices_equal(result1, result2))

    free_matrix(matrix1);
    free_matrix(matrix2);
    free_matrix(result1);
    free_matrix(result2);
}

void test_addition_commutative() {
    constexpr unsigned int rows = 5, columns = 5;
    constexpr int one = 1, two = 2, three = 3;
    auto *matrix1 = allocate_matrix<int>(rows, columns);
    auto *matrix2 = allocate_matrix<int>(rows, columns);
    auto *matrix3 = allocate_matrix<int>(rows, columns);
    fill_matrix(matrix1, one);
    fill_matrix(matrix2, two);
    fill_matrix(matrix3, three);

    Matrix<int> *one_plus_two = add_matrices_synchronously(matrix1, matrix2);
    Matrix<int> *two_plus_three = add_matrices_synchronously(matrix2, matrix3);
    Matrix<int> *result1 = add_matrices_synchronously(one_plus_two, matrix3);
    Matrix<int> *result2 = add_matrices_synchronously(matrix1, two_plus_three);
    CU_ASSERT(matrices_equal(result1, result2))

    free_matrix(matrix1);
    free_matrix(matrix2);
    free_matrix(one_plus_two);
    free_matrix(two_plus_three);
    free_matrix(result1);
    free_matrix(result2);
}

void test_addition_non_square_matrices() {
    constexpr unsigned int rows = 3, columns = 2;
    constexpr int one = 1, two = 2;
    auto *matrix1 = allocate_matrix<int>(rows, columns);
    auto *matrix2 = allocate_matrix<int>(rows, columns);
    auto *expected = allocate_matrix<int>(rows, columns);
    fill_matrix(matrix1, one);
    fill_matrix(matrix2, two);
    fill_matrix(expected, one + two);

    Matrix<int> *result = add_matrices_synchronously(matrix1, matrix2);
    CU_ASSERT(matrices_equal(result, expected))

    free_matrix(matrix1);
    free_matrix(matrix2);
    free_matrix(expected);
    free_matrix(result);
}

void test_addition_differing_rows_error() {
    constexpr unsigned int columns = 2;
    auto *matrix1 = allocate_matrix<int>(1, columns);
    auto *matrix2 = allocate_matrix<int>(2, columns);


    try {
        Matrix<int> *_ = add_matrices_synchronously(matrix1, matrix2);
        CU_FAIL()
    } catch (std::exception &error) {
    }

    free_matrix(matrix1);
    free_matrix(matrix2);
}

void test_addition_differing_columns_error() {
    constexpr unsigned int rows = 2;
    auto *matrix1 = allocate_matrix<int>(rows, 1);
    auto *matrix2 = allocate_matrix<int>(rows, 2);


    try {
        Matrix<int> *_ = add_matrices_synchronously(matrix1, matrix2);
        CU_FAIL()
    } catch (std::exception &error) {
    }

    free_matrix(matrix1);
    free_matrix(matrix2);
}

void test_basic_functions() {
    CU_pSuite suite = CU_add_suite("BasicFunctionsSuite", 0, 0);
    CU_add_test(suite, "Fill matrix with 0s", test_fill_matrix);
    CU_add_test(suite, "Equality of same value matrices", test_equality_same_values);
    CU_add_test(suite, "Equality of different value matrices", test_equality_different_value);
    CU_add_test(suite, "Equality of matrix with itself", test_equality_reflexively);
    CU_add_test(suite, "Addition of 0 filled matrices", test_addition_zeros);
    CU_add_test(suite, "Addition of 1 filled matrices", test_addition_ones);
    CU_add_test(suite, "Addition of differently filled matrices", test_addition_ones_and_twos);
    CU_add_test(suite, "Addition of manually filled matrices", test_addition_manual_values);
    CU_add_test(suite, "Addition is associative", test_addition_associative);
    CU_add_test(suite, "Addition is commutative", test_addition_commutative);
    CU_add_test(suite, "Addition of non square matrices", test_addition_non_square_matrices);
    CU_add_test(suite, "Addition of matrices with differing row sizes throws error",
                test_addition_differing_rows_error);
    CU_add_test(suite, "Addition of matrices with differing columns sizes throws error",
                test_addition_differing_columns_error);
}
