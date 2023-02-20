#!/bin/bash
echo -n "Enter a number: "
read num

function factorial() {
    if (( $1 == 1 )); then
        echo 1
    else
        echo $(( $1 * $(factorial $(( $1 - 1 ))) ))
    fi
}

result=$(factorial $num)
echo "Factorial of $num is: $result"
