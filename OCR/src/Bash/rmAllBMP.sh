#!/bin/bash

if [[ $# -lt 1 ]]; then
    echo "Usage: $0 <levels>"
    exit 1
fi

target_dir="src" #the search directory in project
max_levels="$1" #the maximu level above the current position in project
start_dir=$(pwd) #the current directory

# Loop to find the target directory
for ((i = 0; i < max_levels; i++)); do
    if [[ -d "$start_dir/$target_dir" ]]; then
        echo "Found target directory: $target_dir"
        for f in $(find "$start_dir/$target_dir" -type f -name "*.bmp"); do
            rm "$f"
            echo "Delete: $f"
        done
        echo "Deleted all *.bmp file in OCR"
        exit 0
    fi
    # Move one level up
    start_dir=$(dirname "$start_dir")
done

echo "Target_dir '$target_dir' not found within $max_levels levels.
parameter when rmAllBMP can be wrong or '$target_dir' is not in project"
exit 1
