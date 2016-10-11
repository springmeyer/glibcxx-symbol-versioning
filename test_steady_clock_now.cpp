#include "cxx14_workaround.hpp"
#include <iostream>
#include <chrono>

int main() {
#if __cplusplus >= 201300L
    // https://github.com/gcc-mirror/gcc/blob/d7b41a73a78cbd6f291bf8d4090638057b964c11/libstdc%2B%2B-v3/config/abi/pre/gnu.ver#L1589-L1597
    std::chrono::steady_clock::now();
#else
    #warning "only enabled with C++14 support"
#endif
    return 0;
}
