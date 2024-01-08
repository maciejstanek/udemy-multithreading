#include <iostream>
#include <thread>
#include <vector>
#include <utility>
#include <algorithm>

int global = 0;

auto increment() -> void {
    for (auto i = 0; i < 100'000; ++i, ++global) {}
}

auto main() -> int {
    auto const max_thread_count = 10;
    for (auto thread_count = 1; thread_count < max_thread_count; ++thread_count) {
        global = 0;
        std::vector<std::thread> pool;
        for (auto count = 0; count < thread_count; ++count) {
            pool.emplace_back(increment);
        }
        std::for_each(pool.rbegin(), pool.rend(), [](auto& thr) { thr.join(); });
        std::cout << "For thread count " << thread_count << " the result is " << global << std::endl;
    } 
    return 0;
}
