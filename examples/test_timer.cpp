#include "../include/vstats/timer.h"
#include <iostream>

int main() {
    vstats::Timer timer("Busy Wait Timer");
    timer.start();

    // Simulate delay using a busy loop (simple workload)
    volatile long long dummy = 0;
    for (int i = 0; i < 10000000; ++i) {
        dummy += i;
    }

    timer.stop();
    return 0;
}
