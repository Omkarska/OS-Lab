# Read input number
echo "Enter a number:"
read n

# Initialize reverse number as 0
rev=0

# Store original number in another variable
orig=$n

# Loop until n becomes 0
while [ $n -gt 0 ]
do
    # Get last digit of n
    d=$((n % 10))

    # Multiply rev by 10 and add d
    rev=$((rev * 10 + d))

    # Divide n by 10
    n=$((n / 10))
done

# Print reverse number
echo "Reverse of $orig is $rev"

# Check if orig and rev are equal
if [ $orig -eq $rev ]
then
    echo "$orig is a palindrome"
else
    echo "$orig is not a palindrome"
fi