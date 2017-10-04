#!/bin/bash
mkdir build > /dev/null 2>&1

g++ src/qlearning-scd-agent-test.cpp \
../build/rlinterface/environment.o \
../build/rlinterface/state.o \
../build/rlinterface/response.o \
../build/environment/simplegridworld/gridstate.o \
../build/environment/simplegridworld/gridworld.o \
../build/agent/qlearning-scd/state.o \
../build/agent/qlearning-scd/action.o \
../build/agent/qlearning-scd/qlearningagent.o \
-o build/qlearning-scd-agent-test
echo 'Compiled!'
