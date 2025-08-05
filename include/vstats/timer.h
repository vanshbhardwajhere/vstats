#ifndef VSTATS_TIMER_H
#define VSTATS_TIMER_H

#include <chrono>
#include <string>

namespace vstats {

class Timer {
public:
    Timer(const std::string& name = "Unnamed Timer");
    ~Timer();

    void start();
    void stop();

    // ✅ Add this function
    long long elapsed_microseconds() const;

private:
    std::string name_;
    std::chrono::high_resolution_clock::time_point start_time_;
    std::chrono::high_resolution_clock::time_point end_time_; // Added
    bool running_;
};

} // namespace vstats

#endif // VSTATS_TIMER_H
