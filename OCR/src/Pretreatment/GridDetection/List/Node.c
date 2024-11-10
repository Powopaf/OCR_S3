#include "Node.h"

// Node is how we named our implementation of linked list

Node* NewNode(Shape* data)
{
    /*
    Function to create a new node with given Shape data
    */
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

    if (node->next == node)  // Check for self-referencing node
    {
        err(1, "ERROR: Self-referencing node\n");
    }
    
    if (*lst == NULL)
    {
        *lst = node;
        return;
    }

    Node* n = *lst;
    while (n->next != NULL) // search the last node
    {
        n = n->next;
    }

    if (n == node)  // Prevent circular references
    {
        err(1, "ERROR: Circular reference when adding node\n");
        return;
    }

    n->next = node; // Link the last node to the new node
}

void RemoveNode(Node** lst, int index)
{
    if (*lst == NULL) {
        err(1, "ERROR: List is empty\n");
    }

    if (index < 0) {
        err(1, "ERROR: Index cannot be negative\n"); // Handle invalid index
    }

    Node* current = *lst;

    // Special case: removing the head node
    if (index == 0) {
        *lst = current->next; // Update head to the next node
        FreeNode(current, 1); // Free the removed node
        return;
    }

    // go to the node and stop at index - 1
    for (int i = 0; i < index - 1; i++) {
        if (current == NULL || current->next == NULL) {
            err(1, "ERROR: Index out of range\n");
        }
        current = current->next;
    }

    Node* nodeToRemove = current->next; // Identify the node to remove
    if (nodeToRemove == NULL) {
        err(1, "ERROR: Index out of range\n");
    }

    // Unlink the node and free it
    current->next = nodeToRemove->next;
    FreeNode(nodeToRemove, 1);
}

int LenNode(Node** lst)
{
    /*
    Function to count the number of nodes in the list
    */
    if (lst == NULL || *lst == NULL)
    {
        return 0;
    }

    int i = 1;
    Node* n = *lst;
    // visit all node
    while (n->next != NULL)
    {
        i++;
        n = n->next;
    }
    return i;
}

Node* GetNode(Node** lst, int i)
{
    /*
    Function to get the node at a specified index
    return the node at the specific index
    */
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
    /*
    Function to free a single node
    */
    if (node == NULL)
    {
        return; // Do nothing if node is NULL
    }

    if (node->data != NULL && freeData == 1) // Free data if specified
    {
        free(node->data);
        node->data = NULL;
    }
    free(node); // Free the node itself
    node = NULL;
}

void FreeNodeList(Node** lst, int freeData)
{
    /*
    Function to free the entire list
    */
    Node* c = *lst;
    Node* n;

    while (c != NULL) // Traverse through the list
    {
        n = c->next;
        FreeNode(c, freeData); // Free each node
        c = n;
    }
    *lst = NULL; // Set list head to NULL
}

int ContainsNode(Node* lst, Shape* s)
{
    /*
    Function to check if a Shape with the same ID exists in the list
    */
    Node* c = lst;
    while (c != NULL)
    {
        if (c->next != NULL && c->data->id == c->next->data->id) // Detect circular reference
        {
            err(1, "ERROR: Circular reference detected\n");
        }
        if (c->data->id == s->id) // Check for matching ID
        {
            return 1; // Return 1 if the shape is found
        }
        c = c->next;
    }
    return 0; // Return 0 if the shape is not found
}

