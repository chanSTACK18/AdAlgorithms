// Implementing Red-Black Tree in C

#include <stdio.h>
#include <stdlib.h>

enum nodeColor 
{
  RED,
  BLACK
};

struct rbNode {
  int data, color;
  struct rbNode *link[2];
};

struct rbNode *root = NULL;

// Create a red-black tree
struct rbNode *createNode(int data) {
  struct rbNode *newNode;
  newNode = (struct rbNode *)malloc(sizeof(struct rbNode));
  newNode->data = data;
  newNode->color = RED;
  newNode->link[0] = newNode->link[1] = NULL;
  return newNode;
}

// Insert an node
void insertNode(int data) {
  struct rbNode *stack[98], *ptr, *newNode, *xPtr, *yPtr;
  int dir[98], height = 0, index;
  ptr = root;
  if (!root) {
    root = createNode(data);
    return;
  }

  stack[height] = root;
  dir[height++] = 0;
  while (ptr != NULL) {
    if (ptr->data == data) {
      printf("Duplicates Not Allowed!!\n");
      return;
    }
    index = (data - ptr->data) > 0 ? 1 : 0;
    stack[height] = ptr;
    ptr = ptr->link[index];
    dir[height++] = index;
  }
  stack[height - 1]->link[index] = newNode = createNode(data);
  while ((height >= 3) && (stack[height - 1]->color == RED)) {
    if (dir[height - 2] == 0) {
      yPtr = stack[height - 2]->link[1];
      if (yPtr != NULL && yPtr->color == RED) {
        stack[height - 2]->color = RED;
        stack[height - 1]->color = yPtr->color = BLACK;
        height = height - 2;
      } else {
        if (dir[height - 1] == 0) {
          yPtr = stack[height - 1];
        } else {
          xPtr = stack[height - 1];
          yPtr = xPtr->link[1];
          xPtr->link[1] = yPtr->link[0];
          yPtr->link[0] = xPtr;
          stack[height - 2]->link[0] = yPtr;
        }
        xPtr = stack[height - 2];
        xPtr->color = RED;
        yPtr->color = BLACK;
        xPtr->link[0] = yPtr->link[1];
        yPtr->link[1] = xPtr;
        if (xPtr == root) {
          root = yPtr;
        } else {
          stack[height - 3]->link[dir[height - 3]] = yPtr;
        }
        break;
      }
    } else {
      yPtr = stack[height - 2]->link[0];
      if ((yPtr != NULL) && (yPtr->color == RED)) {
        stack[height - 2]->color = RED;
        stack[height - 1]->color = yPtr->color = BLACK;
        height = height - 2;
      } else {
        if (dir[height - 1] == 1) {
          yPtr = stack[height - 1];
        } else {
          xPtr = stack[height - 1];
          yPtr = xPtr->link[0];
          xPtr->link[0] = yPtr->link[1];
          yPtr->link[1] = xPtr;
          stack[height - 2]->link[1] = yPtr;
        }
        xPtr = stack[height - 2];
        yPtr->color = BLACK;
        xPtr->color = RED;
        xPtr->link[1] = yPtr->link[0];
        yPtr->link[0] = xPtr;
        if (xPtr == root) {
          root = yPtr;
        } else {
          stack[height - 3]->link[dir[height - 3]] = yPtr;
        }
        break;
      }
    }
  }
  root->color = BLACK;
}

