#!/bin/bash
mkdir build > /dev/null 2>&1

g++ src/rlcd-s-test.cpp \
../build/rlinterface/environment.o \
../build/rlinterface/state.o \
../build/rlinterface/response.o \
../build/environment/simplegridworld/gridstate.o \
../build/environment/simplegridworld/gridworld.o \
../build/environment/ballcatching/ballcatchingworld.o \
../build/environment/ballcatching/toroidalstate.o \
../build/agent/rl-cd-s/state.o \
../build/agent/rl-cd-s/action.o \
../build/agent/rl-cd-s/model.o \
../build/agent/rl-cd-s/rlcdsagent.o \
-o build/rlcd-s-test
echo 'Compiled!'
