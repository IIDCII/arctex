//
// Created by germain on 14/11/2025.
//

#ifndef CUDAEXPLORATION_DISTRIBUTED_FUNCTIONS_TESTS_CUH
#define CUDAEXPLORATION_DISTRIBUTED_FUNCTIONS_TESTS_CUH
#include <CUnit/TestDB.h>

// void matrixAdd(int *mat1, int *mat2, int *added_matrix, size_t size) {
//     int row = blockIdx.y * blockDim.y + threadIdx.y;
//     int col = blockIdx.x * blockDim.x + threadIdx.x;
//
//     if (row < size && col < cols) {
//         int idx = row * cols + col;
//         C[idx] = A[idx] + B[idx];
//     }
// }
//
// void foo() {
//     constexpr size_t length = 2;
//     constexpr size_t bytes = sizeof(int) * length * length;
//     int *mat1, *mat2, *added_matrix, *expected_matrix;
//
//     cudaMallocManaged(&mat1, bytes);
//     cudaMallocManaged(&mat2, bytes);
//     cudaMallocManaged(&added_matrix, bytes);
//     cudaMallocManaged(&expected_matrix, bytes);
//
//     mat1[0] = 1, mat1[1] = 4, mat1[2] = 3, mat1[3] = 5;
//     mat2[0] = 7, mat2[1] = 8, mat2[2] = 0, mat2[3] = 9;
//     expected_matrix[0] = 1 + 7, expected_matrix[1] = 4 + 8, expected_matrix[2] = 3 + 0, expected_matrix[3] = 5 + 9;
//
//     // Launch 1 block of 2x2 threads (overkill but clear)
//     dim3 threads(2, 2);
//     dim3 blocks(1, 1);
//
//     // matrixAdd<<<blocks, threads>>>(mat1, mat2, added_matrix, length);
//     cudaDeviceSynchronize();
//     // add_matrices_cuda(mat1, mat2, added_matrix, length);
//
//     CU_ASSERT(is_matrix_equal(expected_matrix, added_matrix, length));
//
//     cudaFree(mat1);
//     cudaFree(mat2);
//     cudaFree(added_matrix);
//     cudaFree(expected_matrix);
// }
//
// void test_cuda_functions() {
//     const CU_pSuite suite = CU_add_suite("CudaImplementations", 0, 0);
//     // CU_add_test(suite, "Add two matrices", foo);
// }

#endif //CUDAEXPLORATION_DISTRIBUTED_FUNCTIONS_TESTS_CUH
