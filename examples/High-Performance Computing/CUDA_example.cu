/**
 * @file: CUDA_example (DPHPC Exam HS23 and CUDA Exercises)
 * @brief: The following CUDA kernel implementing basic matrix and vector
 * arithmetic and operations including dense matrix vector multiplication, 
 * matrix addition and vector addition.
 * @date: 05/02/2025
 */

extern "C" {
#include "CUDA_example.h"
#include <cuda_runtime.h>
}

// ============================================
// IMPLEMENTATION OF <CUDA> KERNEL FUNCTIONS
// ============================================

/**
 * @name: MatVecMult_kernel
 * @brief: CUDA kernel function for general matrix-vector multiplication
 * @param A: float*, input matrix of floats with size m x n
 * @param x: float*, input vector of floats with size n
 * @param y: float*, output vector of floats with size m
 * @param m: const int, given row size of A and size of y
 * @param n: const int, given col size of A and size of x
 */
__global__ void MatVecMult_kernel(float* A, float* x, float* y, const int m, const int n)
{
    // calculate the idx (tid) in output vector
    unsigned int tid = blockDim.x * blockIdx.x + threadIdx.x;
    if(tid >= m){
        return;
    }

    // calculate inner product for output vector
    float c = 0.;
    for(int i = 0; i < n; i++){
        c = c + x[i] * A[tid * m + i];
    }    
    y[tid] = c;
}

/**
 * @name: MatAdd_kernel
 * @brief: CUDA kernel function for matrix additions
 * @param A: float*, lhs input matrix of floats with size m x n
 * @param B: float*, rhs input matrix of floats with size m x n
 * @param C: float*, output matrix of floats with size m x n
 * @param m: const int, given row size of the matrices
 * @param n: const int, given col size of the matrices
 */
__global__ void MatAdd_kernel(float* A, float* B, float* C, const int m, const int n)
{
    // calculate tid in output matrix
    unsigned tid = blockDim.x * blockIdx.x + threadIdx.x;
    if(tid >= m){
        return;
    }

    // perform matrix matrix addition
    C[tid] = A[tid] + B[tid];
}

/**
 * @name: VecAdd_kernel
 * @brief: CUDA kernel function for vector additions
 * @param x: float*, lhs input vector of floats with size m x n
 * @param y: float*, rhs input vector of floats with size m x n
 * @param z: float*, output vector of floats with size m x n
 * @param n: const int, given size of the vectors
 */
__global__ void VecAdd_kernel(float* x, float* y, float* z, const int n)
{
    // calculate tid of the output matrix
    unsigned int tid = blockDim.x * blockIdx.x + threadIdx.x;
    if(tid >= n){
        return;
    }

    // perform vector addition
    z[tid] = x[tid] + y[tid];
}

// =========================================================
// IMPLEMENTATION OF <C/C++> FUNCTIONS USING CUDA KERNELS
// =========================================================

/**
 * @name: MatVecMult
 * @brief: <C/C++> function for general matrix-vector multiplication running CUDA kernel
 * @param A: float*, input matrix of floats with size m x n
 * @param x: float*, input vector of floats with size n
 * @param y: float*, output vector of floats with size m
 * @param m: const int, given row size of A and size of y
 * @param n: const int, given col size of A and size of x
 */
void MatVecMult(float* A, float* x, float* y, const int m, const int n)
{
    // CUDA Setting tool variables
    int threads_perblockm = 32;
    dim3 threadsPerBlockm(threads_perblockm);
    int num_blocksm = (int)ceil((float)m/(float)threads_perblockm);
    dim3 numBlocksm(num_blocksm);

    // initialize size of allocation memory
    size_t A_size = m * n * sizeof(float);
    size_t x_size = n * sizeof(float);
    size_t y_size = m * sizeof(float);

    // initialize CUDA kernel parameter variable
    float *A_cuda, *x_cuda, *y_cuda;

    // allocate CUDA memory
    cudaMalloc(&A_cuda, A_size);
    cudaMalloc(&x_cuda, A_size);
    cudaMalloc(&y_cuda, A_size);

    // Memcpy the input in CUDA
    cudaMemcpy(A_cuda, A, A_size, cudaMemcpyHostToDevice);
    cudaMemcpy(x_cuda, x, x_size, cudaMemcpyHostToDevice);

    // run on kernel
    MatVecMult_kernel<<<numBlocksm, threadsPerBlockm>>>(
        (float*) A_cuda, (float*) x_cuda, (float*) y_cuda, m, n
    );

    // synchronize host and device
    cudaDeviceSynchronize();

    // Memcpy the output in CUDA
    cudaMemcpy(y, y_cuda, y_size, cudaMemcpyDeviceToHost);

    // free CUDA memory
    cudaFree(A_cuda);
    cudaFree(x_cuda);
    cudaFree(y_cuda);
}

