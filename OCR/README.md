#CLAPS Word Search OCR - EPITA student project

##Overview :
This application is designed to detect and solve word search puzzles from an image containing a grid and a list of words to search in this grid.
The program uses image processing techniques to identify and isolate each letter, along with a neural network for analysis and a word search algorithm.
An interactive user interface is provided that displays the answer.

##Requirements :
Before running the application, ensure the following tools are installed:
- `gcc`: to compile C code
- `GTK3`: for the graphical interface
- `ImageMagick`: for image manipulation
- `SDL`: for image processing
- `SDL_image`: for image processing

##Run :
To run the project, run `make` in a terminal inside the root project directory.
After compiling it, open the interface with `./main.out`.
Once in the interface :
- Use the import button to load an image inside the interface
- Use the rotation slider to manually rotate the selected image
- Use the PROCESS button to process the selected image and show the solution
- Use the process steps to show the desired processing step
- Use the EXPORT button to export the actual shown image with the desired type

