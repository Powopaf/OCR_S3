#include "placeInGrid.h"

Shape** generateMatrix(const Node* ShapeList, size_t* sizeX, size_t* sizeY) 
{
    /*
    *   return a matrix of Shape of dimension sizeX and sizeY 
    *   the two pointer are modified in the function
    *   ShapeList is a cluster thar represent the grid
    */
    if (ShapeList == NULL) { err(EXIT_FAILURE, "Shapelist point to NULL\n"); }
   
    Shape** res = malloc(sizeof(struct Shape*) * LenNode(&ShapeList));
    
    while (ShapeList != NULL)
    {
        ShapeList = ShapeList->next;
    }
    return NULL;
}