// vstats/timer.cpp

#include "../include/vstats/timer.h"
#include <iostream>

namespace vstats {

Timer::Timer(const std::string& name)
    : name_(name), running_(false) {}

Timer::~Timer() {
    if (running_) {
        stop();
    }
}

void Timer::start() {
    running_ = true;
    start_time_ = std::chrono::high_resolution_clock::now();
}

void Timer::stop() {
    if (running_) {
        end_time_ = std::chrono::high_resolution_clock::now();  // FIXED!
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time_ - start_time_);
        std::cout  << name_ << ": " << duration.count() << " microseconds\n";
        running_ = false;
    }
}


long long Timer::elapsed_microseconds() const {
    return std::chrono::duration_cast<std::chrono::microseconds>(end_time_ - start_time_).count();
}

} // namespace vstats
