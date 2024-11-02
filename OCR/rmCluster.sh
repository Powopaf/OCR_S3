#!/bin/bash

# Chemin du dossier Letter
LETTER_DIR="output/letter"

# Supprimer tous les fichiers .bmp dans les sous-dossiers de Letter
find "$LETTER_DIR" -type f -name "*.bmp" -exec rm {} \;

# Supprimer tous les sous-dossiers vides dans Letter (sans supprimer Letter lui-même)
find "$LETTER_DIR" -type d -mindepth 1 -exec rmdir {} \; 2>/dev/null

echo "Tous les fichiers .bmp et sous-dossiers dans $LETTER_DIR ont été supprimés, sauf le dossier Letter."

