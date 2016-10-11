/*

c++14 with libstdc++ + g++ 4.8 headers are broken

This is described at https://llvm.org/bugs/show_bug.cgi?id=18402 and https://sourceware.org/bugzilla/show_bug.cgi?id=13566

This is fixed in >= 4.9 but for 4.8 the Sandstorm devs found this workaround:

  https://groups.google.com/forum/#!topic/sandstorm-dev/2VoASO1XALQ

*/

#ifndef __cplusplus
    #error C++ is required
#elif __cplusplus >= 201300L
    #include <initializer_list>  // force libstdc++ to include its config
    #undef _GLIBCXX_HAVE_GETS    // correct broken config
#else
    // less than C++14, no workaround should be needed
#endif
