// insertioning a key on a B-tree in C

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>

#define MAX 3
#define MIN 2

struct btreeNode {
  int item[MAX + 1], count;
  struct btreeNode *link[MAX + 1];
};

struct btreeNode *root;

// Node creation
struct btreeNode *createNode(int item, struct btreeNode *child) {
  struct btreeNode *newNode;
  newNode = (struct btreeNode *)malloc(sizeof(struct btreeNode));
  newNode->item[1] = item;
  newNode->count = 1;
  newNode->link[0] = root;
  newNode->link[1] = child;
  return newNode;
}

// Insert
void insertValue(int item, int pos, struct btreeNode *node,
          struct btreeNode *child) {
  int j = node->count;
  while (j > pos) {
    node->item[j + 1] = node->item[j];
    node->link[j + 1] = node->link[j];
    j--;
  }
  node->item[j + 1] = item;
  node->link[j + 1] = child;
  node->count++;
}

// Split node
void splitNode(int item, int *parVAl, int pos, struct btreeNode *node,
         struct btreeNode *child, struct btreeNode **newNode) {
  int median, j;

  if (pos > MIN)
    median = MIN + 1;
  else
    median = MIN;

  *newNode = (struct btreeNode *)malloc(sizeof(struct btreeNode));
  j = median + 1;
  while (j <= MAX) {
    (*newNode)->item[j - median] = node->item[j];
    (*newNode)->link[j - median] = node->link[j];
    j++;
  }
  node->count = median;
  (*newNode)->count = MAX - median;

  if (pos <= MIN) {
    insertValue(item, pos, node, child);
  } else {
    insertValue(item, pos - median, *newNode, child);
  }
  *parVAl = node->item[node->count];
  (*newNode)->link[0] = node->link[node->count];
  node->count--;
}

// Set the value of node
int setNodeValue(int item, int *parVAl,
           struct btreeNode *node, struct btreeNode **child) {
  int pos;
  if (!node) {
    *parVAl = item;
    *child = NULL;
    return 1;
  }

  if (item < node->item[1]) {
    pos = 0;
  } else {
    for (pos = node->count;
       (item < node->item[pos] && pos > 1); pos--)
      ;
    if (item == node->item[pos]) {
      printf("Duplicates not allowed\n");
      return 0;
    }
  }
  if (setNodeValue(item, parVAl, node->link[pos], child)) {
    if (node->count < MAX) {
      insertValue(*parVAl, pos, node, *child);
    } else {
      splitNode(*parVAl, parVAl, pos, node, *child, child);
      return 1;
    }
  }
  return 0;
}

// Insert the value
void insertion(int item) {
  int flag, i;
  struct btreeNode *child;

  flag = setNodeValue(item, &i, root, &child);
  if (flag)
    root = createNode(i, child);
}

// Copy the successor
void copySuccessor(struct btreeNode *node, int pos) {
  struct btreeNode *temp;
  temp = node->link[pos];

  for (; temp->link[0] != NULL;)
    temp = temp->link[0];
  node->item[pos] = temp->item[1];
}

// Do rightshift
void rightShift(struct btreeNode *node, int pos) {
  struct btreeNode *x = node->link[pos];
  int j = x->count;

  while (j > 0) {
    x->item[j + 1] = x->item[j];
    x->link[j + 1] = x->link[j];
  }
  x->item[1] = node->item[pos];
  x->link[1] = x->link[0];
  x->count++;

  x = node->link[pos - 1];
  node->item[pos] = x->item[x->count];
  node->link[pos] = x->link[x->count];
  x->count--;
  return;
}

// Do leftshift
void leftShift(struct btreeNode *node, int pos) {
  int j = 1;
  struct btreeNode *x = node->link[pos - 1];

  x->count++;
  x->item[x->count] = node->item[pos];
  x->link[x->count] = node->link[pos]->link[0];

  x = node->link[pos];
  node->item[pos] = x->item[1];
  x->link[0] = x->link[1];
  x->count--;

  while (j <= x->count) {
    x->item[j] = x->item[j + 1];
    x->link[j] = x->link[j + 1];
    j++;
  }
  return;
}

// Merge the nodes
void mergeNodes(struct btreeNode *node, int pos) {
  int j = 1;
  struct btreeNode *x1 = node->link[pos], *x2 = node->link[pos - 1];

  x2->count++;
  x2->item[x2->count] = node->item[pos];
  x2->link[x2->count] = node->link[0];

  while (j <= x1->count) {
    x2->count++;
    x2->item[x2->count] = x1->item[j];
    x2->link[x2->count] = x1->link[j];
    j++;
  }

  j = pos;
  while (j < node->count) {
    node->item[j] = node->item[j + 1];
    node->link[j] = node->link[j + 1];
    j++;
  }
  node->count--;
  free(x1);
}

// Adjust the node
void adjustNode(struct btreeNode *node, int pos) {
  if (!pos) {
    if (node->link[1]->count > MIN) {
      leftShift(node, 1);
    } else {
      mergeNodes(node, 1);
    }
  } else {
    if (node->count != pos) {
      if (node->link[pos - 1]->count > MIN) {
        rightShift(node, pos);
      } else {
        if (node->link[pos + 1]->count > MIN) {
          leftShift(node, pos + 1);
        } else {
          mergeNodes(node, pos);
        }
      }
    } else {
      if (node->link[pos - 1]->count > MIN)
        rightShift(node, pos);
      else
        mergeNodes(node, pos);
    }
  }
}

// Traverse the tree
void traversal(struct btreeNode *node) {
  int i;
  if (node) {
    for (i = 0; i < node->count; i++) {
      traversal(node->link[i]);
      printf("%d ", node->item[i + 1]);
    }
    traversal(node->link[i]);
  }
}

int main() {
  int item, ch;

  insertion(8);
  insertion(9);
  insertion(10);
  insertion(11);
  insertion(15);
  insertion(16);
  insertion(17);
  insertion(18);
  insertion(20);
  insertion(23);

  traversal(root);
}