#!/bin/bash
mkdir ../build/ > /dev/null 2>&1
mkdir ../build/rlinterface  > /dev/null 2>&1

g++ -c ../src/rlinterface/state.cpp -o ../build/rlinterface/state.o
g++ -c ../src/rlinterface/response.cpp -o ../build/rlinterface/response.o
g++ -c ../src/rlinterface/environment.cpp -o ../build/rlinterface/environment.o

echo 'Compiled!'