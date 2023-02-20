#!/bin/bash
# Usage: ./script.sh substring string
substring=$1
string=$2
count=0

while [[ $string == *$substring* ]]
do
  string=${string#*$substring}
  ((count++))
done

echo "Number of occurrences = $count"