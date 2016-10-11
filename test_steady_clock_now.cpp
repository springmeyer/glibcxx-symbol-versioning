#include "cxx14_workaround.hpp"
#include <iostream>

#if __cplusplus >= 201300L

#include <chrono>

int main() {
    // https://github.com/gcc-mirror/gcc/blob/d7b41a73a78cbd6f291bf8d4090638057b964c11/libstdc%2B%2B-v3/config/abi/pre/gnu.ver#L1589-L1597
    std::chrono::steady_clock::now();
    return 0;
}

#else
    #warning "only enabled with C++14 support"

int main() {
    return 0;
}

#endif
