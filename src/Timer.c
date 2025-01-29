/**
 * @file    : timer.c
 * @brief   : Source file implementation of timer
 * @author  : David Blickenstorfer
 * 
 * @date 22/10/2024 (basic time management with start, stop, elapse)
 * @copyright Developed at ETH Zurich
 */

#include "../include/Timer.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @name: Timer_Create()
 * @brief: allocate and initialize timer struct and return the pointer
 * @return: pointer of the initialized timer
 */
Timer* Timer_Create() 
{  
    //< The initialization allocate memory with malloc
    //< sets the running as false (0) and the elapse time
    //< to an physical impossible number
    Timer* timer = (Timer*)malloc(sizeof(Timer));
    if(timer == NULL){
        perror("Timer_Create() : Memory allocation failed! \n");
        return NULL;
    }
    timer->running_ = 0;                            
    timer->elapsed_in_ns_ = -1.;
    timer->elapsed_in_sec_ = -1.;
    return timer;
}

/**
 * @name: Timer_Destroy()
 * @brief: destroy a timer struct and free memory
 * @return: pointer of the initialized timer
 */
void Timer_Destroy(Timer* timer)
{
    free(timer);
}

/**
 * @name: Timer_Start()
 * @brief: start the time measurement
 * @param timer: pointer of timer to start measurement
 */
void Timer_Start(Timer* timer)
{
    //< test if the timer has already started the measurement
    if(timer->running_ == 1){
        perror("Timer_Start : Timer is already running! \n");
        Timer_Destroy(timer);
        return;
    }
    //< run the timer and store the time for start
    timer->running_ = 1;
    clock_gettime(CLOCK_MONOTONIC, &(timer->start_));
}

/**
 * @name: Timer_Stop()
 * @brief: stop the time measurement
 * @param Timer: pointer of timer to stop measurement
 */
void Timer_Stop(Timer* timer)
{
    //< firstly, store the time for end
    clock_gettime(CLOCK_MONOTONIC, &(timer->end_));
    //< test if the timer was running
    if(timer->running_ == 0){
        perror("Timer_Stop : Timer is not measuring! \n");
        Timer_Destroy(timer);
        return;
    }
    //< stop the timer run
    timer->running_ = 0;
    //< calculate the duration in ns and then sec
    timer->elapsed_in_ns_ = (timer->end_.tv_nsec - timer->start_.tv_nsec);
    timer->elapsed_in_sec_ = (timer->end_.tv_sec - timer->start_.tv_sec) 
                          + timer->elapsed_in_ns_ / 1e9;
}

/**
 * @name: Timer_Get_Elapsed_in_ns()
 * @brief: return the time interval between start and stop
 * @param Timer: pointer of timer to get the elapsed time [ns]
 */
double Timer_Get_Elapsed_in_ns(Timer* timer)
{
    return timer->elapsed_in_ns_;
}

/**
 * @name: Timer_Get_Elapsed_in_sec()
 * @brief: return the time interval between start and stop
 * @param Timer: pointer of timer to get the elapsed time [ns]
 */
double Timer_Get_Elapsed_in_sec(Timer* timer)
{
    return timer->elapsed_in_sec_;
}