#!/bin/bash

mkdir ../build/ > /dev/null 2>&1
mkdir ../build/agent > /dev/null 2>&1
mkdir ../build/agent/rl-cd > /dev/null 2>&1

g++ -c ../src/agent/rl-cd/rlcdagent.cpp -o ../build/agent/rl-cd/rlcdagent.o
g++ -c ../src/agent/rl-cd/model.cpp -o ../build/agent/rl-cd/model.o
g++ -c ../src/agent/rl-cd/state.cpp -o ../build/agent/rl-cd/state.o
g++ -c ../src/agent/rl-cd/action.cpp -o ../build/agent/rl-cd/action.o

echo 'Compiled!'