#include "cxx14_workaround.hpp"
#include <iostream>
#include <new>

int main() {
#if __cplusplus >= 201300L
    std::new_handler nh = std::get_new_handler();
    if (nh) {
        std::clog << "new handler works\n";
    } else {
        std::clog << "new handler returned nullptr\n";
    }
#else
    #warning "only enabled with C++14 support"
#endif
    return 0;
}
