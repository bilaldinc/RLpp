#!/bin/bash

mkdir ../build/ > /dev/null 2>&1
mkdir ../build/agent > /dev/null 2>&1
mkdir ../build/agent/qlearning-scd > /dev/null 2>&1

g++ -c ../src/agent/qlearning-scd/state.cpp -o ../build/agent/qlearning-scd/state.o
g++ -c ../src/agent/qlearning-scd/action.cpp -o ../build/agent/qlearning-scd/action.o
g++ -c ../src/agent/qlearning-scd/qlearningagent.cpp -o ../build/agent/qlearning-scd/qlearningagent.o

echo 'Compiled!'