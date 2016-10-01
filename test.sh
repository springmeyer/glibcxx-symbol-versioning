#!/usr/bin/env bash

set -eu
set -o pipefail

if [[ ! -d .mason ]]; then
    git clone --depth 1 -b llvm-3.9.0 https://github.com/mapbox/mason .mason
fi

export CLANG_VERSION=${CLANG_VERSION:-3.9.0}
export PACKAGE_NAME="clang++"
./.mason/mason install ${PACKAGE_NAME} ${CLANG_VERSION}
export PATH=$(./.mason/mason prefix ${PACKAGE_NAME} ${CLANG_VERSION})/bin:${PATH}

function color_echo    { >&2 echo -e "\033[1m\033[36m* $1\033[0m"; }

function check() {
    RESULT=0
    nm test_runtime_error | grep GLIBCXX_3.4.2 > /tmp/out.txt || RESULT=$?
    if [[ ${RESULT} != 0 ]]; then
        echo "GLIBCXX_3.4.2 not found"
    else
        cat /tmp/out.txt | c++filt
    fi
}

HEADERS=${HEADERS:-}

color_echo "runtime c++98 std::runtime_error(<cstring>) (${HEADERS})"
clang++ test_runtime_error_cstring.cpp -o test_runtime_error -std=c++98
check

color_echo "runtime c++11 std::runtime_error(<cstring>) (${HEADERS})"
clang++ test_runtime_error_cstring.cpp -o test_runtime_error -std=c++11
check

color_echo "runtime c++14 std::runtime_error(<cstring>) (${HEADERS})"
# bails on stock trusty due to https://llvm.org/bugs/show_bug.cgi?id=18402
clang++ test_runtime_error_cstring.cpp -o test_runtime_error -std=c++14
check

color_echo "runtime c++98 std::runtime_error(<std::string>) (${HEADERS})"
clang++ test_runtime_error_std_string.cpp -o test_runtime_error -std=c++98
check

color_echo "runtime c++11 std::runtime_error(<std::string>) -D_GLIBCXX_USE_CXX11_ABI=0 (${HEADERS})"
clang++ test_runtime_error_std_string.cpp -o test_runtime_error -std=c++11 -D_GLIBCXX_USE_CXX11_ABI=0
check

color_echo "runtime c++11 std::runtime_error(<std::string>) -D_GLIBCXX_USE_CXX11_ABI=1 (${HEADERS})"
clang++ test_runtime_error_std_string.cpp -o test_runtime_error -std=c++11 -D_GLIBCXX_USE_CXX11_ABI=1
check

color_echo "runtime c++14 std::runtime_error(<std::string>) -D_GLIBCXX_USE_CXX11_ABI=0 (${HEADERS})"
# bails on stock trusty due to https://llvm.org/bugs/show_bug.cgi?id=18402
clang++ test_runtime_error_std_string.cpp -o test_runtime_error -std=c++14 -D_GLIBCXX_USE_CXX11_ABI=0
check

color_echo "runtime c++14 std::runtime_error(<std::string>) -D_GLIBCXX_USE_CXX11_ABI=1 (${HEADERS})"
# bails on stock trusty due to https://llvm.org/bugs/show_bug.cgi?id=18402
clang++ test_runtime_error_std_string.cpp -o test_runtime_error -std=c++14 -D_GLIBCXX_USE_CXX11_ABI=1
check
