#!/bin/bash
# Usage: ./run.sh 12   -> compiles and runs solutions/012.cpp, printing the time taken
set -e
cd "$(dirname "$0")"
[ -z "$1" ] && { echo "usage: ./run.sh <problem number>"; exit 1; }
id=$(printf "%03d" "$((10#$1))")
mkdir -p build
clang++ -std=c++20 -O2 -Wall -Wextra -Iinclude "solutions/$id.cpp" -o "build/$id"
start=$(date +%s%N 2>/dev/null || python3 -c 'import time;print(time.time_ns())')
"./build/$id"
end=$(date +%s%N 2>/dev/null || python3 -c 'import time;print(time.time_ns())')
echo "($(( (end - start) / 1000000 )) ms)" >&2
