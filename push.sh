#!/bin/bash

if [ -z "$1" ]; then
    echo "Error: Please provide a commit message as an argument."
    exit 1
fi

make fclean > /dev/null 2>&1 || { echo "Error: 'make fclean' failed."; exit 1; }
git add -A > /dev/null 2>&1
git commit -m "$1" > /dev/null 2>&1 || { echo "Error: 'git commit' failed. Maybe there are no changes to commit?"; exit 1; }
git push > /dev/null 2>&1 || { echo "Error: 'git push' failed."; exit 1; }
make > /dev/null 2>&1 || { echo "Error: 'make' failed."; exit 1; }

echo "Push successful"