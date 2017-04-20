#include "cxx14_workaround.hpp"
#include <iostream>
#include <stdexcept>
#include <array>

#ifdef __linux__ 
#define WORKAROUND
 #warning building with workaround
#else
 #warning not building with workaround
#endif

// https://github.com/bitcoin/bitcoin/pull/4042
// allows building against libstdc++-dev-4.9 while avoiding
// GLIBCXX_3.4.20 dep
// This is needed because libstdc++ itself uses this API - its not
// just an issue of your code using it, ughhh
#ifdef WORKAROUND

namespace std {

 void  __throw_out_of_range_fmt(const char*, ...) __attribute__((__noreturn__));
 void  __throw_out_of_range_fmt(const char* err, ...)
 {
     // Safe and over-simplified version. Ignore the format and print it as-is.
     __throw_out_of_range(err);
 }

}
#endif

int main() {
    try {
        // https://github.com/gcc-mirror/gcc/blob/d7b41a73a78cbd6f291bf8d4090638057b964c11/libstdc%2B%2B-v3/config/abi/pre/gnu.ver#L1611
        // https://github.com/gcc-mirror/gcc/blob/d7b41a73a78cbd6f291bf8d4090638057b964c11/libstdc%2B%2B-v3/include/std/array#L208
        // https://gcc.gnu.org/ml/libstdc++/2013-09/txtxoep3wCwLb.txt
        // https://gcc.gnu.org/bugzilla/show_bug.cgi?id=60936
        std::array<int, 3> a1{ {1, 2, 3} };
        auto item = a1.at(0);
        throw std::out_of_range("hello");
    } catch (std::exception const& ex) {
        std::clog << ex.what() << "\n";
    }
    return 0;
}
