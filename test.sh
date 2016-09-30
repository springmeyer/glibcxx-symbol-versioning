#!/usr/bin/env bash

set -eu
set -o pipefail

if [[ ! -d .mason ]]; then
    git clone --depth 1 -b llvm-3.9.0 https://github.com/mapbox/mason .mason
fi

export CLANG_VERSION=${CLANG_VERSION:-3.9.0}
export PACKAGE_NAME="clang++"
./.mason/mason install ${PACKAGE_NAME} ${CLANG_VERSION}
export PATH=$(./.mason/mason prefix ${PACKAGE_NAME} ${CLANG_VERSION})/bin)

echo "runtime c++98"
clang++ test_runtime_error.cpp -o test_runtime_error -std=c++98
strings test_runtime_error

echo "runtime c++11"
clang++ test_runtime_error.cpp -o test_runtime_error -std=c++11
strings test_runtime_error

echo "runtime c++14"
clang++ test_runtime_error.cpp -o test_runtime_error -std=c++14
strings test_runtime_error