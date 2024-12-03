#include "placeInGrid.h"
#include <err.h>

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

void place(Node*** list, int size, int* clusters_size) {
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
			struct Node* p = list[i][j]->next == NULL ? NULL : list[i][j];
			struct Node* c;
			if (p != NULL) {
				c = p->next;
			}
			while (c != NULL) {
				if (c->data->Cx < p->data->Cx) {
					swap(c->data, p->data); // need a upgrade
				}
				c = c->next;
				p = p->next;
			}
		}
	}
}