// Delete a node
void deleteNode(int data) {
  struct rbNode *stack[98], *ptr, *xPtr, *yPtr;
  struct rbNode *pPtr, *qPtr, *rPtr;
  int dir[98], height = 0, diff, i;
  enum nodeColor color;

  if (!root) {
    printf("Tree not available\n");
    return;
  }

  ptr = root;
  while (ptr != NULL) {
    if ((data - ptr->data) == 0)
      break;
    diff = (data - ptr->data) > 0 ? 1 : 0;
    stack[height] = ptr;
    dir[height++] = diff;
    ptr = ptr->link[diff];
  }

  if (ptr->link[1] == NULL) {
    if ((ptr == root) && (ptr->link[0] == NULL)) {
      free(ptr);
      root = NULL;
    } else if (ptr == root) {
      root = ptr->link[0];
      free(ptr);
    } else {
      stack[height - 1]->link[dir[height - 1]] = ptr->link[0];
    }
  } else {
    xPtr = ptr->link[1];
    if (xPtr->link[0] == NULL) {
      xPtr->link[0] = ptr->link[0];
      color = xPtr->color;
      xPtr->color = ptr->color;
      ptr->color = color;

      if (ptr == root) {
        root = xPtr;
      } else {
        stack[height - 1]->link[dir[height - 1]] = xPtr;
      }

      dir[height] = 1;
      stack[height++] = xPtr;
    } else {
      i = height++;
      while (1) {
        dir[height] = 0;
        stack[height++] = xPtr;
        yPtr = xPtr->link[0];
        if (!yPtr->link[0])
          break;
        xPtr = yPtr;
      }

      dir[i] = 1;
      stack[i] = yPtr;
      if (i > 0)
        stack[i - 1]->link[dir[i - 1]] = yPtr;

      yPtr->link[0] = ptr->link[0];

      xPtr->link[0] = yPtr->link[1];
      yPtr->link[1] = ptr->link[1];

      if (ptr == root) {
        root = yPtr;
      }

      color = yPtr->color;
      yPtr->color = ptr->color;
      ptr->color = color;
    }
  }

  if (height < 1)
    return;

  if (ptr->color == BLACK) {
    while (1) {
      pPtr = stack[height - 1]->link[dir[height - 1]];
      if (pPtr && pPtr->color == RED) {
        pPtr->color = BLACK;
        break;
      }

      if (height < 2)
        break;

      if (dir[height - 2] == 0) {
        rPtr = stack[height - 1]->link[1];

        if (!rPtr)
          break;

        if (rPtr->color == RED) {
          stack[height - 1]->color = RED;
          rPtr->color = BLACK;
          stack[height - 1]->link[1] = rPtr->link[0];
          rPtr->link[0] = stack[height - 1];

          if (stack[height - 1] == root) {
            root = rPtr;
          } else {
            stack[height - 2]->link[dir[height - 2]] = rPtr;
          }
          dir[height] = 0;
          stack[height] = stack[height - 1];
          stack[height - 1] = rPtr;
          height++;

          rPtr = stack[height - 1]->link[1];
        }

        if ((!rPtr->link[0] || rPtr->link[0]->color == BLACK) &&
          (!rPtr->link[1] || rPtr->link[1]->color == BLACK)) {
          rPtr->color = RED;
        } else {
          if (!rPtr->link[1] || rPtr->link[1]->color == BLACK) {
            qPtr = rPtr->link[0];
            rPtr->color = RED;
            qPtr->color = BLACK;
            rPtr->link[0] = qPtr->link[1];
            qPtr->link[1] = rPtr;
            rPtr = stack[height - 1]->link[1] = qPtr;
          }
          rPtr->color = stack[height - 1]->color;
          stack[height - 1]->color = BLACK;
          rPtr->link[1]->color = BLACK;
          stack[height - 1]->link[1] = rPtr->link[0];
          rPtr->link[0] = stack[height - 1];
          if (stack[height - 1] == root) {
            root = rPtr;
          } else {
            stack[height - 2]->link[dir[height - 2]] = rPtr;
          }
          break;
        }
      } else {
        rPtr = stack[height - 1]->link[0];
        if (!rPtr)
          break;

        if (rPtr->color == RED) {
          stack[height - 1]->color = RED;
          rPtr->color = BLACK;
          stack[height - 1]->link[0] = rPtr->link[1];
          rPtr->link[1] = stack[height - 1];

          if (stack[height - 1] == root) {
            root = rPtr;
          } else {
            stack[height - 2]->link[dir[height - 2]] = rPtr;
          }
          dir[height] = 1;
          stack[height] = stack[height - 1];
          stack[height - 1] = rPtr;
          height++;

          rPtr = stack[height - 1]->link[0];
        }
        if ((!rPtr->link[0] || rPtr->link[0]->color == BLACK) &&
          (!rPtr->link[1] || rPtr->link[1]->color == BLACK)) {
          rPtr->color = RED;
        } else {
          if (!rPtr->link[0] || rPtr->link[0]->color == BLACK) {
            qPtr = rPtr->link[1];
            rPtr->color = RED;
            qPtr->color = BLACK;
            rPtr->link[1] = qPtr->link[0];
            qPtr->link[0] = rPtr;
            rPtr = stack[height - 1]->link[0] = qPtr;
          }
          rPtr->color = stack[height - 1]->color;
          stack[height - 1]->color = BLACK;
          rPtr->link[0]->color = BLACK;
          stack[height - 1]->link[0] = rPtr->link[1];
          rPtr->link[1] = stack[height - 1];
          if (stack[height - 1] == root) {
            root = rPtr;
          } else {
            stack[height - 2]->link[dir[height - 2]] = rPtr;
          }
          break;
        }
      }
      height--;
    }
  }
}

// Print the inorder traversal of the tree
void inOrderTraversal(struct rbNode *node) {
  if (node) {
    inOrderTraversal(node->link[0]);
    printf("%d  ", node->data);
    inOrderTraversal(node->link[1]);
  }
  return;
}

// Driver code
int main() {
  int ch, data;
  while (1) {
    printf("1. Insertion\t2. Deletion\n");
    printf("3. Traverse\t4. Exit");
    printf("\nEnter your choice:");
    scanf("%d", &ch);
    switch (ch) {
      case 1:
        printf("Enter the element to insert:");
        scanf("%d", &data);
        insertNode(data);
        break;
      case 2:
        printf("Enter the element to delete:");
        scanf("%d", &data);
        deleteNode(data);
        break;
      case 3:
        inOrderTraversal(root);
        printf("\n");
        break;
      case 4:
        exit(0);
      default:
        printf("Not available\n");
        break;
    }
    printf("\n");
  }
  return 0;
}