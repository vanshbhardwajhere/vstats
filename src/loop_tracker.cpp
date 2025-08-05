#include "../include/vstats/loop_tracker.h"
#include "../include/vstats/timer.h"  // ✅ Use Timer

namespace vstats {

LoopTracker::LoopTracker(const std::string& name)
    : name_(name), iteration_count_(0), total_time_(0) {}

void LoopTracker::startIteration() {
    iter_start_time_ = std::chrono::high_resolution_clock::now();
}

void LoopTracker::endIteration() {
    auto iter_end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(iter_end_time - iter_start_time_);
    total_time_ += duration;
    iteration_count_++;
}

void LoopTracker::report() {
    std::cout << "[vstats::LoopTracker] " << name_ << " ran " << iteration_count_
              << " iterations in " << total_time_.count() << " microseconds" << std::endl;
}

}
