/**
 * @file    : Timer.h
 * @brief   : Header file for Timer struct in C
 * @author  : David Blickenstorfer
 * 
 * @date 22/10/2024 (basic time management: start, stop, elapse)
 * @copyright Developed by David Blickenstorfer
 */

#ifndef TIMER_H
#define TIMER_H

#include <time.h>

/**
 * @name: Timer
 * @brief: struct for managing time intervals
 */
typedef struct Timer
{
    struct timespec start_;     //< store the starting time
    struct timespec end_;       //< store the ending time
    double elapsed_in_sec_;     //< store elapsed times in sec
    double elapsed_in_ns_;      //< store elapsed times in ns
    int running_;               //< store if the timer runs
} Timer;

/**
 * @name: Timer_Create()
 * @brief: allocate and initialize timer struct and return the pointer
 * @return: pointer of the initialized timer
 */
Timer* Timer_Create(); 

/**
 * @name: Timer_Destroy()
 * @brief: destroy a timer struct and free memory
 * @param timer: pointer of timer, free the memory
 */
void Timer_Destroy(Timer* timer);

/**
 * @name: Timer_Start()
 * @brief: start the time measurement
 * @param timer: pointer of timer to start measurement
 */
void Timer_Start(Timer* timer);
/**
 * @name: Timer_Stop()
 * @brief: stop the time measurement
 * @param timer: pointer of timer to stop measurement
 */
void Timer_Stop(Timer* timer);

/**
 * @name: Timer_Get_Elapsed_in_ns()
 * @brief: return the time interval between start and stop
 * @param Timer: pointer of timer to get the elapsed time [ns]
 */
double Timer_Get_Elapsed_in_ns(Timer* timer);

/**
 * @name: Timer_Get_Elapsed_in_sec()
 * @brief: return the time interval between start and stop
 * @param Timer: pointer of timer to get the elapsed time [s]
 */
double Timer_Get_Elapsed_in_sec(Timer* timer);

// Further idea: mean, max, min, standard_deviation, reset
// Needed member variables: min, max, sum, number iteration, double* history


#endif // Timer_H