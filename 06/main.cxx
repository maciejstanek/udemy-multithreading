#include <chrono>
#include <future>
#include <iostream>

auto main() -> int {
    std::cout << "Starting" << std::endl;
    std::packaged_task<int(int, int)> ptask([](int a, int b) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return a + b;
    });
    auto fut = ptask.get_future();
    std::thread thr(std::move(ptask), 6, 7);
    std::cout << fut.get() << std::endl;
    thr.join();
    return 0;
}
