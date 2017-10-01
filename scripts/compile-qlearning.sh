#!/bin/bash

mkdir ../build/ > /dev/null 2>&1
mkdir ../build/agent > /dev/null 2>&1
mkdir ../build/agent/qlearning > /dev/null 2>&1

g++ -c ../src/agent/qlearning/state.cpp -o ../build/agent/qlearning/state.o
g++ -c ../src/agent/qlearning/action.cpp -o ../build/agent/qlearning/action.o
g++ -c ../src/agent/qlearning/qlearningagent.cpp -o ../build/agent/qlearning/qlearningagent.o

echo 'Compiled!'