/**
 * @file    : sort.hpp
 * @brief   : Header file for C++ array sorting algorithm
 * The datatype MUST support following operators: < and >
 * @author  : David Blickenstorfer (DaeBlicki)
 * @date    : 18/11/2025
 * @copyright Developed by David Blickenstorfer
 */

#ifndef BLICK_SORT_HPP
#define BLICK_SORT_HPP

#include <iostream>
#include <cassert>

namespace Blick{

/**
 * @name: swap()
 * @brief: swaps the the content of the pointers
 * @author: David Blickenstorfer (DaeBlicki)
 * @param a: pointer to datatype support '<' and '>' operator
 * @param b: pointer to datatype support '<' and '>' operator
 */
template <typename T>
void swap(T* a, T* b)
{
    T tmp = *a;
    *a = *b;
    *b = tmp;
}

/**
 * @name: is_sorted()
 * @brief: checks if the array is sorted
 * @author: David Blickenstorfer (DaeBlicki)
 * @param arr: array of datatype support '<' and '>' operator
 * @param arr_size: unsigned int, number of elements in array
 * @return: boolean, return true if the array is sorted
 * @runtime: T(n) = n
 */
template <typename T>
bool is_sorted(T* arr, const unsigned int n)
{
    const unsigned int it = n-1;
    for(unsigned int i = 0; i < it; i++){
        if(arr[i] > arr[i+1]){
            return false;
        }
    }
    return true;
}

/**
 * @name: print_array()
 * @brief: print array for debugging
 * @author: David Blickenstorfer (DaeBlicki)
 * @param arr: array of datatype support '<' and '>' operator
 * @param arr_size: unsigned int, number of elements in array
 * @return: boolean, return true if the array is sorted
 * @runtime: T(n) = n
 */
template <typename T>
void print_array(T* arr, const unsigned int n)
{
    const unsigned int it = n-1;
    for(unsigned int i = 0; i < it; i++){
        std::cout << arr[i] << " ";
    }
}

/**
 * @name: bubblesort()
 * @brief: placing the biggest element at the end of the container
 * by swapping with the next element
 * @author: David Blickenstorfer (DaeBlicki)
 * @param arr: array of datatype support '<' and '>' operator
 * @param arr_size: unsigned int, number of elements in array
 * @average_runtime: T(n) = n*n
 * @worst_runtime: T(n) = n*n
 */
template <typename T>
void bubblesort(T* arr, const unsigned int arr_size)
{
    for(int i = 0; i < arr_size; i++){
        for(int j = i+1; j < arr_size; j++){
            if(arr[i] > arr[j]){
                Blick::swap(&arr[i], &arr[j]);
            }
        }
    }
}   

/**
 * @name: quicksort()
 * @brief: placing the current pivot element at the right place in array
 * smaller numbers are on the left side and bigger numbers are on the right side
 * @author: David Blickenstorfer (DaeBlicki)
 * @param arr: array of datatype support '<' and '>' operator
 * @param arr_size: unsigned int, number of elements in array
 * @average_runtime: T(n) = n*log(n)
 * @worst_runtime: T(n) = n*n
 */
template <typename T>
void quicksort(T* arr, const unsigned int arr_size)
{
    if(arr_size <= 0){
        return;
    }
    //< create tool variables for the quicksort algorithm
    T* pivot_element = arr;
    T* compare_element = arr + arr_size - 1;
    bool pivot_is_left = true;
    const unsigned int iterations = arr_size - 1;

    //< quicksort pivoting algorithm
    for(int i = 0; i < iterations; i++){
        //< pivot element is on the left side and bigger
        //< need to swap and increment compare_element (change boolean)
        if(*pivot_element > *compare_element && pivot_is_left){
            Blick::swap(pivot_element, compare_element);
            T* next = pivot_element + 1;
            pivot_element = compare_element;
            compare_element = next;
            pivot_is_left = !pivot_is_left;
        }
        //< pivot element is on the left side and smaller
        //< no need to swap and decrement compare element
        else if(*pivot_element <= *compare_element && pivot_is_left){
            compare_element = compare_element - 1;
        }
        //< pivot element is on the right side and smaller
        //< need to swap and decrement compare element (change boolean)
        else if(*pivot_element < *compare_element && !pivot_is_left){
            Blick::swap(pivot_element, compare_element);
            T* next = pivot_element - 1;
            pivot_element = compare_element;
            compare_element = next;
            pivot_is_left = !pivot_is_left;
        }
        //< pivot element is on the right side and bigger
        //< no need to swap and increment compare element
        else if(*pivot_element >= *compare_element && !pivot_is_left){
            compare_element = compare_element + 1;
        }
    }
    //< create two arrays for divide and conquer
    T* left_ptr = arr;
    const unsigned int left_size = pivot_element - &arr[0];
    T* right_ptr = pivot_element + 1;
    const unsigned int right_size = &arr[arr_size-1] - pivot_element;
    Blick::quicksort(left_ptr, left_size);
    Blick::quicksort(right_ptr, right_size);
}


} // namespace Blick

#endif // BLICK_SORT_HPP