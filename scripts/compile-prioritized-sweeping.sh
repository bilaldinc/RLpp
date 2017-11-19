#!/bin/bash

mkdir ../build/ > /dev/null 2>&1
mkdir ../build/agent > /dev/null 2>&1
mkdir ../build/agent/prioritized-sweeping > /dev/null 2>&1

g++ -c ../src/agent/prioritized-sweeping/prioritizedsweepingagent.cpp -o ../build/agent/prioritized-sweeping/prioritizedsweepingagent.o
g++ -c ../src/agent/prioritized-sweeping/model.cpp -o ../build/agent/prioritized-sweeping/model.o
g++ -c ../src/agent/prioritized-sweeping/state.cpp -o ../build/agent/prioritized-sweeping/state.o
g++ -c ../src/agent/prioritized-sweeping/action.cpp -o ../build/agent/prioritized-sweeping/action.o

echo 'Compiled!'