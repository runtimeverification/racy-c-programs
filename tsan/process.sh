#!/bin/bash

filename=$1

echo "Testing $filename"

clang++ -fsanitize=thread -O1 -std=c++11 "$filename" 2>/dev/null

errors=0

echo "Testing RV"

for i in  $(seq 0 3); do
    result="$(rv-predict-llvm ./a.out 2>&1)"


    if ! [[ $result =~ No\ races\ found\.$ ]]; then
        let "errors += 1"
    fi
done

echo "Done RV"

/usr/etc/clang/bin/clang++ -fsanitize=thread -O1 -std=c++11 "$filename" 2>/dev/null

tsan_errors=0

echo "Testing TSAN"

for i in  $(seq 0 3); do
    result="$(./a.out 2>&1)"
    if [[ $result =~ reported ]]; then
        let "tsan_errors += 1"
    fi
done

echo "Done TSAN"


if [[ $tsan_errors -ne 0 ]]; then
    mv "$filename" Races
    echo "TSan found races"
    cd Races || exit
else
    mv "$filename" NoRaces
    echo "TSan did not find races"
    cd NoRaces || exit
fi

if [[ $errors -eq $tsan_errors ]]; then
    mv "$filename" Success
    echo "$filename sucess"
else
    mv "$filename" Fail
    echo "$filename fail"
fi
