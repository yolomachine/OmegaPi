#!/usr/bin/env bash

rm 31415926.pi
cat bbp.cpp
printf "\n\n"
g++ -o OmegaPi.out bbp.cpp
./OmegaPi.out
printf "\n\n"
cat 31415926.pi
printf "\n\n"