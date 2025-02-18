/**
 * @file    : timer.cpp
 * @brief   : Source file of timer
 * @author  : David Blickenstorfer
 * 
 * @date 23/10/2024 (basic time management: start, stop, elapse)
 * @date 08/01/2025 (basic statistic: mean and standard deviation)
 * @copyright Developed by David Blickenstorfer
 */

#include "../include/Timer.hpp"
#include <stdexcept>    //< for std::runtime_error
#include <numeric>      //< for std::accumulate
#include <math.h>       //< for std::sqrt

 /**
 * @name: Timer()
 * @brief: Default Constructor
 */
Timer::Timer()
{   
    //< the initialized timer has no measurements yet, the number of
    //< measurements can be accessed over the vector data structure
    elapsed_in_sec_ = std::vector<double>();    
    elapsed_in_ns_ = std::vector<double>();     
    running_ = false;
}

/**
 * @name: Timer()
 * @brief: Copy Constructor
 */
Timer::Timer(const Timer& timer)
{
    start_ = timer.start_;
    end_ = timer.end_;
    elapsed_in_sec_ = timer.elapsed_in_sec_;
    elapsed_in_ns_ = timer.elapsed_in_ns_;
    running_ = timer.running_;
}

/**
 * @name: Timer()
 * @brief: Default Destructor
 */
Timer::~Timer()
{
    //< just use C++ default destructor :)
}

/**
 * @name: start()
 * @brief: start the time measurement
 */
void Timer::start()
{
    // check if the timer is not running
    if(running_ == true){
        throw std::runtime_error("timer::start() failed : timer is already measuring! \n");
    }
    // start the measurement
    running_ = true;
    start_ = high_res_clock::now();
}

/**
 * @name: stop()
 * @brief: stop the time measurement
 */
void Timer::stop()
{
    // stop the measurement, precondition can checked afterwards
    end_ = high_res_clock::now();
    // check if timer was running
    if(running_ == false){
        throw std::runtime_error("timer::stop() failed : timer was not measuring! \n");
    }
    // calculate the elapsed time in nanoseconds and seconds
    duration_t elapsed_in_duration_t = end_ - start_;
    double duration_in_ns = 
        double(std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_in_duration_t).count());
    double duration_in_sec = duration_in_ns / ns_to_sec_divisor_;

    // update the measurement vectors and total measured times
    elapsed_in_ns_.push_back(duration_in_ns);
    elapsed_in_sec_.push_back(duration_in_sec);

    // stop the measurements
    running_ = false;
}

/**
 * @name: reset()
 * @brief: reset the timer for new measurements
 */
void Timer::reset()
{
    elapsed_in_sec_.clear();    
    elapsed_in_ns_.clear();     
    running_ = false;
}

/**
 * @name: get_elapsed_in_ns()
 * @brief: return the last measured elapsed time in ns
 * @return double of the last elapsed time in ns
 */
double Timer::get_elapsed_in_ns() const
{
    // check if there are measurements
    if(elapsed_in_ns_.empty()){
        throw std::runtime_error("timer::get_elapsed_in_ns failed : no measurements! \n");
    }
    // return the last elapsed time
    return elapsed_in_ns_.back();
}

/**
 * @name: get_elapsed_in_sec()
 * @brief: return the last measured elapsed time in seconds
 * @return double of the last elapsed time in seconds
 */
double Timer::get_elapsed_in_sec() const
{
    // check if there are measurements
    if(elapsed_in_sec_.empty()){
        throw std::runtime_error("timer::get_elapsed_in_sec failed : no measurements! \n");
    }
    // return the last elapsed time
    return elapsed_in_sec_.back();
}

/**
 * @name: get_mean_in_ns()
 * @brief: return the average of the measured time in seconds
 * @return double of the average of the measured time in seconds
 */
double Timer::get_mean_in_ns() const
{
    // check if there are measurements
    if(elapsed_in_ns_.empty()){
        throw std::runtime_error("timer::get_mean_in_ns failed : no measurements! \n");
    }

    // calculate the mean in ns
    double mean = 0.;
    const unsigned int num_measurements = elapsed_in_ns_.size();
    for(unsigned int i = 0; i < num_measurements; i++){
        mean += elapsed_in_ns_.at(i);
    }
    mean /= num_measurements;
    return mean;
}

/**
 * @name: get_mean_in_sec()
 * @brief: return the average of the measured time in seconds
 * @return double of the average of the measured time in seconds
 */
