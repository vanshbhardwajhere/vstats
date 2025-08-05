#ifndef VSTATS_LOOP_TRACKER_H
#define VSTATS_LOOP_TRACKER_H

#include <string>
#include <chrono>
#include <iostream>

namespace vstats {

class LoopTracker {
public:
    LoopTracker(const std::string& name);
    void startIteration();
    void endIteration();
    void report();

private:
    std::string name_;
    int iteration_count_;
    std::chrono::high_resolution_clock::time_point iter_start_time_;
    std::chrono::microseconds total_time_;
};

}

#endif // VSTATS_LOOP_TRACKER_H
