#include "cxx14_workaround.hpp"
#include <iostream>
#include <new>

// http://stackoverflow.com/questions/31506594/how-do-i-test-the-version-of-libstdc-not-gcc-at-compile-time
#ifdef __linux__
    #ifndef __GLIBCXX__
        #error __GLIBCXX__ must be defined
    #elif __GLIBCXX__ == 20120301 // 4.8 on vanilla precise
        // does not work
    #elif __GLIBCXX__ == 20130604 // 4.8 upgraded on precise
        // does not work
    #elif __GLIBCXX__ == 20150426 // 4.8 on vanilla precise
        // does not work
    #else
        // we assume it works: known version that work from ubuntu-toolchain-r are:
        // 4.9: 20160726
        // 5:   20160904
        // 6:   20160901
        #define SUPPORTS_NEW_HANDLER
    #endif
#else
    #define SUPPORTS_NEW_HANDLER
#endif

int main() {
#if __cplusplus >= 201300L && defined(SUPPORTS_NEW_HANDLER)
    // https://github.com/gcc-mirror/gcc/blob/d7b41a73a78cbd6f291bf8d4090638057b964c11/libstdc%2B%2B-v3/config/abi/pre/gnu.ver#L1599-L1602
    std::new_handler nh = std::get_new_handler();
    if (nh) {
        std::clog << "new handler works\n";
    } else {
        std::clog << "new handler returned nullptr\n";
    }
#else
    #if __cplusplus >= 201300L
        #warning "c++14 support is available, but GLIBCXX is too old to support new handler"
    #else
        #warning "only enabled with C++14 support"
    #endif
#endif
    return 0;
}
