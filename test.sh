#!/usr/bin/env bash

set -eu
set -o pipefail

if [[ ! -d .mason ]]; then
    git clone --depth 1 https://github.com/mapbox/mason .mason
fi

export CLANG_VERSION=${CLANG_VERSION:-3.9.0}
export PACKAGE_NAME="clang++"
./.mason/mason install ${PACKAGE_NAME} ${CLANG_VERSION}
export PATH=$(./.mason/mason prefix ${PACKAGE_NAME} ${CLANG_VERSION})/bin:${PATH}

function color_echo    { >&2 echo -e "\033[1m\033[36m* $1\033[0m"; }
function color_success { >&2 echo -e "\033[1m\033[32m* $1\033[0m"; }
function color_error   { >&2 echo -e "\033[1m\033[31m$1\033[0m"; }

export FINAL_RETURN_CODE=0

function check() {
    local RESULT=0
    nm ${1} | grep "GLIBCXX_3.4.2[0-9]" > /tmp/out.txt || RESULT=$?
    if [[ ${RESULT} != 0 ]]; then
        color_success "Success: GLIBCXX_3.4.2[0-9] not found"
    else
        color_error "$(cat /tmp/out.txt | c++filt)"
        export FINAL_RETURN_CODE=1
    fi
}

function run() {
    local RESULT=0
    ${@} || RESULT=$?
    if [[ ${RESULT} != 0 ]]; then
        export FINAL_RETURN_CODE=1
    fi
}

HEADERS=${HEADERS:-}

function build() {
    color_echo "runtime c++98 std::new_handler (${HEADERS})"
    clang++ test_runtime_error_std_string.cpp -o test_runtime_error -std=c++98
    check
}

function run_it() {
    local cpp=$1
    local std=$2
    local cmd="clang++ ${cpp} -o ./test -Wall -pedantic -std=${std}"
    if [[ $(uname -s) == 'Linux' ]]; then
        display_libstdcxx_version ${std}
        for abi in {0,1}; do
            color_echo "${std}-${cpp}-D_GLIBCXX_USE_CXX11_ABI=${abi} (${HEADERS})"
            local new_cmd="${cmd} -D_GLIBCXX_USE_CXX11_ABI=${abi}"
            echo $new_cmd
            run $new_cmd
            check ./test
            rm -f ./test
        done
    else
        color_echo "${std}-${cpp} (${HEADERS})"
        echo $cmd
        $cmd
        check ./test
        rm ./test
    fi
}

function display_libstdcxx_version() {
    # https://gcc.gnu.org/onlinedocs/libstdc++/manual/using_macros.html
    # https://github.com/gcc-mirror/gcc/blob/1c486c588e0037f4c5645317da3202c6e77ba66c/libstdc%2B%2B-v3/include/bits/c%2B%2Bconfig#L34
    echo "#include <ios>" > test.cpp
    echo "#define XSTR(x) STR(x)" >> test.cpp
    echo "#define STR(x) #x" >> test.cpp
    echo "#ifdef __GLIBCXX__" >> test.cpp
    echo "#pragma message(\"value of __GLIBCXX__: \" XSTR(__GLIBCXX__))" >> test.cpp
    echo "#else" >> test.cpp
    echo "#pragma message(\"WARNING: __GLIBCXX__ not defined\")" >> test.cpp
    echo "#endif" >> test.cpp
    echo "int main() { return 0; }" >> test.cpp
    local std=$1
    local cmd="clang++ test.cpp -o ./test -E -Wall -pedantic -std=${std}"
    echo $cmd
    ${cmd}
    rm test.cpp
    rm ./test
}

clang++ -v

for cpp in $(ls *.cpp); do
    for std in {c++98,c++11,c++14}; do
        run_it ${cpp} ${std}
    done
done

if [[ ${FINAL_RETURN_CODE} != 0 ]]; then
    false
fi
