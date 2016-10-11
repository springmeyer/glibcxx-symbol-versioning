#include "cxx14_workaround.hpp"
#include <iostream>
#include <new>

int main() {
    std::new_handler nh = std::get_new_handler();
    if (nh) {
        std::clog << "new handler works\n";
    } else {
        std::clog << "new handler returned nullptr\n";
    }
    return 0;
}
