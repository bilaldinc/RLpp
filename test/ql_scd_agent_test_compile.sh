#!/bin/bash
mkdir build > /dev/null 2>&1

g++ src/ql_scd_agent_test.cpp \
../build/rlinterface/environment.o \
../build/rlinterface/state.o \
../build/rlinterface/response.o \
../build/environment/simplegridworld/gridstate.o \
../build/environment/simplegridworld/gridworld.o \
../build/agent/ql_scd/ql_scd_state.o \
../build/agent/ql_scd/ql_scd_action.o \
../build/agent/ql_scd/ql_scd_agent.o \
-o build/ql_scd_agent_test
echo 'Compiled!'
