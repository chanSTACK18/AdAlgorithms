// Implementation of Binomial Heap Tree

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

struct node
{
    int n;
    int degree;
    struct node *parent;
    struct node *child;
    struct node *sibling;
};

struct node *MakeBinHeap();
int BinLink(struct node *, struct node *);
struct node *CreateNode(int);
struct node *bin_HEAP_UNION(struct node *, struct node *);
struct node *bin_HEAP_INSERT(struct node *, struct node *);
struct node *bin_HEAP_MERGE(struct node *, struct node *);
struct node *bin_HEAP_EXTRACT_MIN(struct node *);
int Revert_List(struct node *);
int Display(struct node *);
struct node *FIND_NODE(struct node *, int);
int bin_HEAP_DECREASE_KEY(struct node *, int, int);
int bin_HEAP_DELETE(struct node *, int);

int count = 1;

struct node *MakeBinHeap()
{
    struct node *np;
    np = NULL;
    return np;
}

struct node *H = NULL;
struct node *Hr = NULL;

int BinLink(struct node *y, struct node *z)
{
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree = z->degree + 1;
}

struct node *CreateNode(int k)
{
    struct node *p;
    p = (struct node *)malloc(sizeof(struct node));
    p->n = k;
    return p;
}

struct node *bin_HEAP_UNION(struct node *H1, struct node *H2)
{
    struct node *prev_x;
    struct node *next_x;
    struct node *x;
    struct node *H = MakeBinHeap();
    H = bin_HEAP_MERGE(H1, H2);
    if (H == NULL)
        return H;
    prev_x = NULL;
    x = H;
    next_x = x->sibling;
    while (next_x != NULL)
    {
        if ((x->degree != next_x->degree) || ((next_x->sibling != NULL) && (next_x->sibling)->degree == x->degree))
        {
            prev_x = x;
            x = next_x;
        }
        else
        {
            if (x->n <= next_x->n)
            {
                x->sibling = next_x->sibling;
                BinLink(next_x, x);
            }
            else
            {
                if (prev_x == NULL)
                    H = next_x;
                else
                    prev_x->sibling = next_x;
                BinLink(x, next_x);
                x = next_x;
            }
        }
        next_x = x->sibling;
    }
    return H;
}

struct node *bin_HEAP_INSERT(struct node *H, struct node *x)
{
    struct node *H1 = MakeBinHeap();
    x->parent = NULL;
    x->child = NULL;
    x->sibling = NULL;
    x->degree = 0;
    H1 = x;
    H = bin_HEAP_UNION(H, H1);
    return H;
}

struct node *bin_HEAP_MERGE(struct node *H1, struct node *H2)
{
    struct node *H = MakeBinHeap();
    struct node *y;
    struct node *z;
    struct node *a;
    struct node *b;
    y = H1;
    z = H2;
    if (y != NULL)
    {
        if (z != NULL && y->degree <= z->degree)
            H = y;
        else if (z != NULL && y->degree > z->degree)
            H = z;
        else
            H = y;
    }
    else
        H = z;
    while (y != NULL && z != NULL)
    {
        if (y->degree < z->degree)
        {
            y = y->sibling;
        }
        else if (y->degree == z->degree)
        {
            a = y->sibling;
            y->sibling = z;
            y = a;
        }
        else
        {
            b = z->sibling;
            z->sibling = y;
            z = b;
        }
    }
    return H;
}

int Display(struct node *H)
{
    struct node *p;
    if (H == NULL)
    {
        printf("\n[-]Heap is Empty");
        return 0;
    }
    printf("\n[*]Root Nodes are: \n");
    p = H;
    while (p != NULL)
    {
        printf("%d", p->n);
        if (p->sibling != NULL)
            printf("-->");
        p = p->sibling;
    }
    printf("\n");
}

struct node *bin_HEAP_EXTRACT_MIN(struct node *H1)
{
    int min;
    struct node *t = NULL;
    struct node *x = H1;
    struct node *Hr;
    struct node *p;
    Hr = NULL;
    if (x == NULL)
    {
        printf("\n[-]Nothing to Extraction");
        return x;
    }

    p = x;
    while (p->sibling != NULL)
    {
        if ((p->sibling)->n < min)
        {
            min = (p->sibling)->n;
            t = p;
            x = p->sibling;
        }
        p = p->sibling;
    }
    if (t == NULL && x->sibling == NULL)
        H1 = NULL;
    else if (t == NULL)
        H1 = x->sibling;
    else if (t->sibling == NULL)
        t = NULL;
    else
        t->sibling = x->sibling;
    if (x->child != NULL)
    {
        Revert_List(x->child);
        (x->child)->sibling = NULL;
    }
    H = bin_HEAP_UNION(H1, Hr);
    return x;
}

