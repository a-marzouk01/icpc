#!/bin/sh

set -xe

CFLAGS="-std=c++17 -O2 -Wall -Wextra -Wconversion -DLOCAL"

g++ $CFLAGS -o main main.cpp
