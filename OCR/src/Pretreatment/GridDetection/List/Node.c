#include "Node.h"

Node* NewNode(Shape* data)
{
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL)
    {
        err(1, "ERROR: Memory allocation for node failed\n");
    }
    node->data = data;
    node->next = NULL;
    return node;
}

void AddNode(Node** lst, Node* node)
{
    if (lst == NULL || node == NULL)
    {
        err(1, "ERROR: Invalid list or node\n");
    }

    if (node->next == node)  // Vérifie si le nœud pointe vers lui-même
    {
        err(1, "ERROR: Self-referencing node\n");
    }
    
    if (*lst == NULL)
    {
        *lst = node;
        return;
    }

    Node* n = *lst;
    while (n->next != NULL)
    {
        n = n->next;
    }

    if (n == node)  // Vérifie que nous n'ajoutons pas une boucle
    {
        err(1, "ERROR: Circular reference when adding node\n");
        return;
    }

    n->next = node;
}


void RemoveNode(Node** lst, int index)
{
    if (*lst == NULL) {
        err(1, "ERROR: List is empty\n");
    }

    if (index < 0) {
        err(1, "ERROR: Index cannot be negative\n");
    }

    Node* current = *lst;

    // Cas où le premier nœud doit être supprimé
    if (index == 0) {
        *lst = current->next; // Le premier élément pointe vers le suivant
        FreeNode(current,1);     // Libère le nœud supprimé
        return;
    }

    // Parcourir la liste jusqu'à l'index-1
    for (int i = 0; i < index - 1; i++) {
        if (current == NULL || current->next == NULL) {
            err(1, "ERROR: Index out of range\n");
        }
        current = current->next;
    }

    Node* nodeToRemove = current->next;
    if (nodeToRemove == NULL) {
        err(1, "ERROR: Index out of range\n");
    }

    // Supprimer le nœud et relier les éléments de la liste
    current->next = nodeToRemove->next;
    FreeNode(nodeToRemove,1);  // Libérer la mémoire du nœud supprimé
}


int LenNode(Node** lst)
{
    if (lst == NULL || *lst == NULL)
    {
        return 0;
    }

    int i = 1;
    Node* n = *lst;
    while (n->next != NULL)
    {
        i++;
        n = n->next;
    }
    return i;
}

Node* GetNode(Node** lst, int i)
{
    if (lst == NULL || *lst == NULL)
    {
        err(1, "ERROR: List is empty\n");
    }

    Node* n = *lst;
    while (i > 0)
    {
        if (n->next == NULL)
        {
            err(1, "ERROR: Index out of range\n");
        }
        n = n->next;
        i--;
    }
    return n;
}

void FreeNode(Node* node, int freeData)
{
    if (node == NULL)
    {
        return;
    }

    if (node->data != NULL && freeData==1)
    {
        free(node->data);
        node->data = NULL;
    }
    free(node);
    node = NULL;
    
}

void FreeNodeList(Node** lst, int freeData)
{
    Node* c = *lst;
    Node* n;

    while(c!=NULL)
    {
        n = c->next;
        FreeNode(c,freeData);
        c = n;
    }
    c = NULL;

    *lst = NULL;
}

int ContainsNode(Node* lst, Shape* s)
{
    Node* c = lst;
    while(c!=NULL)
    {
        if(c->next!=NULL && c->data->id == c->next->data->id)
        {
            err(1, "ERROR: Circular reference detected\n");
        }
        //printf("Test Contains shape %i\n",c->data->id);
        if(c->data->id == s->id)
        {
            return 1;
        }
        c = c->next;
    }
    return 0;
}
