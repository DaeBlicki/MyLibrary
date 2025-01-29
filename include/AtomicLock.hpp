/**
 * @file    : AtomicLock.hpp
 * @brief   : Header file of TAS (test-and-swap) Lock
 * @author  : David Blickenstorfer
 * 
 * @date 28/01/2025
 * @copyright Developed by David Blickenstorfer
 */

#ifndef TASLOCK_HPP
#define TASLOCK_HPP

#include <thread>   //< allow multi-threading programming
#include <atomic>   //< allow atomic variables to protect compiler optimization

/**
 * @name: TAS() - test-and-set
 * @brief: Atomic operation test-and-set, modify memory flag with lock state
 * and return the old value of flag
 * @param flag: pointer to atomic template class, memory of the test variable
 * @return: boolean, true old value of flag
 */
template <typename T>
bool TAS(T* flag) {
    // swap with locked = true
    return __sync_lock_test_and_set(flag, true);
}

class AtomicLock
{
private:
    // can be updated into std::atomic<bool> locked_ in further implementations
    bool locked_;  //< Lock State (true = locked, false = unlocked)

public:

    /**
     * @name: AtomicLock()
     * @brief: Default Constructor
     */
    AtomicLock();

    /**
     * @name: AtomicLock()
     * @brief: Copy Constructor
     */
    AtomicLock(const AtomicLock& atomicLock)=default; 

    /**
     * @name: AtomicLock()
     * @brief: Default Destructor
     */
    ~AtomicLock()=default; 

    /**
     * @name: acquire()
     * @brief: lock the TAS lock before entering critical region
     */
    void acquire();

    /**
     * @name: release()
     * @brief: unlock the TAS lock before leaving critical region
     */
    void release();

}; // class AtomicLock

#endif // TASLOCK_HPP