#!/bin/bash

for f in $(find -iname "*.bmp" -type f); do
    rm "$f"
    echo "rm $f"
done
