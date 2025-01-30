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
2) Timer : benchmarking tool in <C/C++> to measure time in ns precision
 - Timer.h : timer struct written in \<C\> based on ```time_spec``` from <time.h>
 - Timer.hpp : timer class written in <C++> based on ```high_resolution_clock``` from <chrono.h>
3) PrintUtility : Printing framework for <C/C++> to print colors in terminal based on <stdio.h>

