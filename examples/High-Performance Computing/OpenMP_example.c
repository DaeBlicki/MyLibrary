/**
 * @file: OMP_example (DPHPC Exam HS23)
 * @brief: The following OpenMP program is supposed to perform array arithmetic
 * @date: 05/02/2025
 */

// ======================================================================
// Documentation for MPI_Send and MPI_Recv
// int MPI_Send(const void *buf, int count, MPI_Datatype datatype,
//              int dest, int tag, MPI_Comm comm)
// int MPI_Recv(void *buf, int count, MPI_Datatype datatype,
//              int source, int tag, MPI_Comm comm, MPI_Status *status)
// ======================================================================

#define NUM_PROCESSORS 10
#define ARR_SIZE 20000

#include <omp.h>                //< parallel programming
#include <malloc.h>             //< memory allocation
#include "utils/Timer.h"        //< benchmarking
#include "utils/print_utils.h"  //< debugging

int main(int argc, char** argv)
{
    // tool variables for programm
    int i, j, sum;
    int size = ARR_SIZE;
    int* A;
    Timer* stopwatch;

    // sequential execution
    println('y', 'b', "Start of sequential execution!");

    // allocate memory
    A = malloc(ARR_SIZE * sizeof(int));
    if(A == NULL){
        print('r', 'b', "malloc failed! \n");
        Timer_Destroy(stopwatch);
        return -1;
    }

    // create benchmark tools
    stopwatch = Timer_Create();
    Timer_Start(stopwatch);

    // start of program
    j = 0;
    sum = 0;
    for(i = 0; i < size; i++){
        A[i] = i;
    }
    for(i = 0; i < size; i++){
        A[i] = A[i] + j;
        j += 5;
    }
    for(i = 0; i < size; i++){
        sum += A[i];
    }

    // benchmark and printing
    Timer_Stop(stopwatch);
    print('b', 'd', "Elapsed time: ");
    printf("%f ns \n", Timer_Get_Elapsed_in_ns(stopwatch));

    // print solution
    print('b', 'd', "The accumulated sum : ");
    printf("%d \n", sum);

    // free memory
    free(A);

    // parallel execution
    println('y', 'b', "Start of first parallel execution!");
    omp_set_num_threads(NUM_PROCESSORS);

    // allocate memory
    A = malloc(ARR_SIZE * sizeof(int));
    if(A == NULL){
        print('r', 'b', "malloc failed! \n");
        Timer_Destroy(stopwatch);
        return -1;
    }

    // create benchmark tools
    stopwatch = Timer_Create();
    Timer_Start(stopwatch);

    // start of program
    j = 0;
    sum = 0;

    #pragma omp parallel for reduction (+:sum)
    for(i = 0; i < size; i++){
        A[i] = i;
        A[i] = A[i] + j + i*5;
        sum += A[i];    
    }   

    // benchmark and printing
    Timer_Stop(stopwatch);
    print('b', 'd', "Elapsed time: ");
    printf("%f ns \n", Timer_Get_Elapsed_in_ns(stopwatch));

    // print solution
    print('b', 'd', "The accumulated sum : ");
    printf("%d \n", sum);

    // free memory
    free(A);

    // parallel execution
    println('y', 'b', "Start of second parallel execution!");
    omp_set_num_threads(NUM_PROCESSORS);

    // allocate memory
    A = malloc(ARR_SIZE * sizeof(int));
    if(A == NULL){
        print('r', 'b', "malloc failed! \n");
        Timer_Destroy(stopwatch);
        return -1;
    }

    // create benchmark tools
    stopwatch = Timer_Create();
    Timer_Start(stopwatch);

    // start of program
    j = 0;
    sum = 0;
    #pragma omp parallel for
    for(i = 0; i < size; i++){
        A[i] = i;
        A[i] = A[i] + j + i*5;
        #pragma omp critical
        sum += A[i];
    }

    // benchmark and printing
    Timer_Stop(stopwatch);
    print('b', 'd', "Elapsed time: ");
    printf("%f ns \n", Timer_Get_Elapsed_in_ns(stopwatch));

    // print solution
    print('b', 'd', "The accumulated sum : ");
    printf("%d \n", sum);

    // free memory
    free(A);

    return 0;
}

