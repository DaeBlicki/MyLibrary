/**
 * @file    : test_print_utils.cpp
 * @brief   : test code for printing utility
 * @author  : David Blickenstorfer
 * @date 18/11/2024
 * @copyright Developed by David Blickenstorfer
 */

#include "../include/print_utils.h"
#include "../include/Timer.h"

int main()
{
    println('r', 'b', "this is a bold red text!");
    print('y', 'f', "flashy yellow");
    print('w', 'b', " vs. ");
    println('c', 'u', "underlined cyan");
    println('g', 'b', "hello world :)");
    printf("\n");
    
    println('y', 'b', "Benchmark utility printing function!");
    Timer* utils_clock = Timer_Create();
    Timer_Start(utils_clock);
    for(unsigned int i = 0; i < 10; i++){
        println('g', 'd', "hello world!");
    }
    Timer_Stop(utils_clock);
    const double elapsed_time_in_ns_for_utilts = utils_clock->elapsed_in_ns_;
    printf("%s%f%s", "Elapsed time in ns: ", elapsed_time_in_ns_for_utilts, "\n");
    Timer_Destroy(utils_clock);

    println('y', 'b', "Benchmark printing function for C++ standard library!");
    Timer* standard_clock = Timer_Create();
    Timer_Start(standard_clock);
    for(unsigned int i = 0; i < 10; i++){
        printf("hello world! \n");
    }
    Timer_Stop(standard_clock);
    const double elapsed_time_in_ns_for_standard = standard_clock->elapsed_in_ns_;
    printf("%s%f%s", "Elapsed time in ns: ", elapsed_time_in_ns_for_standard, "\n");
    Timer_Destroy(standard_clock);
}