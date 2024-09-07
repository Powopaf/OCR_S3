#ifndef SOLVER_H
#define SOLVER_H

#include <stdio.h>
#include <stdlib.h>

// Variables globales
extern char filename[];
extern char grid[256][256];
extern int grid_len_x;
extern int grid_len_y;

// Prototypes de fonctions
int print_grid(int Start[], int End[]);
int len(char word[]);
int find_word(char word[], int End[2], int i, int j, int vx, int vy);
int find_second_letter(char word[], int End[2], int x, int y);
int solve_grid(char word[], int Start[2], int End[2]);
int read_grid(char filename[]);
int solver(char word[]);

#endif

