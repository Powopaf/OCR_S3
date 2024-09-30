#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <err.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node* next;
} Node;

Node* NewNode(int data);
void AddNode(Node* lst, Node* node);
Node* RemoveNode(Node* lst, int i);
int LenNode(Node* lst);
Node* GetNode(Node* lst, int i);

#endif //NODE_H
