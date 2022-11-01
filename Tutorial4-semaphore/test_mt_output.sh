#!/bin/bash
for i in `seq 1 1000`
do
    output=$($1)
    if [ "$output" != "$2" ]; then
        echo "\033[31mTest failed: $1 returned $2, expected $output\033[0m"
        exit 1
    fi
done
# green
echo "\033[32mTest passed\033[0m"
