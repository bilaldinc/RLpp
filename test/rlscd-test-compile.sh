#!/bin/bash
mkdir build > /dev/null 2>&1

g++ src/rlscd-test.cpp \
../build/rlinterface/environment.o \
../build/rlinterface/state.o \
../build/rlinterface/response.o \
../build/environment/simplegridworld/gridstate.o \
../build/environment/simplegridworld/gridworld.o \
../build/environment/ballcatching/ballcatchingworld.o \
../build/environment/ballcatching/toroidalstate.o \
../build/agent/rl-scd/state.o \
../build/agent/rl-scd/action.o \
../build/agent/rl-scd/model.o \
../build/agent/rl-scd/rlcdagent.o \
-o build/rlscd-test
echo 'Compiled!'
