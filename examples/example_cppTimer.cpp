/**
 * @file    : exampe_cppTimer.cpp
 * @brief   : Documentation code for the usage of Timer (C++)
 * @author  : David Blickenstorfer
 * 
 * @date 28/01/2025
 * @copyright Developed by David Blickenstorfer
 */

#include "../include/Timer.hpp"
#include <iostream>

int main(int argc, char* argv[]) 
{
    // create Timer class
    Timer myTimer;

    // Start the time measurement
    myTimer.start();

    // Calculate the sum of n = 0 + 1 + 2 ... + 10000
    unsigned int sum = 0;
    for(unsigned int i = 0; i < 1000000; i++){
        sum += i;
    }

    // Stop the time measurement
    myTimer.stop();

    // print out the result
    std::cout << "The sum of 0 up to 1000000 is " << sum << "\n";
    std::cout << "Elapsed time in ns : " << myTimer.get_elapsed_in_ns() << "\n";
    std::cout << "Elapsed time in sec : " << myTimer.get_elapsed_in_sec() << "\n";
    std::cout << "Performance in Flop/s : " << myTimer.get_Flop_per_sec(1000000) << "\n";
    std::cout << "Performance in MFlop/s : " << myTimer.get_MFlop_per_sec(1000000) << "\n";
    std::cout << "Performance in GFlop/s : " << myTimer.get_GFlop_per_sec(1000000) << "\n";


    // reset the timer
    std::cout << "\n";
    myTimer.reset();

    // calculate the sum of n = 0 + 1 + 2 + ... + 10000 for 5 times
    std::cout << "Calculate the sum from 0 to 1000000 for 5 times \n";
    for(unsigned int i = 0; i < 5; i++){
        myTimer.start();
        unsigned int sum_mean = 0;
        for(unsigned int j = 0; j < 1000000; j++){
            sum_mean += j;
        }
        myTimer.stop();
        if(sum != sum_mean){
            std::cout << "invalid result: sum != sum_mean \n";
        }
    }

    std::cout << "Elapsed mean in ns : " << myTimer.get_mean_in_ns() << "\n";
    std::cout << "standard deviaction in ns : " << myTimer.get_sd_in_ns() << "\n";
    std::cout << "Elapsed mean in sec : " << myTimer.get_mean_in_sec() << "\n";
    std::cout << "standard deviaction in sec : " << myTimer.get_sd_in_sec() << "\n";

    std::cout << "\n";

    std::cout << "average Performance in Flop/s : " << myTimer.get_mean_in_Flop_per_sec(1000000) << "\n";
    std::cout << "standard deviation in Flop/s : " << myTimer.get_sd_in_Flop_per_sec(1000000) << "\n";
    std::cout << "average Performance in MFlop/s : " << myTimer.get_mean_in_MFlop_per_sec(1000000) << "\n";
    std::cout << "standard deviation in MFlop/s : " << myTimer.get_sd_in_MFlop_per_sec(1000000) << "\n";
    std::cout << "average Performance in GFlop/s : " << myTimer.get_mean_in_GFlop_per_sec(1000000) << "\n";
    std::cout << "standard deviation in GFlop/s : " << myTimer.get_sd_in_GFlop_per_sec(1000000) << "\n";

    return 0;
}