// #include "vstats/timer.h"
// #include "../include/vstats/timer.h"
// using namespace vstats;
// #include<bits/stdc++.h>


// int main() {
//     vstats::Timer t("Test Timer");
//     int x = 0;
//     for (int i = 0; i < 1000000; ++i){
//         x += i;
//     }
//     return 0;
// }


// -------------------------------------------------------------------------------

// #include "../include/vstats/loop_tracker.h"
// using namespace vstats;

// int main() {
//     LoopTracker tracker("Loop Test");

//     for (int i = 0; i < 1000; ++i) {
//         tracker.startIteration();

//         // Simulate work
//         for (int j = 0; j < 1000; ++j);

//         tracker.endIteration();
//     }

//     tracker.report();
//     return 0;
// }



// --------------------------------------------------------------------------


// #include <iostream>
// #include "../include/vstats/big_o_estimator.h"

// int main() {
//     std::vector<int> Ns = {100, 200, 400, 800, 1600};
//     std::vector<long long> Ops = {100, 200, 400, 800, 1600};

//     std::string result = vstats::estimate_big_o(Ns, Ops);
//     std::cout << "[vstats::BigOEstimator] Estimated Time Complexity: " << result << std::endl;

//     return 0;
// }



// ----------------------------------------------------------------------------



// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <chrono>
// #include "../include/vstats/big_o_estimator.h"

// using namespace std;
// using namespace std::chrono;

// // Test function whose complexity you want to analyze
// void myFunction(int n) {
//     vector<int> arr(n);
//     for (int i = 0; i < n; ++i)
//         arr[i] = rand();

//     sort(arr.begin(), arr.end()); // You can replace this with any logic
// }

// // Runs the test on growing N and records time
// void runComplexityTest() {
//     vector<int> Ns;
//     vector<long long> Ops; // time in microseconds

//     for (int N = 100; N <= 5000; N *= 2) {
//         auto start = high_resolution_clock::now();
//         myFunction(N);
//         auto end = high_resolution_clock::now();

//         auto duration = duration_cast<microseconds>(end - start).count();

//         Ns.push_back(N);
//         Ops.push_back(duration);

//         cout << "N = " << N << ", Time = " << duration << "μs" << endl;
//     }

//     string result = vstats::estimate_big_o(Ns, Ops);
//     cout << "\nEstimated Time Complexity: " << result << endl;
// }

// int main() {
//     runComplexityTest();
//     return 0;
// }


// -------------------------------------------------------------------------------------

// #include "../include/vstats/complexity_estimator.h"
// #include <iostream>
// #include<bits/stdc++.h>
// int main() {
//     using namespace complexity;

//     TimerEstimator timer_estimator;
//     OpsEstimator ops_estimator;

//     for (int N : {100, 200, 400, 800, 1600}) {
//         // === Timer-based
//         timer_estimator.record(N, [N]() {
//             std::vector<int> v(N);
//             for (int i = 0; i < N; ++i) v[i] = i;
//             std::sort(v.begin(), v.end());
//         });

//         // === Ops-based
//         ops_estimator.reset_counter();
//         for (int i = 0; i < N; ++i) {
//             for (int j = 0; j < N; ++j) {
//                 ops_estimator.counter++;  // Simulate a basic op
//             }
//         }
//         ops_estimator.record(N);
//     }

//     std::cout << "Timer-based estimation: " << timer_estimator.estimate() << "\n";
//     std::cout << "Ops-based estimation: " << ops_estimator.estimate() << "\n";

//     return 0;
// }


// ------------------------------------------------------------------------------------


// #include <iostream>
// #include <vector>
// #include <cstdlib>
// #include "../include/vstats/complexity_estimator.h"

// using namespace complexity;

// int bruteForce(const std::vector<int>& arr, long long& ops) {
//     int maxSum = arr[0];
//     for (int i = 0; i < arr.size(); ++i) {
//         int sum = 0;
//         for (int j = i; j < arr.size(); ++j) {
//             sum += arr[j]; ops++;
//             maxSum = std::max(maxSum, sum); ops++;
//         }
//     }
//     return maxSum;
// }

// int kadane(const std::vector<int>& arr, long long& ops) {
//     int maxSum = arr[0], currentSum = arr[0]; ops += 2;
//     for (int i = 1; i < arr.size(); ++i) {
//         currentSum = std::max(arr[i], currentSum + arr[i]); ops++;
//         maxSum = std::max(maxSum, currentSum); ops++;
//     }
//     return maxSum;
// }

// int main() {
//     OpsEstimator bruteEst, kadaneEst;

//     for (int n : {50, 100, 200, 400}) {
//         std::vector<int> arr(n);
//         for (int& val : arr) val = rand() % 200 - 100;

//         benchmark("Brute", bruteForce, bruteEst, arr);
//         benchmark("Kadane", kadane, kadaneEst, arr);
//     }

//     std::cout << "\nEstimated Complexity (Brute): " << bruteEst.estimate() << "\n";
//     std::cout << "Estimated Complexity (Kadane): " << kadaneEst.estimate() << "\n";

//     return 0;
// }


// ------------------------------------------------------------------------------------------




// #include "../include/vstats/complexity_estimator.h"
// #include<bits/stdc++.h>

// void my_algo_with_ops(const std::vector<int>& arr, long long& ops) {
//     for (int x : arr) {
//         for (int i =0;i<arr.size()/2;i+=2) {
//         volatile int y = x * 2;
//         ops++;   // prevent optimization
//     }
//     }
    
// }

// void my_algo_no_ops(const std::vector<int>& arr) {
//     for (int x : arr) {
//         volatile int y = x * 2;  // prevent optimization
//     }
// }

// int main() {
//     std::vector<std::vector<int>> testcases = {
//     std::vector<int>(100),
//     std::vector<int>(1000),
//     std::vector<int>(10000),
// };


//     std::cout << complexity::estimate_complexity(my_algo_with_ops, testcases) << "\n";
//     std::cout << complexity::estimate_complexity(my_algo_no_ops, testcases) << "\n";

//     return 0;
// }



// ----------------------------------------------------------------------------------

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
