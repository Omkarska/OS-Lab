#!/bin/bash

# Declare an empty array
arr=()

# Prompt the user for input
echo "Enter numbers separated by space:"

# Read the input into an array
read -a arr

# Get the length of the array
len=${#arr[@]}

# Loop through the array
for ((i = 0; i < len; i++)); do

    # Loop through the remaining elements
    for ((j = i + 1; j < len; j++)); do

        # Compare and swap if needed
        if [ ${arr[i]} -gt ${arr[j]} ]; then
            temp=${arr[i]}
            arr[i]=${arr[j]}
            arr[j]=$temp
        fi
    done
done

# Print the sorted array
echo "Array in sorted order:"
echo ${arr[@]}