#!/bin/sh

set -xe

# CFLAGS="-std=c++17 -O2 -Wall -Wextra -Wconversion -DLOCAL"

g++ -Wall -Wextra -Wshadow -Ofast -std=c++17 -pedantic -Wformat=2 -Wconversion -DLOCAL -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wfloat-equal -fstack-protector -fmax-errors=2 -o main main.cpp
