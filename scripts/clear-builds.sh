#!/bin/bash

find ../build/ -type f -exec rm {} \;
find ../test/build/ -type f -exec rm {} \;

echo 'Done!'