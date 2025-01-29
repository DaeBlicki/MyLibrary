/**
 * @file    : SpinLock.hpp
 * @brief   : Header file of CAS (compare-and-swap) Lock
 * @author  : David Blickenstorfer
 * 
 * @date 21/01/2025
 * @copyright Developed by David Blickenstorfer
 */

#ifndef CASLOCK_HPP
#define CASLOCK_HPP

#include <thread>   //< allow multi-threading programming
#include <atomic>   //< allow atomic variables to protect compiler optimization

/**
 * @name: CAS() - compare-and-swap
 * @brief: Atomic operation compare-and-swap, modify memory with new_val
 * if the stored value equals old_val. Return if memory was modified.
 * @param value: pointer to atomic template class, memory of the compared variable
 * @param old_val: template class, reference value for swapping
 * @param new_val: template class, modified value for memory
 * @return: boolean, true if memory value equals old_val
 */
template <typename T>
bool CAS(T* value, T old_val, T new_val) {
    return __sync_bool_compare_and_swap(value, old_val, new_val);
}

class SpinLock
{
private:
    // can be updated into std::atomic<bool> locked_ in further implementations
    bool locked_;  //< Lock State (true = locked, false = unlocked)

public:

    /**
     * @name: SpinLock()
     * @brief: Default Constructor
     */
    SpinLock();

    /**
     * @name: SpinLock()
     * @brief: Copy Constructor
     */
    SpinLock(const SpinLock& spinLock)=default; 

    /**
     * @name: SpinLock()
     * @brief: Default Destructor
     */
    ~SpinLock()=default; 

    /**
     * @name: acquire()
     * @brief: lock the CAS lock before entering critical region
     */
    void acquire();

    /**
     * @name: release()
     * @brief: unlock the CAS lock before leaving critical region
     */
    void release();

}; // class CAS_lock

#endif // CASLOCK_HPP