#!/bin/bash

mkdir ../build/ > /dev/null 2>&1
mkdir ../build/agent > /dev/null 2>&1
mkdir ../build/agent/rl-cd-s > /dev/null 2>&1

g++ -c ../src/agent/rl-cd-s/rlcdsagent.cpp -o ../build/agent/rl-cd-s/rlcdsagent.o
g++ -c ../src/agent/rl-cd-s/model.cpp -o ../build/agent/rl-cd-s/model.o
g++ -c ../src/agent/rl-cd-s/state.cpp -o ../build/agent/rl-cd-s/state.o
g++ -c ../src/agent/rl-cd-s/action.cpp -o ../build/agent/rl-cd-s/action.o

echo 'Compiled!'
