#include "placeInGrid.h"
#include <err.h>

void swap(struct Node* p1, struct Node* p2) {
	/*
	 * list -> linked list
	 * we swap p1 and p2 !! p1 > p2
	 * p1, p2 index of the values to switch
	 */
	struct Shape* t = p1->data;
	p1->data = p2->data;
	p2->data = t;
}

void sort_cluster(struct Node* lst) {
	for (struct Node* i = lst; i != NULL; i = i->next) {
		for (struct Node* j = i->next; j != NULL; j = j->next) {
			if (j->data->Cx < i->data->Cx) {
				swap(j, i);
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

void find_grid(Node*** list, int size, int* clusters_size) {
	for (int i = 0; i < size; i++) {
		int k = 0;
		for (int j = 0; j < clusters_size[i]; j++) {
			int l = 0;
			for(struct Node* p = list[i][j]; p != NULL; p = p->next) {
				l++;
			}
			k = j == 0 ? l : k;
			if (k != l) {
				break;
			}
		}
	}
}
