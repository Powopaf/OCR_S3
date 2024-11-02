#!/bin/bash

LETTER_DIR="output/letter"

find "$LETTER_DIR" -type f -name "*.bmp" -exec rm {} \;

find "$LETTER_DIR" -type d -mindepth 1 -exec rmdir {} \; 2>/dev/null

