
#include "../include/vstats/complexity_estimator.h"
#include <vector>
using namespace complexity;

void my_algo_with_ops(const std::vector<int>& arr, long long& ops) {
    for (int x : arr) {
        for (size_t i = 0; i < arr.size() / 2; i += 2) {
            volatile int y = x * 2;
            ops++;  // Count operation
        }
    }
}

void my_algo_no_ops(const std::vector<int>& arr) {
    for (int x : arr) {
        volatile int y = x * 2;
    }
}
int main() {
    std::vector<std::vector<int>> testcases = {
        std::vector<int>(100),
        std::vector<int>(1000),
        std::vector<int>(10000),
        std::vector<int>(20000)
    };

    for (const auto& test : testcases) {
        long long ops = 0;
        auto start = std::chrono::high_resolution_clock::now();
        my_algo_with_ops(test, ops);
        auto end = std::chrono::high_resolution_clock::now();
        double time_ms = std::chrono::duration<double, std::milli>(end - start).count();

        std::string complexity = estimate_complexity(my_algo_with_ops, testcases);
        print_performance_summary(time_ms, ops, complexity);
    }

    return 0;
}
