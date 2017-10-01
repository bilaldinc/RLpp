#!/bin/bash
g++ -c ../src/environment/simplegridworld/gridstate.cpp -o ../build/environment/simplegridworld/gridstate.o
g++ -c ../src/environment/simplegridworld/gridworld.cpp -o ../build/environment/simplegridworld/gridworld.o
echo 'Compiled!'