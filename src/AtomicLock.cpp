/**
 * @file    : AtomicLock.cpp
 * @brief   : Cpp file of TES (test-and-set) Lock
 * @author  : David Blickenstorfer
 * 
 * @date 28/01/2025
 * @copyright Developed by David Blickenstorfer
 */

#include "../include/AtomicLock.hpp"

/**
 * @name: AtomicLock()
 * @brief: Default Constructor
 */
AtomicLock::AtomicLock()
{
    locked_ = false;
}


/**
 * @name: acquire()
 * @brief: lock the CAS lock before entering critical region
 */
void AtomicLock::acquire()
{
    while(TAS(&locked_)){
        // reduce CPU contention 
        std::this_thread::yield();
    }
}

/**
 * @name: release()
 * @brief: unlock the CAS lock before leaving critical region
 */
void AtomicLock::release()
{
    locked_ = false;
}

