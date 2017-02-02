#include "cxx14_workaround.hpp"
#include <iostream>
#include <stdexcept>

int main() {
    try {
        // https://github.com/gcc-mirror/gcc/blob/d7b41a73a78cbd6f291bf8d4090638057b964c11/libstdc%2B%2B-v3/config/abi/pre/gnu.ver#L1611
        throw std::out_of_range("hello");
    } catch (std::exception const& ex) {
        std::clog << ex.what() << "\n";
    }
    return 0;
}
