#!/bin/bash
echo -n "Enter a number: "
read num

result=1

for (( i=1; i<=num; i++ ))
do
    result=$(( result * i ))
done

echo "Factorial of $num is: $result"
