#!/bin/bash

filename=$1

echo "Testing $filename"

clang++ -fsanitize=thread -std=c++11 "$filename" 2>/dev/null

good=0

for i in `seq 0 10`; do
    result="$(rv-predict-llvm ./a.out 2>&1)"


    if ! [[ $result =~ No\ races\ found\.$ ]]; then
        let "good += 1"
    fi
done


if [[ $good -ne 0 ]]; then
    echo "$filename sucess"
    mv $filename Success
else
    echo "$filename fail"
    mv $filename Fail
fi
