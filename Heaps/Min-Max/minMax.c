// Implementation of Min-Max Heap in c

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

struct minMax
{
    int *heapArr;
    int size;
    int capacity;
};

typedef struct minMax minMax;

void insert(int heap[], int n, int x)
{
    int parent;
    n = n + 1;
    parent = n / 2;
}
