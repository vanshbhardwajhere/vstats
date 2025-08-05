
#include "../include/vstats/complexity_estimator.h"
#include <bits/stdc++.h>

// Algorithm with ops tracking
void my_algo_with_ops(const std::vector<int>& arr, long long& ops) {
    for (int x : arr) {
        for (int i = 0; i < arr.size() / 2; i += 2) {
            volatile int y = x * 2;
            ops++;  // Prevent optimization
        }
    }
}

// Algorithm without ops tracking
void my_algo_no_ops(const std::vector<int>& arr) {
    for (int x : arr) {
        volatile int y = x * 2;  // Prevent optimization
    }
}

int main() {
    std::vector<std::vector<int>> testcases = {
        std::vector<int>(100),
        std::vector<int>(1000),
        std::vector<int>(10000),
    };

    std::cout << complexity::estimate_complexity(my_algo_with_ops, testcases) << "\n";
    std::cout << complexity::estimate_complexity(my_algo_no_ops, testcases) << "\n";

    return 0;
}
