#include "placeInGrid.h"
#include <err.h>

int len(Shape** lst) {
	// TODO -> return the length of lst
	return 0;
}

void swap(Shape* p1, Shape* p2) {
	/*
	 * list -> linked list
	 * we swap p1 and p2 !! p1 > p2
	 * p1, p2 index of the values to switch
	 */
	struct Shape t = *p1;
	*p1 = *p2;
	*p2 = t;
}

Shape** sort_cluster(struct Shape** lst, int len) {
	/*
	 * Sort the liked list lst using a ShellSort
	 */
	for (int gap = len / 2; gap > 0; gap = gap / 2) {
		for (int i = gap; i < len; i++) {
			Shape* t = lst[i];
			int j;
			for (j = i; j >= gap && lst[j - gap]->Cx > t->Cx; j = j - gap) {
				lst[j] = lst[j - gap];
			}
		}
	}
	return lst;
}

void place(Shape**** list, int size, int* clusters_size) {
    /*
	 * Sort the list inside the cluster list
	 * list -> array of all the cluster 
	 * size -> length of list
	 */
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < clusters_size[i]; j++) {
			if (list[i][j] == NULL) {
				err(EXIT_FAILURE, "cluster %i line %iis NULL in place()", i, j);
			}
			sort_cluster(list[i][j], len(list[i][j]));
		}
	}
}
