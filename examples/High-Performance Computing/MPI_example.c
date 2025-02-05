/**
 * @file: MPI_example (DPHPC Exam HS23)
 * @brief: The following MPI program is supposed to implement a ring broadcast, but contains five
 * errors. Locate each problem, explain what is wrong, and provide a solution to correct it.
 * @date: 03/02/2025
 */

// ======================================================================
// Documentation for MPI_Send and MPI_Recv
// int MPI_Send(const void *buf, int count, MPI_Datatype datatype,
//              int dest, int tag, MPI_Comm comm)
// int MPI_Recv(void *buf, int count, MPI_Datatype datatype,
//              int source, int tag, MPI_Comm comm, MPI_Status *status)
// ======================================================================

#include <mpi.h>                //< parallel programming
#include "utils/print_utils.h"  //< debugging

int main(int argc, char** argv)
{
    // initialize MPI World
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int message;

    // ring broadcast
    if(rank == 0){
        message = 42;
        println('r', 'b', "Start Message Passing with MPI!");
        MPI_Send(&message, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        print('y', 'd', "Message send with m = ");
        printf("%d \n", message);
        MPI_Recv(&message, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        print('b', 'd', "Message received with m = ");
        printf("%d \n", message);
    } else{
        MPI_Recv(&message, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        print('b', 'd', "Message received with m = ");
        printf("%d \n", message);        
        message++;
        MPI_Send(&message, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
        print('y', 'd', "Message send with m = ");
        printf("%d \n", message);
    }

    // finalize MPI World
    MPI_Finalize();

    return 0;
}