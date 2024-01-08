#include <array>
#include <iostream>
#include <string>
#include <thread>

auto main() -> int {
    auto const limit = 100;
    std::array<std::string_view, 4> const names{
        "Abdul", "Bart", "Claudia", "Divya"};
    auto const fizzbuzzer = [limit, &names]() {
        for (auto i = 1; i <= limit; ++i) {
            std::string value;
            if (i % 3 == 0) {
                value += "fizz";
            }
            if (i % 5 == 0) {
                value += "buzz";
            }
            if (value.empty()) {
                value += std::to_string(i);
            } else {
                value += "!";
            }
            std::cout << names[(i - 1) % names.size()]
                      << " says " << value << '\n';
        }
    };
    std::thread thr(fizzbuzzer);
    thr.join();
    return 0;
}
