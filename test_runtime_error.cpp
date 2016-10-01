#include <iostream>
#include <stdexcept>

int main() {
    try {
        std::string msg("hello");
        throw std::runtime_error(msg);
    } catch (std::exception const& ex) {
        std::clog << ex.what() << "\n";
    }

    return 0;
}