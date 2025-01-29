# ================================================================
# CMakeLists.txt for MyLibrary
# author: David Blickenstorfer (DaeBlicki)
# created: 18/11/2024
# copyright: Developed by David Blickenstorfer
# ================================================================

# Minimum required version of CMake to build the project.
cmake_minimum_required(VERSION 3.12)

# Project name and version
project("MyLibrary" VERSION 1.0)

# Set the C++ 20 standard
set(CXX_STANDARD_REQUIRED on)
set(CXX_STANDARD 20)

# Set Optimization flags
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra")

# Add include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# list of spgemm source
set(myLibrary_cpp_source
    #add .cpp files
    src/Timer.cpp
    src/SpinLock.cpp
    src/AtomicLock.cpp
)

set(myLibrary_c_source
    # add .c files
    src/Timer.c
)

# add testing
enable_testing()

# C++ code
set(tests_cpp
    #add test names in test file
    test_timer
    test_sort
    test_lock
)

foreach(test ${tests_cpp})
    add_executable(${test} test/${test}.cpp ${myLibrary_cpp_source})
    target_include_directories(${test} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
    # target_link_libraries(${test} my_library)
    add_test(NAME ${test} COMMAND $(test))
    set_target_properties(${test} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/
        OUTPUT_NAME ${test}.exe
    )
endforeach()

#C Code
set(tests_c
    #add test names in test file
    test_print_utils
)

foreach(test ${tests_c})
    add_executable(${test} test/${test}.c ${myLibrary_c_source})
    target_include_directories(${test} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
    # target_link_libraries(${test} my_library)
    add_test(NAME ${test} COMMAND $(test))
    set_target_properties(${test} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/
        OUTPUT_NAME ${test}.exe
    )
endforeach()

set(examples_c
    #add examples name in example
)