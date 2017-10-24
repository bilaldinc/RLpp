#!/bin/bash
mkdir ../build/ > /dev/null 2>&1
mkdir ../build/environment  > /dev/null 2>&1
mkdir ../build/environment/ballcatching  > /dev/null 2>&1

g++ -c ../src/environment/ballcatching/toroidalstate.cpp -o ../build/environment/ballcatching/toroidalstate.o
g++ -c ../src/environment/ballcatching/ballcatchingworld.cpp -o ../build/environment/ballcatching/ballcatchingworld.o
echo 'Compiled!'