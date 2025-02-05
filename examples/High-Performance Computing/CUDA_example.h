/**
 * @file: CUDA_example.h (DPHPC Exam HS23 and CUDA Exercises)
 * @brief: Header file with definitions of C++ wrapper function for
 * CUDA kernels.
 * @date: 05/02/2025
 */

#ifndef CUDA_EXAMPLE_H
#define CUDA_EXAMPLE_H

/**
 * @name: MatVecMult
 * @brief: <C/C++> function for general matrix-vector multiplication running CUDA kernel
 * @param A: float*, input matrix of floats with size m x n
 * @param x: float*, input vector of floats with size n
 * @param y: float*, output vector of floats with size m
 * @param m: const int, given row size of A and size of y
 * @param n: const int, given col size of A and size of x
 */
void MatVecMult(float* A, float* x, float* y, const int m, const int n);

/**
 * @name: MatAdd_kernel
 * @brief: <C/C++> function for matrix additions running CUDA kernel
 * @param A: float*, lhs input matrix of floats with size m x n
 * @param B: float*, rhs input matrix of floats with size m x n
 * @param C: float*, output matrix of floats with size m x n
 * @param m: const int, given row size of the matrices
 * @param n: const int, given col size of the matrices
 */
void MatAdd(float* A, float* B, float* C, const int m, const int n);

/**
 * @name: VecAdd_kernel
 * @brief: <C/C++> function for matrix additions running CUDA kernel
 * @param x: float*, lhs input vector of floats with size n
 * @param y: float*, rhs input vector of floats with size n
 * @param z: float*, output vector of floats with size n
 * @param n: const int, given size of the vectors
 */
void VecAdd(float* x, float* y, float* z, const int n);

#endif // CUDA_EXAMPLE_H