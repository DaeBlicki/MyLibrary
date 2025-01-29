/**
 * @file    : test_sort.cpp
 * @brief   : test code for sorting algorthm
 * @author  : David Blickenstorfer (DaeBlicki)
 * @date 18/11/2024
 * @copyright Developed by David Blickenstorfer (DaeBlicki)
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../include/sort.hpp"
#include "../include/Timer.hpp"
#include "algorithm"
#include "random"


// =======================================
// TEST CASES FOR SWAP() AND IS_SORTED()
// =======================================
TEST_SUITE("swap() and is_sorted()"){
    TEST_CASE("swap"){
        //< initialize two doubles
        double a = 2.;
        double b = 4.;
        //< swap the content and time 
        Blick::swap(&a, &b);
        //< check the swap
        CHECK(a == 4.);
        CHECK(b == 2.);
    }
    TEST_CASE("is_sorted() on sorted array"){
        //< Create test and sorted array
        const unsigned int arr_size = 10;
        int arr[arr_size];
        //< filling test and sorted array
        for(int i = 0; i < arr_size; i++){
            arr[i] = i;
        }
        //< check is_sorted on sorted array
        CHECK(Blick::is_sorted(arr, arr_size) == true);
    }
    TEST_CASE("is_sorted() on unsorted array"){
        //< Create test and sorted array
        const unsigned int arr_size = 10;
        int arr[arr_size];
        //< filling test and sorted array
        for(int i = 0; i < arr_size; i++){
            arr[arr_size - 1 - i] = i;
        }        
        //< check is_sorted on sorted array
        CHECK(Blick::is_sorted(arr, arr_size) == false);
    }
}

// =======================================
// TEST CASES FOR BUBBLESORT()
// =======================================
TEST_SUITE("Bubblesort"){
    TEST_CASE("Sorted array"){
        //< Create sorted array
        const unsigned int arr_size = 10;
        int arr[arr_size];
        //< filling sorted array
        for(int i = 0; i < arr_size; i++){
            arr[i] = i;
        }
        //< Sorting array with sorting algorithm
        Timer T;
        T.start();
        Blick::bubblesort(arr, arr_size);
        T.stop();
        //< check the algorithm
        MESSAGE("RUNTIME: " << T.get_elapsed_in_ns() << "ns");
        CHECK(Blick::is_sorted(arr, arr_size));
    }
    TEST_CASE("Reversed array"){
        //< Create sorted array
        const unsigned int arr_size = 10;
        int arr[arr_size];
        //< filling sorted array
        for(int i = 0; i < arr_size; i++){
            arr[arr_size - 1 - i] = i;
        }
        //< Sorting array with sorting algorithm
        Timer T;
        T.start();
        Blick::bubblesort(arr, arr_size);
        T.stop();
        //< check the algorithm
        MESSAGE("RUNTIME: " << T.get_elapsed_in_ns() << "ns");
        CHECK(Blick::is_sorted(arr, arr_size));
    }
    TEST_CASE("Specific array"){
         //< Create sorted array
        const unsigned int arr_size = 10;
        int arr[arr_size];
        //< filling sorted array
        arr[0] = 2; arr[1] = 1; arr[2] = 9; arr[3] = 5; arr[4] = 0;
        arr[5] = 3; arr[6] = 7; arr[7] = 8; arr[8] = 4; arr[9] = 6;
        //< Sorting array with sorting algorithm
        Timer T;
        T.start();
        Blick::bubblesort(arr, arr_size);
        T.stop();
        //< check the algorithm
        MESSAGE("RUNTIME: " << T.get_elapsed_in_ns() << "ns");
        CHECK(Blick::is_sorted(arr, arr_size));
    }  
    TEST_CASE("Randomized array"){
        //< Create sorted array
        const unsigned int arr_size = 10;
        int arr[arr_size];
        //< filling sorted array
        for(int i = 0; i < arr_size; i++){
            arr[i] = (rand() % 10);
        }
        //< Sorting array with sorting algorithm
        Timer T;
        T.start();
        Blick::bubblesort(arr, arr_size);
        T.stop();
        //< check the algorithm
        MESSAGE("RUNTIME: " << T.get_elapsed_in_ns() << "ns");
        CHECK(Blick::is_sorted(arr, arr_size));
    }
}


// =======================================
// TEST CASES FOR QUICKSORT()
// =======================================
TEST_SUITE("Quicksort"){
    TEST_CASE("Sorted array"){
        //< Create sorted array
        const unsigned int arr_size = 10;
        int arr[arr_size];
        //< filling sorted array
        for(int i = 0; i < arr_size; i++){
            arr[i] = i;
        }
        //< Sorting array with sorting algorithm
        Timer T;
        T.start();
        Blick::quicksort(arr, arr_size);
        T.stop();
        //< check the algorithm
        MESSAGE("RUNTIME: " << T.get_elapsed_in_ns() << "ns");
        CHECK(Blick::is_sorted(arr, arr_size));
    }
    TEST_CASE("Reversed array"){
        //< Create sorted array
        const unsigned int arr_size = 10;
        int arr[arr_size];
        //< filling sorted array
        for(int i = 0; i < arr_size; i++){
            arr[arr_size - 1 - i] = i;
        }
        //< Sorting array with sorting algorithm
        Timer T;
        T.start();
        Blick::quicksort(arr, arr_size);
        T.stop();
        //< check the algorithm
        MESSAGE("RUNTIME: " << T.get_elapsed_in_ns() << "ns");
        CHECK(Blick::is_sorted(arr, arr_size));
    }
    TEST_CASE("Specific array"){
         //< Create sorted array
        const unsigned int arr_size = 10;
        int arr[arr_size];
        //< filling sorted array
        arr[0] = 2; arr[1] = 1; arr[2] = 9; arr[3] = 5; arr[4] = 0;
        arr[5] = 3; arr[6] = 7; arr[7] = 8; arr[8] = 4; arr[9] = 6;
        //< Sorting array with sorting algorithm
        Timer T;
        T.start();
        Blick::quicksort(arr, arr_size);
        T.stop();
        //< check the algorithm
        MESSAGE("RUNTIME: " << T.get_elapsed_in_ns() << "ns");
        CHECK(Blick::is_sorted(arr, arr_size));
    }  
    TEST_CASE("Randomized array"){
        //< Create sorted array
        const unsigned int arr_size = 10;
        int arr[arr_size];
        //< filling sorted array
        for(int i = 0; i < arr_size; i++){
            arr[i] = (rand() % 10);
        }
        //< Sorting array with sorting algorithm
        Timer T;
        T.start();
        Blick::quicksort(arr, arr_size);
        T.stop();
        //< check the algorithm
        MESSAGE("RUNTIME: " << T.get_elapsed_in_ns() << "ns");
        CHECK(Blick::is_sorted(arr, arr_size));
    }
}
