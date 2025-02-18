/**
 * @file    : Timer.hpp
 * @brief   : Header file for Timer class in C++
 * @author  : David Blickenstorfer
 * 
 * @date 23/10/2024 (basic time management: start, stop, elapse)
 * @date 08/01/2025 (basic statistic: mean and standard deviation)
 * @date 29/01/2025 (refactoring comments)
 * @date 17/02/2025 (basic performance management: flops_per_seconds)
 * standard deviation sd instead of variance
 * @copyright Developed by David Blickenstorfer
 */

#ifndef TIMER_HPP   
#define TIMER_HPP

#include <chrono>
#include <vector>

typedef std::chrono::high_resolution_clock high_res_clock;
typedef std::chrono::duration<double> duration_t;

/**
 * @name: Timer
 * @brief: class for measuring time in ns precision and performance in Flops/s
 */
class Timer
{
private:
    // divide measured time in nanoseconds with this constant 
    // to get measured time in seconds
    static const unsigned int ns_to_sec_divisor_ = 1e9;
    static const unsigned int Flops_to_MFlops_divisor_ = 1e6;
    static const unsigned int Flops_to_GFlops_divisor_ = 1e9;

    // store the time of the start and end of the measurement
    high_res_clock::time_point start_;   //< store the starting time
    high_res_clock::time_point end_;     //< store the ending time

    // store the measurements as vectors of duration type
    std::vector<double> elapsed_in_sec_;    //< store measurements in seconds
    std::vector<double> elapsed_in_ns_;     //< store measurements in nanoseconds

    bool running_;  //< store the running variable of timer

public:

    /**
     * @name: Timer
     * @brief: Default Constructor
     */
    Timer();

    /**
     * @name: Timer
     * @brief: Copy Constructor
     */
    Timer(const Timer& timer); 

    /**
     * @name: Timer
     * @brief: Default Destructor
     */
    ~Timer(); 

    /**
     * @name: start
     * @brief: start the time measurement
     */
    void start();

    /**
     * @name: stop
     * @brief: stop the time measurement
     */
    void stop();

    /**
     * @name: reset
     * @brief: reset the timer for new measurements
     */
    void reset();

    /**
     * @name: get_elapsed_in_ns
     * @brief: return the last measured elapsed time in ns
     * @return double, last measured elapsed time in ns
     */
    double get_elapsed_in_ns() const;

    /**
     * @name: get_elapsed_in_sec
     * @brief: return the last measured elapsed time in seconds
     * @return double, last measured elapsed time in seconds
     */
    double get_elapsed_in_sec() const;

    /**
     * @name: get_mean_in_ns
     * @brief: return the average of the measured time in ns
     * @return double, average of the measured time in ns
     */
    double get_mean_in_ns() const;

    /**
     * @name: get_mean_in_sec
     * @brief: return the average of the measured time in seconds
     * @return double, average of the measured time in seconds
     */
    double get_mean_in_sec() const;

    /**
     * @name: get_sd_in_sec
     * @brief: return the standard deviation of the measured time in sec
     * @return double, standard deviation of the measured time in sec
     */
    double get_sd_in_sec() const;

    /**
     * @name: get_sd_in_ns
     * @brief: return the standard deviation of the measured time in ns
     * @return double, standard deviation of the measured time in ns
     */
    double get_sd_in_ns() const;

    /**
     * @name: get_Flop_per_sec
     * @brief: return the performance in Flops/sec for the last measurement
     * @param num_operations: size_t, number of arithmetic operations of the last measurment
     * @return double, performance of last measurement in flops per sec
     */
    double get_Flop_per_sec(const size_t num_operations) const;

    /**
     * @name: get_MFlop_per_sec
     * @brief: return the performance in Flops/s for the last measurement
     * @param num_operations: size_t, number of arithmetic operations of the last measurment
     * @return double, performance of last measurement in MFlops/s
     */
    double get_MFlop_per_sec(const size_t num_operations) const;

    /**
     * @name: get_GFlop_per_sec
     * @brief: return the performance in MFlops/s for the last measurement
     * @param num_operations: size_t, number of arithmetic operations of the last measurment
     * @return double, performance of last measurement in MFlops/s
     */
    double get_GFlop_per_sec(const size_t num_operations) const;

    /**
     * @name: get_mean_in_Flop_per_sec
     * @brief: calculate the average of the measured performance in Flop/sec
     * @param num_operations: size_t, number of arithmetic operations of the measurements
     * @return double, average of the measured performance in Flop/sec
     */
    double get_mean_in_Flop_per_sec(const size_t num_operations) const;

    /**
     * @name: get_mean_in_MFlop_per_sec
     * @brief: calculate the average of the measured performance in MFlop/sec
     * @param num_operations: size_t, number of arithmetic operations of the measurements
     * @return double, average of the measured performance in MFlop/sec
     */
    double get_mean_in_MFlop_per_sec(const size_t num_operations) const;

    /**
     * @name: get_mean_in_GFlop_per_sec
     * @brief: calculate the average of the measured performance in GFlop/sec
     * @param num_operations: size_t, number of arithmetic operations of the measurements
     * @return double, average of the measured performance in GFlop/sec
     */
    double get_mean_in_GFlop_per_sec(const size_t num_operations) const;

    /**
     * @name: get_sd_in_Flop_per_sec
     * @brief: return the variance of the measured performance in Flops/s
     * @param num_operations: size_t, number of arithmetic operations of the measurements
     * @return double, standard deviation of the measured performance in Flops/s
     */
    double get_sd_in_Flop_per_sec(const size_t num_operations) const;

    /**
     * @name: get_sd_in_MFlop_per_sec
     * @brief: return the variance of the measured performance in MFlops/s
     * @param num_operations: size_t, number of arithmetic operations of the measurements
     * @return double, standard deviation of the measured performance in MFlops/s
     */
    double get_sd_in_MFlop_per_sec(const size_t num_operations) const;

    /**
     * @name: get_sd_in_GFlop_per_sec
     * @brief: return the variance of the measured performance in GFlops/s
     * @param num_operations: size_t, number of arithmetic operations of the measurements
     * @return double, standard deviation of the measured performance in GFlops/s
     */
    double get_sd_in_GFlop_per_sec(const size_t num_operations) const;

}; // class timer


#endif //TIMER_HPP