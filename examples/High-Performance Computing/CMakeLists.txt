# ================================================================
# CMakeLists.txt for High-Performance Computing
# author: David Blickenstorfer
# created: 03/02/25
# copyright: Developed by David Blickenstorfer
# ================================================================

##################################################################
#                   PROJECT SETTING
# Minimum required version of CMake to build the project.
cmake_minimum_required(VERSION 3.12)

# Project name and version
project("High-Performance Computing" VERSION 1.0 LANGUAGES C CUDA)

# Set the <C> 23 standard
set(C_STANDARD_REQUIRED on)
set(C_STANDARD 23)

# Set the compiler for MPI
set(CMAKE_C_COMPILER mpicc)

# Set Optimization flags
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra")

# Define ANSI color codes
string(ASCII 27 Esc)
set(Reset "${Esc}[m")
set(BoldRed "${Esc}[1;31m")
set(BoldYellow "${Esc}[1;33m")
set(BoldGreen "${Esc}[1;32m")

##################################################################
#                 PROJECT UTILS LIBRARIES

# list of spgemm source
set(utility_source
    #add .cpp files
    utils/Timer.c
)

add_library(utils STATIC ${utility_source})

##################################################################
#                          OpenMP
find_package(OpenMP REQUIRED)
if(OpenMP_FOUND)
    message(STATUS "${BoldGreen}OpenMP found.${Reset}")
    include_directories(${OMP_INCLUDE_PATH})
else()
    message(FATAL_ERROR "${BoldRed}OpenMP not found.${Reset}")
endif()

##################################################################
#                          MPI
find_package(MPI REQUIRED)
if(MPI_FOUND)
    message(STATUS "${BoldGreen}MPI found.${Reset}")
    include_directories(${MPI_INCLUDE_PATH})
    set(CMAKE_CXX_COMPILE_FLAGS ${CMAKE_CXX_COMPILE_FLAGS} ${MPI_COMPILE_FLAGS})
    set(CMAKE_CXX_LINK_FLAGS ${CMAKE_CXX_LINK_FLAGS} ${MPI_LINK_FLAGS})
else()
    message(FATAL_ERROR "${BoldRed}MPI not found.${Reset}")
endif()

##################################################################
#                   PROJECT EXAMPLE EXECUTABLES

# <C++> examples
set(examples
    #add examples name in example
    MPI_example
    OpenMP_example
)

# target_link_libraries(${example} PUBLIC matplot MPI::MPI_CXX Eigen3::Eigen OpenMP::OpenMP_CXX TBB::tbb)

foreach(example ${examples})
    add_executable(${example} ${example}.c)
    target_link_libraries(${example} utils MPI::MPI_C OpenMP::OpenMP_C)
endforeach()

##################################################################
#            PROJECT EXAMPLE EXECUTABLES WITH GPU
find_package(CUDA REQUIRED on)
if(CUDA_FOUND)
    message(STATUS "${BoldGreen}CUDA found.${Reset}")
    include_directories(${CUDA_INCLUDE_PATH})
    set(CUDA_ARCHITECTURES "60;70;75;80")
    set(CMAKE_CUDA_ARCHITECTURES ${CUDA_ARCHITECTURES})
    add_executable(CUDA_example CUDA_example.c CUDA_example.cu)
    set_target_properties(CUDA_example PROPERTIES 
        CUDA_SEPARABLE_COMPILATION ON
    )
    target_link_libraries(CUDA_example utils)
else()
    message(STATUS "${BoldRed}OpenMP not found.${Reset}")
endif()
