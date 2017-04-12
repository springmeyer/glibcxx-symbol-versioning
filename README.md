# glibcxx-symbol-versioning

Sample code to demonstrate how libstdc++ symbol versioning works

[![Build Status](https://travis-ci.org/springmeyer/glibcxx-symbol-versioning.svg?branch=master)](https://travis-ci.org/springmeyer/glibcxx-symbol-versioning)

Testing methods:

 - Travis jobs
 - Using the default libstdc++ packages and ones upgraded from https://launchpad.net/~ubuntu-toolchain-r/+archive/ubuntu/test
 - Studying https://github.com/gcc-mirror/gcc/blob/d7b41a73a78cbd6f291bf8d4090638057b964c11/libstdc%2B%2B-v3/config/abi/pre/gnu.ver#L1599-L1602 for when symbols arrived

Findings based on testing:

### Default precise

- libc6 2.15-0ubuntu10.10
- libstdc++6 4.6.3-1ubuntu5
- GLIBCXX_3.4.16
- Selected GCC installation: /usr/lib/gcc/x86_64-linux-gnu/4.6
- __GLIBCXX__: 20120301

### Default trusty
 - libstdc++6 4.8.4-2ubuntu1~14.04.3
 - GLIBCXX_3.4.19
 - Selected GCC installation: /usr/lib/gcc/x86_64-linux-gnu/4.8
 - __GLIBCXX__: 20150426


Bug with `-std=c++14`:

```
/usr/lib/gcc/x86_64-linux-gnu/4.8/../../../../include/c++/4.8/cstdio:120:11: error: 
      no member named 'gets' in the global namespace
  using ::gets;
        ~~^
```

### libstdc++-4.8-dev upgrade on precise (via toolchain-r)

 - libstdc++6 6.2.0-3ubuntu11~12.04
 - libgcc-4.8-dev amd64 4.8.1-2ubuntu1~12.04
 - libstdc++-4.8-dev amd64 4.8.1-2ubuntu1~12.04
 - GLIBCXX_3.4.22
 - Selected GCC installation: /usr/lib/gcc/x86_64-linux-gnu/4.8
 - __GLIBCXX__: 20130604

### libstdc++-4.9-dev upgrade on precise (via toolchain-r)

 - libstdc++6 6.2.0-3ubuntu11~12.04
 - libgcc-4.9-dev amd64 4.9.4-2ubuntu1~12.04
 - libstdc++-4.9-dev amd64 4.9.4-2ubuntu1~12.04
 - GLIBCXX_3.4.22
 - Selected GCC installation: /usr/lib/gcc/x86_64-linux-gnu/4.9
 - __GLIBCXX__: 20160726
 - std::get_new_handler()@@GLIBCXX_3.4.20

### libstdc++-5-dev upgrade on precise (via toolchain-r)

 - libstdc++6 6.2.0-3ubuntu11~12.04
 - libgcc-5-dev amd64 5.4.1-2ubuntu1~12.04
 - libstdc++-5-dev amd64 5.4.1-2ubuntu1~12.04
 - GLIBCXX_3.4.22
 - Selected GCC installation: /usr/lib/gcc/x86_64-linux-gnu/5.4.1
 - __GLIBCXX__: 20160904
 - std::out_of_range::out_of_range(char const*)@@GLIBCXX_3.4.21
 - std::__codecvt_utf8_utf16_base<wchar_t>::do_encoding() const@@GLIBCXX_3.4.21
 - std::runtime_error::runtime_error(char const*)@@GLIBCXX_3.4.21

### libstdc++-6-dev upgrade on precise (via toolchain-r)

 - libstdc++6 6.2.0-3ubuntu11~12.04
 - libgcc-6-dev amd64 6.2.0-3ubuntu11~12.04
 - libstdc++-6-dev amd64 6.2.0-3ubuntu11~12.04
 - GLIBCXX_3.4.22
 - Selected GCC installation: /usr/lib/gcc/x86_64-linux-gnu/6.2.0
 - __GLIBCXX__: 20160901
 - std::__codecvt_utf8_utf16_base<wchar_t>::do_encoding() const@@GLIBCXX_3.4.21
 - std::runtime_error::runtime_error(char const*)@@GLIBCXX_3.4.21


libstdc++ version on all linux distros: https://pkgs.org/download/libstdc++6



