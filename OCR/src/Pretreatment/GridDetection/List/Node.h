#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <err.h>
#include <stdlib.h>
#include "../Shape/shape.h"

typedef struct Node
{
    Shape* data;
    struct Node* next;
} Node;

Node* NewNode(Shape* data);
void AddNode(Node** lst, Node* node);
void RemoveNode(Node** lst, int i);
int LenNode(Node** lst);
Node* GetNode(Node** lst, int i);
void FreeNode(Node* node, int freeData);
void FreeNodeList(Node** lst, int freeData);
int ContainsNode(Node* lst, Shape* s);
#endif //NODE_H
