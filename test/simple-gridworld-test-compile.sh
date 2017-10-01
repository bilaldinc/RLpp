#!/bin/bash
g++ src/simple-gridworld-test.cpp \
../build/rlinterface/environment.o \
../build/rlinterface/state.o \
../build/rlinterface/response.o \
../build/environment/simplegridworld/gridstate.o \
../build/environment/simplegridworld/gridworld.o \
-o build/simple-gridworld-test
echo 'Compiled!'
