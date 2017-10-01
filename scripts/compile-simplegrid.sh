#!/bin/bash
mkdir ../build/ > /dev/null 2>&1
mkdir ../build/environment  > /dev/null 2>&1
mkdir ../build/environment/simplegridworld  > /dev/null 2>&1

g++ -c ../src/environment/simplegridworld/gridstate.cpp -o ../build/environment/simplegridworld/gridstate.o
g++ -c ../src/environment/simplegridworld/gridworld.cpp -o ../build/environment/simplegridworld/gridworld.o
echo 'Compiled!'