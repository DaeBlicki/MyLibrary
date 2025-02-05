/**
 * @file: CUDA_example.c (DPHPC Exam HS23)
 * @brief: The following CUDA Progrom performs linear algebra operations.
 * In particular, dense matrix vector multiplication, matrix addition 
 * and vector additions with CUDA kernel.
 * @date: 05/02/2025
 */

#include "CUDA_example.h"       //< GPU Programming
#include <malloc.h>             //< Memory allocation
#include <stdlib.h>             //< exit
#include "utils/print_utils.h"  //< Debugging
#include "utils/Timer.h"        //< Benchmarking

int main(int argc, char** argv)
{
    // Initialize sizes for all linear operations
    int m = 8;   // 8 Bytes
    int n = 8;   // 8 Bytes

    // allocate memory for input vectors and matrices
    float* A = malloc(m * n * sizeof(float));
    float* B = malloc(m * n * sizeof(float));
    float* x = malloc(n * sizeof(float));
    float* y = malloc(n * sizeof(float));

    // allocate memory for output vectors and matrices
    float* MatVecMultOutput = malloc(m * sizeof(float));
    float* MatAddOutput = malloc(m * n * sizeof(float));
    float* VecAddOutput = malloc(n * sizeof(float));

    // allocate memory for Timer
    Timer* stopwatch = Timer_Create();

    // check if allocation failed!
    if(A == NULL || B == NULL || x == NULL || y == NULL || stopwatch == NULL){
        println('r', 'b', "Memory allocation failed! Exit program!");
        free(A); free(B); free(x); free(y);
        free(MatVecMultOutput);
        free(MatAddOutput);
        free(VecAddOutput);
        Timer_Destroy(stopwatch);
        exit(-1);
    }

    // filling all input matrices
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            A[i * n + j] = (float) i / 5.0f + (float) j / 10.0f;
            B[i * n + j] = (float) i / 8.0f + (float) j / 6.0f;
        }
    }

    // filling all input vectors
    for(int i = 0; i < n; i++){
        x[i] = (float) (i+1) / 4.;
        y[i] = (float) (i+1) / 8.;
    }

    // perform gpu linear algebra multiplication

    // vector addition
    Timer_Start(stopwatch);
    VecAdd(x, y, VecAddOutput, n);
    Timer_Stop(stopwatch);
    print('b', 'd', "Elapsed time: ");
    printf("%f ms \n", Timer_Get_Elapsed_in_sec(stopwatch) / 1000.);

    // mat addition
    Timer_Start(stopwatch);
    MatAdd(A, B, MatAddOutput, m, n);
    Timer_Stop(stopwatch);
    print('b', 'd', "Elapsed time: ");
    printf("%f ms \n", Timer_Get_Elapsed_in_sec(stopwatch) / 1000.);

    // mat vector multiplication
    Timer_Start(stopwatch);
    MatVecMult(A, x, MatVecMultOutput, m, n);
    Timer_Stop(stopwatch);
    print('b', 'd', "Elapsed time: ");
    printf("%f ms \n", Timer_Get_Elapsed_in_sec(stopwatch) / 1000.);  
    
    // check result and print out result
    println('y', 'b', "lhs input matrix A");
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            printf("%f ", A[i * n + j]);
        }
        printf("\n");
    }

    // check result and print out result
    println('y', 'b', "rhs input matrix B");
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            printf("%f ", B[i * n + j]);
        }
        printf("\n");
    }

    // check result and print out result
    println('y', 'b', "MatAddOutput matrix!");
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            printf("%f ", MatAddOutput[i * n + j]);
        }
        printf("\n");
    }

    // free memory 
    free(A); free(B); free(x); free(y);
    free(MatVecMultOutput);
    free(MatAddOutput);
    free(VecAddOutput);
    Timer_Destroy(stopwatch);

    return 0;
}