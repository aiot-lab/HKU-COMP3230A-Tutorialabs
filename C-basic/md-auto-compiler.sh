#!/usr/bin/bash
# compile n to m lines in a file as a C language code and run it
# Usage: md-auto-compiler.sh <file> <start line> <end line>
# Example: md-auto-compiler.sh 05-c-string.md 1 10

# check if the file exists
if [ ! -f $1 ]; then
    echo "File $1 does not exist"
    exit 1
fi

# check if the start line is a number
if ! [[ $2 =~ ^[0-9]+$ ]]; then
    echo "Start line $2 is not a number"
    exit 1
fi

# check if the end line is a number
if ! [[ $3 =~ ^[0-9]+$ ]]; then
    echo "End line $3 is not a number"
    exit 1
fi

# check if the start line is less than the end line
if [ $2 -gt $3 ]; then
    echo "Start line $2 is greater than end line $3"
    exit 1
fi

# check if the start line is greater than 0
if [ $2 -lt 1 ]; then
    echo "Start line $2 is less than 1"
    exit 1
fi

# check if the end line is less than the total number of lines in the file
if [ $3 -gt $(wc -l $1 | cut -d ' ' -f 1) ]; then
    echo "End line $3 is greater than the total number of lines in the file"
    exit 1
fi

# create a temporary file for C code
temp_file=$(mktemp)

# copy the lines from the start line to the end line to the temporary file
sed -n "$2,$3 p" $1 > $temp_file
echo -e "\e[33mCopied lines $2 to $3 from $1 to $temp_file\e[0m"

# compile the temporary file as a C language code
echo -e "\e[33mCompiled $temp_file as a C language code\e[0m"
gcc -x c $temp_file -o $temp_file.out
# if the compilation is successful, run the executable
if [ $? -eq 0 ]; then
    echo -e "\e[33mRunning $temp_file.out\e[0m"
    echo -e "\e[32m--------output:start-----------\e[0m"
    $temp_file.out
    echo -e "\e[32m--------output:end-------------\e[0m"
# else
else
    echo -e "\e[31mCompilation failed\e[0m"
fi

# remove the temporary file
rm $temp_file

# remove the executable file
rm $temp_file.out
echo "temp_file and temp_file.out removed"

# exit the script
exit 0