double Timer::get_mean_in_sec() const
{
    // check if there are measurements
    if(elapsed_in_sec_.empty()){
        throw std::runtime_error("timer::get_mean_in_sec failed : no measurements! \n");
    }
    // calculate the mean in sec
    double mean = 0.;
    const unsigned int num_measurements = elapsed_in_sec_.size();
    for(unsigned int i = 0; i < num_measurements; i++){
        mean += elapsed_in_sec_.at(i);
    }
    mean /= num_measurements;
    return mean;
}

/**
 * @name: get_sd_in_sec
 * @brief: return the standard deviation of the measured time in sec
 * @return double, standard deviation of the measured time in sec
 */
double Timer::get_sd_in_sec() const
{
    // check if there are measurements
    if(elapsed_in_sec_.empty()){
        throw std::runtime_error("timer::get_sd_in_sec failed : no measurements! \n");
    }
    const unsigned int num_measurements = elapsed_in_sec_.size();
    // trivial variance if there is only one measurement
    if(num_measurements < 2){
        return 0.;
    }

    // calculate the mean and variance
    const double mean = get_mean_in_sec();
    double variance = 0.;
    for(unsigned int i = 0; i < num_measurements; i++){
        const double tmp = elapsed_in_sec_.at(i) - mean;
        variance += tmp * tmp;
    }

    // variance for sampling
    variance /= num_measurements - 1.;

    return std::sqrt(variance);
}

/**
 * @name: get_sd_in_ns
 * @brief: return the standard deviation of the measured time in ns
 * @return double, standard deviation of the measured time in ns
 */
double Timer::get_sd_in_ns() const
{
    //< check if there are measurements
    if(elapsed_in_ns_.empty()){
        throw std::runtime_error("timer::get_sd_in_ns failed : no measurements! \n");
    }
    const unsigned int num_measurements = elapsed_in_ns_.size();
    // trivial variance if there is only one measurement
    if(num_measurements < 2){
        return 0.;
    }

    // calculate the mean and variance
    const double mean = get_mean_in_ns();
    double variance = 0.;
    for(unsigned int i = 0; i < num_measurements; i++){
        const double tmp = elapsed_in_ns_.at(i) - mean;
        variance += tmp * tmp;
    }

    // variance for sampling
    variance /= num_measurements - 1.;
    
    return std::sqrt(variance);
}

/**
 * @name: get_Flop_per_sec
 * @brief: return the performance in Flops/sec for the last measurement
 * @param num_operations: size_t, number of arithmetic operations of the last measurment
 * @return double, performance of last measurement in flops per sec
 */
double Timer::get_Flop_per_sec(const size_t num_operations) const
{
    try{
        const double elapsed_in_sec = get_elapsed_in_sec();
        return num_operations / elapsed_in_sec;
    }catch(const std::runtime_error& e){
        throw std::runtime_error("timer::get_Flop_per_sec failed! : no measurements! \n");
    }
}

/**
 * @name: get_MFlop_per_sec
 * @brief: return the performance in Flops/s for the last measurement
 * @param num_operations: size_t, number of arithmetic operations of the last measurment
 * @return double, performance of last measurement in MFlops/s
 */
double Timer::get_MFlop_per_sec(const size_t num_operations) const
{
    try{
        const double elapsed_in_sec = get_elapsed_in_sec();
        return num_operations / (elapsed_in_sec * Flops_to_MFlops_divisor_);
    }catch(const std::runtime_error& e){
        throw std::runtime_error("timer::get_MFlop_per_sec failed! : no measurements! \n");
    }
}

/**
 * @name: get_GFlop_per_sec
 * @brief: return the performance in MFlops/s for the last measurement
 * @param num_operations: size_t, number of arithmetic operations of the last measurment
 * @return double, performance of last measurement in MFlops/s
 */
double Timer::get_GFlop_per_sec(const size_t num_operations) const
{
    try{
        const double elapsed_in_sec = get_elapsed_in_sec();
        return num_operations / (elapsed_in_sec * Flops_to_GFlops_divisor_);
    }catch(const std::runtime_error& e){
        throw std::runtime_error("timer::get_GFlop_per_sec failed! : no measurements! \n");
    }
}

/**
 * @name: get_mean_in_Flop_per_sec
 * @brief: calculate the average of the measured performance in Flop/sec
 * @param num_operations: size_t, number of arithmetic operations of the measurements
 * @return double, average of the measured performance in Flop/sec
 */
