#include <chrono>
#include <future>
#include <iostream>
#include <thread>

auto main() -> int {
    auto const adder = [](std::promise<int>& prom, int a, int b) {
        std::cout << "adder computes the result for \"" << a << "\" and \"" << b
                  << "\"" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "adder sets the promised value" << std::endl;
        prom.set_value(a + b);
    };
    auto const printer = [](std::future<int>& fut) {
        std::cout << "printer boots up" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "printer awaits" << std::endl;
        auto value = fut.get();
        std::cout << "printer got \"" << value << "\"" << std::endl;

    };

    std::cout << "starting" << std::endl;
    std::promise<int> prom;
    auto fut = prom.get_future();
    auto const a = 6;
    auto const b = 7;
    std::jthread thr1(adder, std::ref(prom), a, b);
    std::jthread thr2(printer, std::ref(fut));
    return 0;
}
