# MyLibrary
This is my personal <C/C++> Utility Library for reusablity.

## General Information
All code can be used for any applications. 

> [!NOTE]
> The author does not guarantee the correctness of the written code in this libray!

## Content
1) Locks : high-performance computing tool in <C++> to prevent multiple threads in critical region
- AtomicLock.hpp : based on TAS (test-and-set)
- SpinLock.hpp : based on CAS (compare-and-swap)
2) Timer : Benchmarking tool in <C/C++> to measure time in ns precision
 - Timer.h : Timer struct written in \<C\> based on ```time_spec``` from <time.h>
 - Timer.hpp : Timer class written in <C++> based on ```high_resolution_clock``` from <chrono.h>
3) PrintUtility : Printing framework for <C/C++> to print colors in terminal based on <stdio.h>
4) High-Performance Computing: Example codes for parallel programming in \<C\> 
- CUDA : Application programming interface for parallel computing on GPU
- OpenMP : Application programming interface for multiprocessing on shared memory
- MPI : Message Passing Interface, Library for two-sided communication on distributed memory
