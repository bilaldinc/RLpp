#!/bin/bash
mkdir build > /dev/null 2>&1

g++ src/ballcatching-test.cpp \
../build/rlinterface/environment.o \
../build/rlinterface/state.o \
../build/rlinterface/response.o \
../build/environment/ballcatching/toroidalstate.o \
../build/environment/ballcatching/ballcatchingworld.o \
-o build/ballcatching-test
echo 'Compiled!'
