#include "../include/vstats/loop_tracker.h"

int main() {
    vstats::LoopTracker tracker("Simple Loop");

    for (int i = 0; i < 5; ++i) {
        tracker.startIteration();

        // Simulate some work
        volatile int dummy = 0;
        for (int j = 0; j < 1000000; ++j) {
            dummy += j;
        }

        tracker.endIteration();
    }

    tracker.report();
    return 0;
}
