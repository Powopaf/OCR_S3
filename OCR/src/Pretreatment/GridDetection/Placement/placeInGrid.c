#include "placeInGrid.h"
#include <err.h>

void swap(struct Shape* p1, struct Shape* p2) {
	/*
	 * list -> linked list
	 * we swap p1 and p2 !! p1 > p2
	 * p1, p2 index of the values to switch
	 */
	struct Shape t = *p1;
	*p1 = *p2;
	*p2 = t;
}

void sort_cluster(struct Node* lst) {
	for (struct Node* i = lst; i != NULL; i = i->next) {
		for (struct Node* j = i->next; j != NULL; j = j->next) {
			if (j->data->Cx < i->data->Cx) {
				swap(j->data, i->data);
			}
		}
	}
}



void place(Node*** list, int size, int* clusters_size) {
    /*
	 * Sort the list inside the cluster list
	 * list -> array of all the cluster 
	 * size -> length of list
	 */
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < clusters_size[i]; j++) {
			if (list[i][j] != NULL) {
				sort_cluster(list[i][j]);
			}
		}
	}
}
