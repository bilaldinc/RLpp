#!/bin/bash
mkdir build > /dev/null 2>&1

g++ src/rlcd-test.cpp \
../build/rlinterface/environment.o \
../build/rlinterface/state.o \
../build/rlinterface/response.o \
../build/environment/simplegridworld/gridstate.o \
../build/environment/simplegridworld/gridworld.o \
../build/environment/ballcatching/ballcatchingworld.o \
../build/environment/ballcatching/toroidalstate.o \
../build/agent/rl-cd/state.o \
../build/agent/rl-cd/action.o \
../build/agent/rl-cd/model.o \
../build/agent/rl-cd/rlcdagent.o \
-o build/rlcd-test
echo 'Compiled!'
