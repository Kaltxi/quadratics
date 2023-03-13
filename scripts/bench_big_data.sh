#!/usr/bin/env bash
./build/quadratics_gen 1000 > data.txt
./build/quadratics_bench $(cat data.txt)
rm data.txt