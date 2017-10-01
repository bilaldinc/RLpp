#!/bin/bash
g++ src/qlearning-state-test.cpp \
../build/rlinterface/environment.o \
../build/rlinterface/state.o \
../build/rlinterface/response.o \
../build/environment/simplegridworld/gridstate.o \
../build/agent/qlearning/state.o \
../build/agent/qlearning/action.o \
-o build/qlearning-state-test
echo 'Compiled!'
