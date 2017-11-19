#!/bin/bash
mkdir build > /dev/null 2>&1

g++ src/ps-test.cpp \
../build/rlinterface/environment.o \
../build/rlinterface/state.o \
../build/rlinterface/response.o \
../build/environment/simplegridworld/gridstate.o \
../build/environment/simplegridworld/gridworld.o \
../build/agent/prioritized-sweeping/state.o \
../build/agent/prioritized-sweeping/action.o \
../build/agent/prioritized-sweeping/model.o \
../build/agent/prioritized-sweeping/prioritizedsweepingagent.o \
-o build/ps-test
echo 'Compiled!'
