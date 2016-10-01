#include <iostream>
#include <stdexcept>

int main() {
    try {
        throw std::runtime_error("hello");
    } catch (std::exception const& ex) {
        std::clog << ex.what() << "\n";
    }

    return 0;
}