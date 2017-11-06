#!/bin/bash

rm -f CMakeCache.txt
rm -rf CMakeFiles/
rm -f cmake_install.cmake

#-D CMAKE_CXX_FLAGS:string="-O1 -g -fsanitize=address -fno-omit-frame-pointer"

cmake -DCMAKE_RULE_MESSAGES:BOOL=OFF -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON -DCMAKE_BUILD_TYPE=Release .

make VERBOSE=1
