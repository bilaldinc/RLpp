#!/bin/bash

mkdir ../build/ > /dev/null 2>&1
mkdir ../build/agent > /dev/null 2>&1
mkdir ../build/agent/ql_scd > /dev/null 2>&1

g++ -c ../src/agent/ql_scd/ql_scd_state.cpp -o ../build/agent/ql_scd/ql_scd_state.o
g++ -c ../src/agent/ql_scd/ql_scd_action.cpp -o ../build/agent/ql_scd/ql_scd_action.o
g++ -c ../src/agent/ql_scd/ql_scd_agent.cpp -o ../build/agent/ql_scd/ql_scd_agent.o

echo 'Compiled!'
