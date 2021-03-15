// Inserting a key into BTree

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<malloc.h>

#define MAX 3
#define MIN 2

struct btreeNode
{
    int count;
    int item[MAX+1];
    struct btreeNode *link[MAX+1];
};
struct btreeNode *root;

struct btreeNode *createNode(int item, struct btreeNode *child)
{
    struct btreeNode *newNode = (struct btreeNode *)malloc(sizeof(struct btreeNode));
    newNode -> item[1] = item;
    newNode -> count = 1;
    newNode -> link[0] = root;
    newNode -> link[1] = child;
    return newNode;
}

// Insert
void insertValue(int item, int pos, struct btreeNode *node, struct btreeNode *child)
{
    int i = node->count;
    while (i > pos)
    {
        node->item[i + 1] = node->item[i];
        node->link[i + 1] = node->link[i];
        i--;
    }
    node->item[i + 1] = item;
    node->link[i + 1] = child;
    node->count++;
}

// Split node
void splitNode(int item, int *parVAl, int pos, struct btreeNode *node, struct btreeNode *child, struct btreeNode **newNode)
{
    int mid, i;

    if (pos > MIN)
        mid = MIN + 1;
    else
        mid = MIN;

        *newNode = (struct btreeNode *)malloc(sizeof(struct btreeNode));
        i = mid + 1;
        while (i <= MAX)
        {
            (*newNode)->item[i - mid] = node->item[i];
            (*newNode)->link[i - mid] = node->link[i];
            i++;
        }
        node->count = mid;
        (*newNode)->count = MAX - mid;

        if (pos <= MIN)
        {
            insertValue(item, pos, node, child);
        } 
        else 
        {
            insertValue(item, pos - mid, *newNode, child);
        } 
        *parVAl = node->item[node->count];
        (*newNode)->link[0] = node->link[node->count];
        node->count--;
}

// Set the value of node
int setNodeValue(int item, int *parVAl, struct btreeNode *node, struct btreeNode **child)
{
    int pos;
    if (!node) 
    {
    *parVAl = item;
    *child = NULL;
    return 1;
    }

    if (item < node->item[1]) 
    {
        pos = 0;
    } 
    else 
    {
        for (pos = node->count;
            (item < node->item[pos] && pos > 1); pos--)
            ;
            if (item == node->item[pos]) 
            {
                printf("Duplicates not allowed\n");
                return 0;
            }
    }
    if (setNodeValue(item, parVAl, node->link[pos], child)) 
    {
        if (node->count < MAX) 
        {
            insertValue(*parVAl, pos, node, *child);
        } 
        else 
        {
            splitNode(*parVAl, parVAl, pos, node, *child, child);
            return 1;
        }
    }
    return 0;
}

// Insert the value
void insert(int item) {
    int flag, i;
    struct btreeNode *child;

    flag = setNodeValue(item, &i, root, &child);
    if (flag)
        root = createNode(i, child);
}

// Copy the successor
void copySuccessor(struct btreeNode *node, int pos) 
{
    struct btreeNode *temp;
    temp = node->link[pos];

    for (; temp->link[0] != NULL;)
        temp = temp->link[0];
        node->item[pos] = temp->item[1];
}

// Do rightshift
void rightShift(struct btreeNode *node, int pos) 
{
    struct btreeNode *temp = node->link[pos];
    int i = temp->count;

    while (i > 0) {
        temp->item[i + 1] = temp->item[i];
        temp->link[i + 1] = temp->link[i];
    }
    temp->item[1] = node->item[pos];
    temp->link[1] = temp->link[0];
    temp->count++;

    temp = node->link[pos - 1];
    node->item[pos] = temp->item[temp->count];
    node->link[pos] = temp->link[temp->count];
    temp->count--;
}

// Do leftshift
void leftShift(struct btreeNode *node, int pos) 
{
    int i = 1;
    struct btreeNode *temp = node->link[pos - 1];

    temp->count++;
    temp->item[temp->count] = node->item[pos];
    temp->link[temp->count] = node->link[pos]->link[0];

    temp = node->link[pos];
    node->item[pos] = temp->item[1];
    temp->link[0] = temp->link[1];
    temp->count--;

    while (i <= temp->count) {
        temp->item[i] = temp->item[i + 1];
        temp->link[i] = temp->link[i + 1];
        i++;
    }

}

// Merge the nodes
void mergeNodes(struct btreeNode *node, int pos) 
{
    int i = 1;
    struct btreeNode *temp1 = node->link[pos], *temp2 = node->link[pos - 1];

    temp2->count++;
    temp2->item[temp2->count] = node->item[pos];
    temp2->link[temp2->count] = node->link[0];

    while (i <= temp1->count) {
        temp2->count++;
        temp2->item[temp2->count] = temp1->item[i];
        temp2->link[temp2->count] = temp1->link[i];
        i++;
    }

    i = pos;
    while (i < node->count) {
        node->item[i] = node->item[i + 1];
        node->link[i] = node->link[i + 1];
        i++;
    }
    node->count--;
    free(temp1);
}

// Adjust the node
void adjustNode(struct btreeNode *node, int pos) 
{
    if (!pos) {
        if (node->link[1]->count > MIN) {
            leftShift(node, 1);
        } 
        else 
        {
            mergeNodes(node, 1);
        }
    } 
    else 
    {
        if (node->count != pos) {
            if (node->link[pos - 1]->count > MIN) {
                rightShift(node, pos);
            } 
            else 
            {
                if (node->link[pos + 1]->count > MIN) {
                    leftShift(node, pos + 1);
                } 
                else 
                {
                    mergeNodes(node, pos);
                }
            }
        } 
        else 
        {
            if (node->link[pos - 1]->count > MIN)
                rightShift(node, pos);
            else
                mergeNodes(node, pos);
        }
    }
}

// Traverse the tree
void traversal(struct btreeNode *node) 
{
    int i;
    if (node)
    {
        for (i = 0; i < node->count; i++)
        {
            traversal(node->link[i]);
            printf("%d ", node->item[i + 1]);
        }
        traversal(node->link[i]);
    }
}

int main() {
    int item, ch;

    insert(11);
    insert(18);
    insert(10);
    insert(8);
    insert(23);
    insert(16);
    insert(17);
    insert(9);
    insert(20);
    insert(15);

    traversal(root);
}