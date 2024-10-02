#!/bin/bash

# Loop through all .bmp file to delete them

for f in $(find -type f -name "*bmp"); do
    rm "$f"
    echo "Deleted $f"
done
echo "no .bmp in project (all remove)"
