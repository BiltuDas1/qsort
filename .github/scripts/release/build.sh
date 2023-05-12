#!/bin/bash

# ENVIRONMENT
VER=$1

cmake -B build .
cd build/
make deb
cd ..
mv "qsort-debian.deb" "qsort_v"$VER"_1_amd64.deb"