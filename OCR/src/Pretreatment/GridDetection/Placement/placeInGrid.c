#include "placeInGrid.h"
#include <err.h>

void swap(int* p1, int* p2) {
	/*
	 * list -> linked list
	 * we swap p1 and p2 !! p1 > p2
	 * p1, p2 index of the values to switch
	 */
	int t = *p1;
	*p1 = *p2;
	*p2 = t;
}

Node*** place(const Node*** list, int size) {
    /*
	 * Sort the list inside the cluster list
	 * list -> array of all the cluster 
	 * size -> length of list
	 */
}
