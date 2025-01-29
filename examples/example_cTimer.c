/**
 * @file    : example_cTimer.c
 * @brief   : Documentation code for the usage of Timer
 * @author  : David Blickenstorfer
 * 
 * @date 22/10/2024 (code architecture)
 * @copyright Developed at ETH Zurich
 */

#include "../include/Timer.h"
#include <stdio.h>

int main(int argc, char* argv[]) 
{
    //< Create pointer of Timer (Initialization)
    Timer* myTimer = Timer_Create();

    //< Start the time measurement
    Timer_Start(myTimer);

    //< Calculate the sum of n = 0 + 1 + 2 ... + 10000
    unsigned int sum = 0;
    for(unsigned int i = 0; i < 10000; i++){
        sum += i;
    }

    //< Stop the time measurement
    Timer_Stop(myTimer);

    //< print out the result
    printf("The sum of 0 up to 10000 is %d \n", sum);
    printf("Time in ns : %f \n", Timer_Get_Elapsed_in_ns(myTimer));
    printf("Time in sec : %f \n", Timer_Get_Elapsed_in_sec(myTimer));

    //< Deallocate the Timer memory
    Timer_Destroy(myTimer);

    return 0;
}