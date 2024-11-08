# CLAPS Word Search OCR - EPITA student project

## Overview :
This application is designed to detect and solve word search puzzles from an image of a grid.
The program uses image processing techniques to identify and isolate each letter, along with a neural network for analysis and a word search algorithm.
An interactive user interface is provided.

## Requirements :
Before running the application, ensure the following tools are installed:
- `gcc`: to compile C code
- `GTK3`: for the graphical interface
- `ImageMagick`: for image manipulation
- `SDL`: for image processing

## Run :
To run the project, run `make` in a terminal inside the root project directory.
After compiling it, open the interface with `./main.out`.
Once in the interface :
- Use the import button to load an image inside the software
- Use the rotation slider to manually rotate the selected image
- Use the PROCESS button to process the selected image and show the solution
- Use the process steps to show the desired processing step
- Use the Export button to export the actual shown image with the desired type

## PROJECT RULES

### ARCHI

- \*.c = \*.h
- 80 caractères **__max__** par ligne
- eviter les fichier c de +200 lignes
- mettre .out sur les exécutable
- put .png file un /photo directory

### GITHUB REGLES

- 1 feature = 1 branches
- merge via le site
- supprimer la branche une fois merge
- lors du premier push sur une branche faire une pull request

### TUTO GIT

* Créer sa branche :
    * `git branch <nom>`
    * `git checkout <nom>`
    * `git push --set-upstream origin <nom>`
* Lors du premier push :
    * créer une pull request comme ça on garde un suivi de la branche sur git
      et on peut faire des commentaires si besoin
    * se fait directement sur le site
    
        1. 
            ![](photoREADME/newpull.png "")
        
        2. mettre dans base: le main et dans compare la branche créée
            ![](photoREADME/select.png "")
        
        3. 
            ![](photoREADME/create.png "")
        
        4. 
            ![](photoREADME/createoff.png "")
* Dev :
    * `git status` (on ne sait jamais)
    * `git add <nom de fichier>` ou `git add .` pour tout d'un coup
    * `git commit -m "mon message"`
        * mettre ce que l'on a fait dans le message du commit
    * `git push`
* Fin du Dev
    * Squash and merge la branche et la delete comme montré avec les photos si
      dessous
        
        1.
            ![](photoREADME/squash.png "")

        2.
            ![](photoREADME/delete.png "")

        3. `git checkout main`
        4. `git branch -d <nom>`