/**
 * @name: MatAdd_kernel
 * @brief: <C/C++> function for matrix additions running CUDA kernel
 * @param A: float*, lhs input matrix of floats with size m x n
 * @param B: float*, rhs input matrix of floats with size m x n
 * @param C: float*, output matrix of floats with size m x n
 * @param m: const int, given row size of the matrices
 * @param n: const int, given col size of the matrices
 */
void MatAdd(float* A, float* B, float* C, const int m, const int n)
{
    // initialize CUDA tool variable
    int threads_perBlock = 32;
    dim3 threadsPerBlock(threads_perBlock);
    int num_blocks = (int) ceil((float) (m * n) / (float) threads_perBlock);
    dim3 numBlocks(num_blocks);

    // allocate size of allocation memory
    size_t mat_size = m * n * sizeof(float);

    // initialize CUDA kernel variable
    float *A_cuda, *B_cuda, *C_cuda;

    // allocate CUDA memory
    cudaMalloc(&A_cuda, mat_size);
    cudaMalloc(&B_cuda, mat_size);
    cudaMalloc(&C_cuda, mat_size);

    // Memcpy the input in CUDA
    cudaMemcpy(A_cuda, A, mat_size, cudaMemcpyHostToDevice);
    cudaMemcpy(B_cuda, B, mat_size, cudaMemcpyHostToDevice);

    // run on kernel
    MatAdd_kernel<<<numBlocks, threadsPerBlock>>>(A_cuda, B_cuda, C_cuda, m, n);

    // synchronize host and device
    cudaDeviceSynchronize();

    // Memcpy the output in CUDA
    cudaMemcpy(C_cuda, C, mat_size, cudaMemcpyDeviceToHost);

    // free CUDA memory
    cudaFree(A_cuda);
    cudaFree(B_cuda);
    cudaFree(C_cuda);
}

/**
 * @name: VecAdd_kernel
 * @brief: <C/C++> function for matrix additions running CUDA kernel
 * @param x: float*, lhs input vector of floats with size n
 * @param y: float*, rhs input vector of floats with size n
 * @param z: float*, output vector of floats with size n
 * @param n: const int, given size of the vectors
 */
void VecAdd(float* x, float* y, float* z, const int n)
{
    // CUDA Setting tool variables
    int threads_perBlock = 32;
    dim3 threadsPerBlock(threads_perBlock);
    int num_blocks = (int) ceil((float) n / (float) threads_perBlock);
    dim3 numBlocks(num_blocks);

    // allocate size of input variables
    size_t vec_size = sizeof(float) * n;

    // initialize CUDA kernel variables
    float *x_cuda, *y_cuda, *z_cuda;
    
    // allocate CUDA memory
    cudaMalloc(&x_cuda, vec_size);
    cudaMalloc(&y_cuda, vec_size);
    cudaMalloc(&z_cuda, vec_size);

    // Memcpy the input in CUDA
    cudaMemcpy(x_cuda, x, vec_size, cudaMemcpyHostToDevice);
    cudaMemcpy(y_cuda, y, vec_size, cudaMemcpyHostToDevice);

    // run on kernel
    VecAdd_kernel<<<numBlocks, threadsPerBlock>>>(x_cuda, y_cuda, z_cuda, n);

    // synchronize host and device
    cudaDeviceSynchronize();

    // Memcpy the output in CUDA
    cudaMemcpy(z_cuda, z, vec_size, cudaMemcpyDeviceToHost);

    // free CUDA memory
    cudaFree(x_cuda);
    cudaFree(y_cuda);
    cudaFree(z_cuda);
}