#!/bin/bash

for dir in */; do
    rm *.bmp
    if [ -L "${d%/}" ]
    then
        cd dir
    fi
done
