#!/bin/bash
# Usage: ./run.sh <num-of-test-demo>
# E.g. ./run.sh 1

NUM=$(printf "%02d" ${1})
gsed -i "s/\(TESTS = demo\)\([0-9]*\)/\1${NUM}/" Makefile
make clean all
