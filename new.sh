#!/bin/bash
# Usage: ./new.sh 12   -> creates solutions/012.cpp from template.cpp
set -e
cd "$(dirname "$0")"
[ -z "$1" ] && { echo "usage: ./new.sh <problem number>"; exit 1; }
n=$((10#$1))
id=$(printf "%03d" "$n")
file="solutions/$id.cpp"
[ -e "$file" ] && { echo "$file already exists"; exit 1; }
sed "s/NNN/$n/g" template.cpp > "$file"
echo "created $file"
