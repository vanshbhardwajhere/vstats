#pragma once

// Standard Library Includes
#include <vector>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>
#include <functional>
#include <chrono>
#include <iostream>
#include <type_traits>

// Colored Console Output
#include "colors.h" 

namespace complexity {

    // ---------------------------------------------
    // Internal Utility: Estimate Big-O from log-log slope
    // ---------------------------------------------
    std::string estimate_big_o(const std::vector<int>& Ns, const std::vector<long long>& Ops) {
        int n = Ns.size();
        if (n != Ops.size() || n < 2) return "Insufficient data";

        double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;

        for (int i = 0; i < n; ++i) {
            double x = std::log10(Ns[i]);
            double y = std::log10(static_cast<double>(Ops[i]));

            sumX += x;
            sumY += y;
            sumXY += x * y;
            sumX2 += x * x;
        }

        double slope = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);

        std::ostringstream os;
        os << std::fixed << std::setprecision(2) << slope;

        if (slope < 0.5) return " O(1)";
        else if (slope < 1.2) return " O(N)";
        else if (slope < 1.8) return " O(N^1.5)";
        else if (slope < 2.2) return " O(N^2)";
        else if (slope < 2.8) return " O(N^2.5)";
        else if (slope < 3.5) return " O(N^3)";
        else return " O(N^" + os.str() + ")";
    }

    // ---------------------------------------------
    // Ops Estimator: Uses user-supplied `ops` counter
    // ---------------------------------------------
    class OpsEstimator {
        std::vector<int> Ns;
        std::vector<long long> Ops;

    public:
        void record(int N, long long operations) {
            Ns.push_back(N);
            Ops.push_back(operations);
        }

        std::string estimate() {
            return estimate_big_o(Ns, Ops);
        }
    };

    // ---------------------------------------------
    // Timer Estimator: Measures execution time
    // ---------------------------------------------
    class TimerEstimator {
        std::vector<int> Ns;
        std::vector<long long> durations;

    public:
        template <typename Func>
        void record(int N, Func func) {
            auto start = std::chrono::high_resolution_clock::now();
            func();  // Run the user function
            auto end = std::chrono::high_resolution_clock::now();

            long long duration = std::max(1LL, 
                std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());

            Ns.push_back(N);
            durations.push_back(duration);
        }

        std::string estimate() {
            return estimate_big_o(Ns, durations);
        }
    };

    // ---------------------------------------------
    // Benchmark with `ops` parameter
    // ---------------------------------------------
    template <typename Func>
    std::string benchmark(Func algo, const std::vector<std::vector<int>>& testcases, std::true_type) {
        OpsEstimator est;
        for (const auto& arr : testcases) {
            long long ops = 0;
            algo(arr, ops);
            est.record(static_cast<int>(arr.size()), ops);
        }
        return est.estimate();
    }

    // ---------------------------------------------
    // Benchmark without `ops` parameter (time-based)
    // ---------------------------------------------
    template <typename Func>
    std::string benchmark(Func algo, const std::vector<std::vector<int>>& testcases, std::false_type) {
        TimerEstimator est;
        for (const auto& arr : testcases) {
            est.record(static_cast<int>(arr.size()), [&]() {
                algo(arr);
            });
        }
        return est.estimate();
    }

    // ---------------------------------------------
    // Public Interface: Auto detect algo signature
    // ---------------------------------------------
    template <typename Func>
    std::string estimate_complexity(Func algo, const std::vector<std::vector<int>>& testcases) {
        using has_ops_param = std::is_constructible<
            std::function<void(const std::vector<int>&, long long&)>, Func
        >;
        return benchmark(algo, testcases, has_ops_param{});
    }

    // ---------------------------------------------
    // Optional: Performance Summary Printer
    // ---------------------------------------------
    void print_performance_summary(double elapsedTimeMs, long long ops, const std::string& complexityStr) {
        std::cout << BOLD << CYAN << "\n=== Performance Summary ===" << RESET << "\n";
        std::cout << GREEN   << "   Time taken:          " << RESET << elapsedTimeMs << " ms\n";
        std::cout << YELLOW  << "   Operations counted: " << RESET << ops << "\n";
        std::cout << MAGENTA << "   Estimated Complexity: " << RESET << complexityStr << "\n";
        std::cout << CYAN    << "=============================" << RESET << "\n\n";
    }

} // namespace complexity
