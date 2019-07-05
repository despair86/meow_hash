#!/bin/sh

set -eu

if [[ `uname -s` = "SunOS" ]];
then
	ARCH_FLAGS="-xarch=avx -xarch=aes"
	ARCH_FLAGS_2="-xarch=avx2 -xarch=aes"
	CXX=${CXX:-CC}
else
	ARCH_FLAGS="-mavx -maes"
	ARCH_FLAGS_2="-mavx2 -maes"
	CXX=${CXX:-clang++}
fi

mkdir -p build
${CXX} $* -I. meow_example.cpp -O3 ${ARCH_FLAGS} -o build/meow_example
${CXX} $* -I. util/meow_test.cpp -O3 ${ARCH_FLAGS} -o build/meow_test
${CXX} $* -I. util/meow_search.cpp -O3 ${ARCH_FLAGS} -o build/meow_search
${CXX} $* -I. util/meow_bench.cpp -O3 ${ARCH_FLAGS_2} -o build/meow_bench
