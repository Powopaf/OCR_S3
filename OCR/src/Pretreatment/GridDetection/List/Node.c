#include "Node.h" // Include the header file for the Node and Shape structures

// Function to create a new node with given Shape data
Node* NewNode(Shape* data)
{
    Node* node = (Node*)malloc(sizeof(Node)); // Allocate memory for the new node
    if (node == NULL)
    {
        err(1, "ERROR: Memory allocation for node failed\n"); // Handle allocation failure
    }
    node->data = data; // Assign Shape data to the node
    node->next = NULL; // Set next pointer to NULL
    return node; // Return the created node
}

// Function to add a node to the end of the list
void AddNode(Node** lst, Node* node)
{
    if (lst == NULL || node == NULL)
    {
        err(1, "ERROR: Invalid list or node\n"); // Handle invalid arguments
    }

    if (node->next == node)  // Check for self-referencing node
    {
        err(1, "ERROR: Self-referencing node\n");
    }
    
    if (*lst == NULL) // If the list is empty, set node as the head
    {
        *lst = node;
        return;
    }

    Node* n = *lst;
    while (n->next != NULL) // Traverse to the last node
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

// Function to remove a node at a specific index from the list
void RemoveNode(Node** lst, int index)
{
    if (*lst == NULL) {
        err(1, "ERROR: List is empty\n"); // Handle empty list
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

    // Traverse to the node just before the target index
    for (int i = 0; i < index - 1; i++) {
        if (current == NULL || current->next == NULL) {
            err(1, "ERROR: Index out of range\n");
        }
        current = current->next;
    }

    Node* nodeToRemove = current->next; // Identify the node to remove
    if (nodeToRemove == NULL) {
        err(1, "ERROR: Index out of range\n"); // Handle out-of-range index
    }

    // Unlink the node and free it
    current->next = nodeToRemove->next;
    FreeNode(nodeToRemove, 1); // Free the memory of the removed node
}

// Function to count the number of nodes in the list
int LenNode(Node** lst)
{
    if (lst == NULL || *lst == NULL)
    {
        return 0; // Return 0 for an empty list
    }

    int i = 1;
    Node* n = *lst;
    while (n->next != NULL) // Traverse through the list
    {
        i++;
        n = n->next;
    }
    return i; // Return the count
}

// Function to get the node at a specified index
Node* GetNode(Node** lst, int i)
{
    if (lst == NULL || *lst == NULL)
    {
        err(1, "ERROR: List is empty\n"); // Handle empty list
    }

    Node* n = *lst;
    while (i > 0)
    {
        if (n->next == NULL)
        {
            err(1, "ERROR: Index out of range\n"); // Handle out-of-range index
        }
        n = n->next;
        i--;
    }
    return n; // Return the node at the specified index
}

// Function to free a single node
void FreeNode(Node* node, int freeData)
{
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

// Function to free the entire list
void FreeNodeList(Node** lst, int freeData)
{
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

// Function to check if a Shape with the same ID exists in the list
int ContainsNode(Node* lst, Shape* s)
{
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

