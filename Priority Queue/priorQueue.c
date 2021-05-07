// Implementation of Priority Queue in c

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

void insert();
void delete ();
void display();

struct node
{
  int priority;
  int info;
  struct node *next;
} *start = NULL, *pQue, *temp, *newNode;

typedef struct node PriorQue;

void insert()
{
  int item, itemPrior;
  newNode = (PriorQue *)malloc(sizeof(PriorQue));
  printf("\n[+]Enter element to be inserted : ");
  scanf("%d", &item);
  printf("\n[+]Enter it's Priority : ");
  scanf("%d", &itemPrior);
  newNode->info = item;
  newNode->priority = itemPrior;
  newNode->next = NULL;
  if (start == NULL)
  {
    //newNode->next=start;
    start = newNode;
  }
  else if (start != NULL && itemPrior <= start->priority)
  {
    newNode->next = start;
    start = newNode;
  }
  else
  {
    pQue = start;
    while (pQue->next != NULL && pQue->next->priority <= itemPrior)
    {
      pQue = pQue->next;
    }
    newNode->next = pQue->next;
    pQue->next = newNode;
  }
}

void delete ()
{
  if (start == NULL)
  {
    printf("\n[-]Queue Underflow Condition!!");
  }
  else
  {
    newNode = start;
    printf("\n[-]Deleted Item is %d ", newNode->info);
    start = start->next;
    //free(start);
  }
}

void display()
{
  temp = start;
  if (start == NULL)
    printf("\n[-]Queue is Empty ");
  else
  {
    printf("\n[*]Queue IS: ");
    if (temp != NULL)
      for (temp = start; temp != NULL; temp = temp->next)
      {
        printf("\n[*] %d Priority = %d\n", temp->info, temp->priority);
        //temp=temp->next;
      }
  }
}

int main()
{
  int choice;
  do
  {
    printf("\n[1] INSERTION\t[2] DELETION\t[3] DISPLAY [4] EXIT\n[+]Enter your Choice: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
      insert();
      break;
    case 2:
      delete ();
      break;
    case 3:
      display();
      break;
    case 4:
      break;
    }
  } while (choice < 4);
}