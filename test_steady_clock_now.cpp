#include "cxx14_workaround.hpp"
#include <iostream>

// http://stackoverflow.com/questions/31506594/how-do-i-test-the-version-of-libstdc-not-gcc-at-compile-time
#ifdef __linux__
    #ifndef __GLIBCXX__
        #error __GLIBCXX__ must be defined
    #elif __GLIBCXX__ == 20120301 // 4.8 on vanilla precise
        // does not work
    #else
        // >= GLIBCXX_3.4.19
        // we assume it works: known versions that work are:
        // 4.8: 20130604 upgraded on precise from ubuntu-toolchain-r
        // 4.8: 20150426 on vanilla trusty
        // 4.9: 20160726 upgraded on precise from ubuntu-toolchain-r
        // 5:   20160904 upgraded on precise from ubuntu-toolchain-r
        // 6:   20160901 upgraded on precise from ubuntu-toolchain-r
        #define SUPPORTS_STEADY_CLOCK
    #endif
#else
    #define SUPPORTS_STEADY_CLOCK
#endif

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
