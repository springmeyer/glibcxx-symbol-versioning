#include "cxx14_workaround.hpp"
#include <iostream>
#include <stdexcept>

int main() {
    try {
        std::string hello("hello");
        throw std::runtime_error(hello);
    } catch (std::exception const& ex) {
        std::clog << ex.what() << "\n";
    }
    return 0;
}
