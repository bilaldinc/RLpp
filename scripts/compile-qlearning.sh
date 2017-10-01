#!/bin/bash
g++ -c ../src/agent/qlearning/state.cpp -o ../build/agent/qlearning/state.o
g++ -c ../src/agent/qlearning/action.cpp -o ../build/agent/qlearning/action.o
g++ -c ../src/agent/qlearning/qlearningagent.cpp -o ../build/agent/qlearning/qlearningagent.o

echo 'Compiled!'