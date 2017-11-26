#!/bin/bash
mkdir build > /dev/null 2>&1

g++ src/simple-gridworld-test.cpp \
../build/rlinterface/environment.o \
../build/rlinterface/state.o \
../build/rlinterface/response.o \
../build/environment/simplegridworld/gridstate.o \
../build/environment/simplegridworld/gridworld.o \
../build/agent/qlearning/state.o \
../build/agent/qlearning/action.o \
../build/agent/qlearning/qlearningagent.o \
-o build/simple-gridworld-test
echo 'Compiled!'
