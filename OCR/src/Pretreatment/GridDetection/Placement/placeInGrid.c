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

void find_grid(Node*** list, int size, int* clusters_size) {
	for (int i = 0; i < size; i++) {
		if (list[i] != NULL) {
			int b = 0;
			int j = 0;
			while (j < clusters_size[i]) {
				if (list[i][j] != NULL) {
					int a = LenNode(&list[i][j]);
					b = j == 0 ? a : b;
					if (b != a) {
						break;
					}
					j++;
				}
			}
			if (j >= clusters_size[i]) {
				Node** t = list[0];
				list[0] = list[i];
				list[i] = t;
				int tt = clusters_size[0];
				clusters_size[0] = clusters_size[i];
				clusters_size[i] = tt;
				break;
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
		if (list[i] != NULL) {
			for (int j = 0; j < clusters_size[i]; j++) {
				if (list[i][j] != NULL) {
					sort_cluster(list[i][j]);
				}
			}
		}
	}
	find_grid(list, size, clusters_size);
}

// DO NOT DELETE THE TEST !!!!
/*int main() {
	Node*** list = malloc(sizeof(Node***) * 3);
	
	list[0] = malloc(sizeof(Node**) * 3);
	list[1] = NULL;
	list[2] = malloc(sizeof(Node**) * 3);
	
	
	Shape* p = malloc(sizeof(Shape*));
	p->Cx = 7;
	list[0][0] = NewNode(p);
	Shape* pp = malloc(sizeof(Shape*));
	pp->Cx = 5;
	AddNode(&list[0][0], NewNode(pp));
	Shape* ppp = malloc(sizeof(Shape*));
	ppp->Cx = 1;
	AddNode(&list[0][0], NewNode(ppp));
	Shape* pppp = malloc(sizeof(Shape*));
	pppp->Cx = 9;
	AddNode(&list[0][0], NewNode(pppp));

	Shape* a = malloc(sizeof(Shape*));
	a->Cx = 7;
	list[0][1] = NewNode(a);
	Shape* aa = malloc(sizeof(Shape*));
	aa->Cx = 5;
	AddNode(&list[0][1], NewNode(aa));
	Shape* aaa = malloc(sizeof(Shape*));
	aaa->Cx = 1;
	AddNode(&list[0][1], NewNode(aaa));

	Shape* z = malloc(sizeof(Shape*));
	z->Cx = 7;
	list[0][2] = NewNode(z);
	Shape* zz = malloc(sizeof(Shape*));
	zz->Cx = 5;
	AddNode(&list[0][2], NewNode(zz));
	Shape* zzz = malloc(sizeof(Shape*));
	zzz->Cx = 1;
	AddNode(&list[0][2], NewNode(zzz));

	Shape* r = malloc(sizeof(Shape*));
	r->Cx = 7;
	list[2][0] = NewNode(r);
	Shape* rr = malloc(sizeof(Shape*));
	rr->Cx = 5;
	AddNode(&list[2][0], NewNode(rr));
	Shape* rrr = malloc(sizeof(Shape*));
	rrr->Cx = 1;
	AddNode(&list[2][0], NewNode(rrr));

	//list[2][1] = NULL;

	Shape* t = malloc(sizeof(Shape*));
	t->Cx = 7;
	list[2][1] = NewNode(t);
	Shape* tt = malloc(sizeof(Shape*));
	tt->Cx = 5;
	AddNode(&list[2][1], NewNode(tt));
	Shape* ttt = malloc(sizeof(Shape*));
	ttt->Cx = 1;
	AddNode(&list[2][1], NewNode(ttt));
	
	int s[3] = { 3, 0, 2 };
	place(list, 3, s);

	for (int i = 0; i < 3; i++) {
		if (list[i] != NULL) {
			for (int j = 0; j < 3; j++) {
				for(Node* k = list[i][j]; k != NULL; k = k->next) {
					printf("%i ", k->data->Cx);
				}
				printf("\n");
			}
			printf("\n");
		}
	}

	return EXIT_SUCCESS;
}*/