int Revert_List(struct node *y)
{
    if (y->sibling != NULL)
    {
        Revert_List(y->sibling);
        (y->sibling)->sibling = y;
    }
    else
    {
        Hr = y;
    }
}

struct node *FIND_NODE(struct node *H, int k)
{
    struct node *x = H;
    struct node *p = NULL;
    if (x->n == k)
    {
        p = x;
        return p;
    }
    if (x->child != NULL && p == NULL)
    {
        p = FIND_NODE(x->child, k);
    }

    if (x->sibling != NULL && p == NULL)
    {
        p = FIND_NODE(x->sibling, k);
    }
    return p;
}

int bin_HEAP_DECREASE_KEY(struct node *H, int i, int k)
{
    int temp;
    struct node *p;
    struct node *y;
    struct node *z;
    p = FIND_NODE(H, i);
    if (p == NULL)
    {
        printf("\n[x]Invalid Choice of key to be Reduced.");
        return 0;
    }
    if (k > p->n)
    {
        printf("\n[!!]New key is Greater then current one.");
        return 0;
    }
    p->n = k;
    y = p;
    z = p->parent;
    while (z != NULL && y->n < z->n)
    {
        temp = y->n;
        y->n = z->n;
        z->n = temp;
        y = z;
        z = z->parent;
    }
    printf("\n[*]Key Reduced Successfully!");
}

int bin_HEAP_DELETE(struct node *H, int k)
{
    struct node *np;
    if (H == NULL)
    {
        printf("\n[-]Heap is Empty");
        return 0;
    }

    bin_HEAP_DECREASE_KEY(H, k, -1000);
    np = bin_HEAP_EXTRACT_MIN(H);
    if (np != NULL)
        printf("\n[-]Node Deleted Successfully");
}

int main()
{
    int i, n, m, l;
    struct node *p;
    struct node *np;
    char ch;
    printf("\n[+]Enter No. of elements: ");
    scanf("%d", &n);
    printf("\n[+]Enter the elements: \n");
    for (i = 1; i <= n; i++)
    {
        scanf("%d", &m);
        np = CreateNode(m);
        H = bin_HEAP_INSERT(H, np);
    }
    Display(H);
    do
    {
        printf(
            "\n[1]Insert an element\n[2]Extract Minimum Key Node\n[3]Decrease a Node Key\n[4]Delete a Node\n[5]Exit\n");
        printf("\n[+]Enter your choice: ");
        scanf("%d", &l);
        switch (l)
        {
        case 1:
            do
            {
                printf("\n[+]Enter the Element to be Inserted: ");
                scanf("%d", &m);
                p = CreateNode(m);
                H = bin_HEAP_INSERT(H, p);
                printf("\n[*]Heap is: \n");
                Display(H);
                printf("\n[+]Insert More(y)\n");
                fflush(stdin);
                scanf("%c", &ch);
            } while (ch == 'Y' || ch == 'y');
            break;
        case 2:
            do
            {
                printf("\n[+]Extracting Minimum Key Node");
                p = bin_HEAP_EXTRACT_MIN(H);
                if (p != NULL)
                    printf("\n[*]Extracted Node is %d", p->n);
                printf("\n[*]Now, Heap is:\n");
                Display(H);
                printf("\n[+]Extract More(y)\n");
                fflush(stdin);
                scanf("%c", &ch);
            } while (ch == 'Y' || ch == 'y');
            break;
        case 3:
            do
            {
                printf("\n[+]Enter Key of the Node to be Decreased: ");
                scanf("%d", &m);
                printf("\n[+]Enter New Key : ");
                scanf("%d", &l);
                bin_HEAP_DECREASE_KEY(H, m, l);
                printf("\n[*]Now, The Heap is:\n");
                Display(H);
                printf("\n[+]Decreae More(y)\n");
                fflush(stdin);
                scanf("%c", &ch);
            } while (ch == 'Y' || ch == 'y');
            break;
        case 4:
            do
            {
                printf("\n[+]Enter Key to be Deleted: ");
                scanf("%d", &m);
                bin_HEAP_DELETE(H, m);
                printf("\n[+]Delete More(y)\n");
                fflush(stdin);
                scanf("%c", &ch);
            } while (ch == 'y' || ch == 'Y');
            break;
        case 5:
            printf("\n[E]Exit From the Heap . . .\n");
            break;
        default:
            printf("\n[x]Invalid entry...Try again....\n");
        }
    } while (l != 5);
}