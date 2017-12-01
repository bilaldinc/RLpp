#!/bin/bash

mkdir ../build/ > /dev/null 2>&1
mkdir ../build/agent > /dev/null 2>&1
mkdir ../build/agent/rl-scd > /dev/null 2>&1

g++ -c ../src/agent/rl-scd/rlcdagent.cpp -o ../build/agent/rl-scd/rlcdagent.o
g++ -c ../src/agent/rl-scd/model.cpp -o ../build/agent/rl-scd/model.o
g++ -c ../src/agent/rl-scd/state.cpp -o ../build/agent/rl-scd/state.o
g++ -c ../src/agent/rl-scd/action.cpp -o ../build/agent/rl-scd/action.o

echo 'Compiled!'
