#include <thread>
#include <iostream>
#include <mutex>
#include <chrono>

int x{0};
std::mutex mtx;

auto func() -> void {
    // Comment this lock out to exhibit the livelock
    std::lock_guard<std::mutex> lock(mtx);
    while (x == 0) {
        // Added delay for increasing the chances of a livelock ocurring
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << x << std::endl;
        x = 1 - x;
        std::cout << x << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

auto main() -> int {
    std::jthread thr1{func};
    std::jthread thr2{func};
    return 0;
}
