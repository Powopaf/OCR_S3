#include "../Shape/shape.h" // Include the header file for shape-related functions and data structures
#include "../Lib/Lib.h" // Include additional utility functions
#include <stdlib.h> // Include standard library for memory allocation
#include <SDL2/SDL.h> // Include SDL2 for handling surfaces

// Function to create and initialize a new Shape structure
Shape* CreateShape(int id, int j, int i) {
    Shape* s = (Shape*)malloc(sizeof(Shape));
    if (s == NULL) {
        err(1, "ERROR Memory Allocation"); // Error handling if memory allocation fails
    }
    s->id = id; // Assign shape ID

    s->Cx = j; // Set initial center x-coordinate
    s->Cy = i; // Set initial center y-coordinate

    s->h = 0; // Initialize height to 0
    s->w = 0; // Initialize width to 0

    // Initialize bounding box coordinates
    s->Maxj = j;
    s->Maxi = i;
    s->Minj = j;
    s->Mini = i;
    
    s->Matj = 0; // Initialize matrix coordinates
    s->Mati = 0;

    s->Len = 0; // Initialize length of shape to 0
    return s; // Return pointer to the created shape
}

// Function to compute dimensions and center coordinates of a shape
void ComputeShape(Shape* s)
{
    s->h = s->Maxj - s->Minj + 1; // Calculate height
    s->w = s->Maxi - s->Mini + 1; // Calculate width
    s->Cx = s->Minj + (s->h)/2; // Set center x-coordinate
    s->Cy = s->Mini + (s->w)/2; // Set center y-coordinate
}

// Recursive function to find a shape on a surface
void FindShape(Shape* s, int** surface, int** Map, int j, int i, int height, int width) {
    Map[j][i] = s->id; // Mark the current position with the shape ID
    s->Len++; // Increment the length of the shape

    // Update bounding box coordinates
    if (s->Maxj < j) s->Maxj = j;
    if (s->Minj > j) s->Minj = j;
    if (s->Maxi < i) s->Maxi = i;
    if (s->Mini > i) s->Mini = i;

    // Recursive exploration in four directions to find connected pixels
    if (IsOnSurface(j+1, i, height, width) && Map[j+1][i] == 0 && surface[j+1][i] == 255)
        FindShape(s, surface, Map, j+1, i, height, width);
    
    if (IsOnSurface(j-1, i, height, width) && Map[j-1][i] == 0 && surface[j-1][i] == 255)
        FindShape(s, surface, Map, j-1, i, height, width);

    if (IsOnSurface(j, i+1, height, width) && Map[j][i+1] == 0 && surface[j][i+1] == 255)
        FindShape(s, surface, Map, j, i+1, height, width);
    
    if (IsOnSurface(j, i-1, height, width) && Map[j][i-1] == 0 && surface[j][i-1] == 255)
        FindShape(s, surface, Map, j, i-1, height, width);
}

// Function to check if a shape is valid by comparing its dimensions to the surface
int IsShapeValid(SDL_Surface* surface, Shape* s) {
    return (s->w < surface->w / 8 && s->h < surface->h / 8); // Returns true if the shape is smaller than a threshold
}

// Function to calculate the minimum distance between two shapes
double FindLowestDist(Shape* s1, Shape* s2)
{
    // Define the four corners of each shape's bounding box
    int p1[4][2] = {
        {s1->Minj, s1->Mini},
        {s1->Minj, s1->Maxi},
        {s1->Maxj, s1->Mini},
        {s1->Maxj, s1->Maxi}
    };

    int p2[4][2] = {
        {s2->Minj, s2->Mini},
        {s2->Minj, s2->Maxi},
        {s2->Maxj, s2->Mini},
        {s2->Maxj, s2->Maxi}
    };

    // Initialize the minimum distance as the distance between the first pair of corners
    double MinDist = distance(p1[0][0], p1[0][1], p2[0][0], p2[0][1]);

    // Loop through each pair of corners to find the minimum distance
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            double dist = distance(p1[i][0], p1[i][1], p2[j][0], p2[j][1]);
            if (dist < MinDist) {
                MinDist = dist; // Update minimum distance if a smaller one is found
            }
        }
    }

    return MinDist; // Return the minimum distance found
}