double Timer::get_mean_in_Flop_per_sec(const size_t num_operations) const
{
    //< check if there are measurements
    if(elapsed_in_sec_.empty()){
        throw std::runtime_error("timer::get_mean_in_Flop_per_sec : no measurements! \n");
    }
    // iterate over time measurements
    double mean = 0.;
    const unsigned int n = elapsed_in_sec_.size();
    for(unsigned int i = 0; i < n; i++){
        mean += num_operations / (elapsed_in_sec_.at(i) * n);
    }

    return mean;
}

/**
 * @name: get_mean_in_MFlop_per_sec
 * @brief: calculate the average of the measured performance in MFlop/sec
 * @param num_operations: size_t, number of arithmetic operations of the measurements
 * @return double, average of the measured performance in MFlop/sec
 */
double Timer::get_mean_in_MFlop_per_sec(const size_t num_operations) const
{
    try{
        const double mean = get_mean_in_Flop_per_sec(num_operations);
        return mean / Flops_to_MFlops_divisor_;
    }catch(const std::runtime_error& e){
        throw std::runtime_error("timer::get_mean_in_MFlop_per_sec failed! \n");
    }
}

/**
 * @name: get_mean_in_GFlop_per_sec
 * @brief: calculate the average of the measured performance in GFlop/sec
 * @param num_operations: size_t, number of arithmetic operations of the measurements
 * @return double, average of the measured performance in GFlop/sec
 */
double Timer::get_mean_in_GFlop_per_sec(const size_t num_operations) const
{
    try{
        const double mean = get_mean_in_Flop_per_sec(num_operations);
        return mean / Flops_to_GFlops_divisor_;
    }catch(const std::runtime_error& e){
        throw std::runtime_error("timer::get_mean_in_GFlop_per_sec failed! \n");
    }
}

/**
 * @name: get_sd_in_Flop_per_sec
 * @brief: return the variance of the measured performance in Flops/s
 * @param num_operations: size_t, number of arithmetic operations of the measurements
 * @return double, standard deviation of the measured performance in Flops/s
 */
double Timer::get_sd_in_Flop_per_sec(const size_t num_operations) const
{
    //< check if there are measurements
    if(elapsed_in_ns_.empty()){
        throw std::runtime_error("timer::get_sd_in_Flop_per_sec failed : no measurements! \n");
    }
    const unsigned int num_measurements = elapsed_in_sec_.size();
    // trivial variance if there is only one measurement
    if(num_measurements < 2){
        return 0.;
    }

    // create new vectors with performance
    std::vector<double> performance_in_Flop_per_sec(num_measurements);
    for(unsigned int i = 0; i < num_measurements; i++){
        performance_in_Flop_per_sec.at(i) = num_operations / elapsed_in_sec_.at(i); 
    }

    // calculate mean and variance for sampling
    const double mean = get_mean_in_Flop_per_sec(num_operations);
    double variance = 0.;
    for(unsigned int i = 0; i < num_measurements; i++){
        const double tmp = performance_in_Flop_per_sec.at(i) - mean;
        variance += tmp * tmp;
    }

    // variance for sampling
    variance /= num_measurements - 1.;
    
    return std::sqrt(variance);
}

/**
 * @name: get_sd_in_MFlop_per_sec
 * @brief: return the variance of the measured performance in MFlops/s
 * @param num_operations: size_t, number of arithmetic operations of the measurements
 * @return double, standard deviation of the measured performance in MFlops/s
 */
double Timer::get_sd_in_MFlop_per_sec(const size_t num_operations) const
{
    try{
        const double sd_in_Flop_per_sec = get_sd_in_Flop_per_sec(num_operations);
        return sd_in_Flop_per_sec / Flops_to_MFlops_divisor_;
    }catch(const std::runtime_error& e){
        throw std::runtime_error("timer::get_sd_in_MFlop_per_sec failed! \n");
    }
}

/**
 * @name: get_sd_in_GFlop_per_sec
 * @brief: return the variance of the measured performance in GFlops/s
 * @param num_operations: size_t, number of arithmetic operations of the measurements
 * @return double, standard deviation of the measured performance in GFlops/s
 */
double Timer::get_sd_in_GFlop_per_sec(const size_t num_operations) const
{
    try{
        const double sd_in_Flop_per_sec = get_sd_in_Flop_per_sec(num_operations);
        return sd_in_Flop_per_sec / Flops_to_GFlops_divisor_;
    }catch(const std::runtime_error& e){
        throw std::runtime_error("timer::get_sd_in_GFlop_per_sec failed! \n");
    }
}
