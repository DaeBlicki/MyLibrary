/**
 * @file    : test_timer.cpp
 * @brief   : test code of timer
 * @author  : David Blickenstorfer
 * 
 * @date 16/01/2024 (implementation start and stop)
 * @date 23/10/2024 (refactoring) 
 * @copyright Developed by David Blickenstorfer
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../include/Timer.hpp"

/**
 * @brief test function for timer::start() and timer::stop()
 */
TEST_SUITE("Start and Stop"){
    //< Test stop after initialization
    TEST_CASE("Stop after initialization"){
        REQUIRE_NOTHROW(Timer T);
        Timer T;
        CHECK_THROWS(T.stop());
    }
    //< Test start after initialization
    TEST_CASE("Start after initialization"){
        Timer T;
        CHECK_NOTHROW(T.start());
    }
    //< Test Start after start
    TEST_CASE("Start after start"){
        Timer T;
        T.start();
        CHECK_THROWS(T.start());
    }
    //< Test stop after start
    TEST_CASE("Stop after start"){
        Timer T;
        T.start();
        CHECK_NOTHROW(T.stop());
    }
    //< Test stop after stop
    TEST_CASE("Stop after stop"){
        Timer T;
        T.start();
        T.stop();
        CHECK_THROWS(T.stop());
    }
}
