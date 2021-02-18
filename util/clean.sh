#!/usr/bin/env bash

rm -rf build/
cd aspera
make clean
cd ../lib/a
make clean
cd ../../util/mkirfs
make clean
