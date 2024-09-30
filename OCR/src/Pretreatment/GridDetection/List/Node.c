#include "Node.h"

Node* NewNode(int data)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

void AddNode(Node* lst, Node* node)
{
    if(lst==NULL)
    {
        lst = node;
        return;
    }
    Node* n = lst;
    while(n->next!=NULL)
    {
        n = n->next;
    }

    n->next = node;
}

Node* RemoveNode(Node* lst, int i)
{
    if(i<0)
    {
        err(1,"ERROR index < 0\n");
    }
    if(i==0)
    {
        return lst->next;
    }

    Node* n = lst;

    while(i>1)
    {
        if(n->next==NULL)
        {
            err(1,"ERROR LST: Index out of range\n");
        }
        n = n->next;
        i--;
    }
    Node* node = n->next;
    n->next = (n->next)->next;
    printf("%i\n",node->data);
    free(node);
    
    return lst;
}

int LenNode(Node* lst)
{
    if(lst==NULL)
    {
        return -1;
    }

    int i = 1;
    Node* n = lst;
    while(n->next!=NULL)
    {
        i++;
        n = n->next;
    }
    return i;
}

Node* GetNode(Node* lst, int i)
{
    if(lst==NULL)
    {
        err(1,"ERROR LST EMPTY\n");
    }
    Node* n = lst;
    while(i>0)
    {
        if(n->next == NULL)
        {
            err(1,"ERROR LST: Index out of range\n");
        }
        n = n->next;
        i--;
    }
    return n;
}

int main()
{
    Node* lst = NewNode(0);

    AddNode(lst,NewNode(1));
    AddNode(lst,NewNode(2));
    AddNode(lst,NewNode(3));
    AddNode(lst,NewNode(4));
    AddNode(lst,NewNode(5));

    printf("%i\n",LenNode(lst));
    lst = RemoveNode(lst,5);
    printf("%i\n",(GetNode(lst,3))->data);
}
