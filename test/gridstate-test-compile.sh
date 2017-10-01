#!/bin/bash
mkdir build > /dev/null 2>&1

g++ src/grid-state-test.cpp \
../build/rlinterface/environment.o \
../build/rlinterface/state.o \
../build/rlinterface/response.o \
../build/environment/simplegridworld/gridstate.o \
-o build/grid-state-test
echo 'Compiled!'
