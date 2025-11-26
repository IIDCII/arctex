//
// Created by germain on 15/11/2025.
//

#include <iostream>
#include <CUnit/TestDB.h>

__global__ void foo(int* a)
{
    int i = threadIdx.x + blockDim.x * blockIdx.x;
    a[i] = i;
}

void test_incremental_1d_indexing()
{
    constexpr int length = 9;
    int* device_array;
    int host_array[length];
    const int expected[length] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

    cudaError_t error_code = cudaMalloc(&device_array, sizeof(int) * length);
    if (error_code != cudaSuccess)
    {
        throw std::exception();
    }
    foo<<<3,3>>>(device_array);
    error_code = cudaGetLastError();
    if (error_code != cudaSuccess)
    {
        std::cerr << "CUDA error " << static_cast<int>(error_code)
            << " (" << cudaGetErrorName(error_code) << "): "
            << cudaGetErrorString(error_code) << "\n";
        std::terminate();
    }
    error_code = cudaDeviceSynchronize();
    if (error_code != cudaSuccess)
    {
        throw std::exception();
    }
    error_code = cudaMemcpy(host_array, device_array, sizeof(int) * length, cudaMemcpyDeviceToHost);
    if (error_code != cudaSuccess)
    {
        throw std::exception();
    }


    for (const int i : host_array)
    {
        std::cout << i << " ";
    }
    std::cout.flush();
    for (size_t i = 0; i < length; ++i)
    {
        CU_ASSERT_EQUAL(host_array[i], expected[i]);
    }

    // CU_ASSERT(matrices_equal(expected, host_array, 3));

    cudaFree(device_array);
}

void test_experimentation()
{
    const CU_pSuite suite = CU_add_suite("CUDA Experimentation", 0, 0);
    CU_add_test(suite, "incrementation", test_incremental_1d_indexing);
}
