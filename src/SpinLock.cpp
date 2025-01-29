/**
 * @file    : SpinLock.cpp
 * @brief   : Cpp file of CAS (compare-and-swap) Lock
 * @author  : David Blickenstorfer
 * 
 * @date 21/01/2025
 * @copyright Developed by David Blickenstorfer
 */

#include "../include/SpinLock.hpp"

/**
 * @name: SpinLock()
 * @brief: Default Constructor
 */
SpinLock::SpinLock()
{
    locked_ = false;
}


/**
 * @name: acquire()
 * @brief: lock the CAS lock before entering critical region
 */
void SpinLock::acquire()
{
    while(!CAS(&locked_, false, true)){
        // reduce CPU contention 
        std::this_thread::yield();
    }
}

/**
 * @name: release()
 * @brief: unlock the CAS lock before leaving critical region
 */
void SpinLock::release()
{
    locked_ = false;
}

