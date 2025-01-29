#include <iostream>
#include <stdlib.h>

#include <thread>
#include "../include/SpinLock.hpp"
#include "../include/AtomicLock.hpp"

template<typename Lock>
void critical_section(int thread_id, Lock& lock) {
    lock.acquire();
    std::cout << "Thread " << thread_id << " in critical section.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate work
    std::cout << "Thread " << thread_id << " leaving critical section.\n";
    lock.release();
}

void test_CAS();

void test_TAS();

int main() 
{
    test_CAS();
    std::cout <<  "\n";
    test_TAS();
    return 0;
}

void test_CAS()
{
    SpinLock CAS_Lock;  //< initialize spinLock (CAS Lock)

    // test spinLock based on CAS (compare-and-swap)
    printf("\033[1;33mTesting SpinLock based on CAS (compare-and-swap)!.\033[0m\n");

    std::thread t1(critical_section<SpinLock>, 1, std::ref(CAS_Lock));
    std::thread t2(critical_section<SpinLock>, 2, std::ref(CAS_Lock));
    std::thread t3(critical_section<SpinLock>, 3, std::ref(CAS_Lock));
    std::thread t4(critical_section<SpinLock>, 4, std::ref(CAS_Lock));   

    // join all threads
    t1.join();
    t2.join();
    t3.join();
    t4.join();
}

void test_TAS()
{
    AtomicLock TAS_Lock;    //< initialize atomicLock (TAS)

    // test spinLock based on TAS (test-and-set)
    printf("\033[1;33mTesting AtomicLock based on TAS (test-and-set)!.\033[0m\n");

    std::thread t1(critical_section<AtomicLock>, 1, std::ref(TAS_Lock));
    std::thread t2(critical_section<AtomicLock>, 2, std::ref(TAS_Lock));
    std::thread t3(critical_section<AtomicLock>, 3, std::ref(TAS_Lock));
    std::thread t4(critical_section<AtomicLock>, 4, std::ref(TAS_Lock));

    // join all threads
    t1.join();
    t2.join();
    t3.join();
    t4.join();
}

