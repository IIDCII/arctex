// simple example of matrix mul on cuda

#include <cassert>
#include <cstdlib>
#include <iostream>

using namespace std;

// just passing N as it's going to be square
__global__ void matrixMul(int *a, int *b, int *c, int N) {
  int row = blockIdx.y * blockDim.y + threadIdx.y;
  int col = blockIdx.x * blockDim.x + threadIdx.x;

  if (row < N && col < N) {
    int tmp = 0;
    for (int i = 0; i < N; i++) {
      tmp += a[row * N + i] * b[i * N + col];
    }

    c[row * N + col] = tmp;
  }
}

// setting rand numbers (0-100)
void init_matrix(int *m, int N) {
  for (int i = 0; i < N * N; i++) {
    m[i] = rand() % 100;
  }
}

void verify_result(int *a, int *b, int *c, int N) {
  int tmp;
  // matrix mult for cpu
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      tmp = 0;
      for (int k = 0; k < N; k++) {
        tmp += a[i * N + k] * b[k * N + j];
      }

      assert(tmp == c[i * N + j]);
    }
  }
}

int mat_mul_main() {
  // setting the matrix size
  // 1 << 10 is is a bitwise left shift (for example number 5 is 101, shift to
  // the left 5 times and you get 10100000)
  int N = 1 << 10;
  size_t bytes = N * N * sizeof(int);

  // setting the pointers(*) to the addresses(&) and then assigning the space
  // each address needs
  int *a, *b, *c;
  cudaMallocManaged(&a, bytes);
  cudaMallocManaged(&b, bytes);
  cudaMallocManaged(&c, bytes);

  // initialising the matricies we're making
  init_matrix(a, N);
  init_matrix(b, N);
  // init_matrix(c, N); // no need to initialize c before kernel
  // init_matrix(c, N);

  int threads = 16;
  int blocks = (N + threads - 1) / threads;

  dim3 THREADS(threads, threads);
  dim3 BLOCKS(blocks, blocks);

  // launch kernel
  matrixMul<<<BLOCKS, THREADS>>>(a, b, c, N);
  cudaDeviceSynchronize();

  verify_result(a, b, c, N);

  std::cout << "completed well" << std::endl;

  return 0;
}
