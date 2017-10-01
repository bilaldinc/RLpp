#!/bin/bash
g++ -c ../src/rlinterface/state.cpp -o ../build/rlinterface/state.o
g++ -c ../src/rlinterface/response.cpp -o ../build/rlinterface/response.o
g++ -c ../src/rlinterface/environment.cpp -o ../build/rlinterface/environment.o

echo 'Compiled!'