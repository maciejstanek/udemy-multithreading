#include <mutex>
#include <atomic>
#include <vector>
#include <thread>
#include <iostream>
#include <chrono>

std::mutex print_mutex;
struct MyType {
    auto doStuff() -> void {
        std::lock_guard<std::mutex> lock(print_mutex);
        std::cout << this << " is doing stuff in thread " << std::this_thread::get_id() << std::endl;
    }
};

// MyType* myTypePtr{nullptr};
std::atomic<MyType*> myTypePtr{nullptr};
std::mutex accessMutex;

auto work() -> void {
    if (!myTypePtr) {
        std::lock_guard<std::mutex> lock(accessMutex);
        if (!myTypePtr) {
            myTypePtr = new MyType;
        }
    }
    MyType* tmpPtr = myTypePtr;
    tmpPtr->doStuff();
}

auto main() -> int {
    auto const max_count = 30;
    std::vector<std::thread> threads;
    for (auto i = 0; i < max_count; ++i) {
        threads.emplace_back(work);
    }
    for (auto i = 0; i < max_count; ++i) {
        threads[i].join();
    }
    return 0;
}
