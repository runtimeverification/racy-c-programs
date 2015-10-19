#!/bin/bash

for f in *; do
    filename=$(basename "$f")
    extension="${filename##*.}"
    if [[ "$extension" = "cc" ]] || [[ "$extension" = "c"  ]] ; then
        ./process.sh "$filename"
    fi
done
