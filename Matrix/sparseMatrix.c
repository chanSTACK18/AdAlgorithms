// Implementation of SparseMatrix using C
#include <stdio.h>
#define MAX 20

void read_matrix(int a[10][10], int rows, int cols);
void create_sparse(int a[10][10], int rows, int cols, int b[MAX][3]);
void print_sparse(int b[MAX][3]);

int main(){
    int a[10][10], b[MAX][3], rows, cols;
    printf("\nEnter the size of matrix(rows & cols):");
    scanf("%d%d",&rows,&cols);

    read_matrix(a, rows, cols);
    create_sparse(a, rows, cols, b);
    print_sparse(b);
    return 0;
}

void read_matrix(int a[10][10], int rows, int cols){
    int i,j;
    printf("\nEnter elements of matrix:\n");

    for ( i = 0; i < rows; i++)
    {
        for ( j = 0; j < cols; j++)
        {
            printf("[%d][%d]",i,j);
            scanf("%d",&a[i][j]);
        }
        
    }
    
}

void create_sparse(int a[10][10], int rows, int cols, int b[MAX][3]){
    int i,j,k;
    k = 1;
    b[0][0] = rows;
    b[0][1] = cols;

    for ( i = 0; i < rows; i++)
    {
        for ( j = 0; j < cols; j++)
        {
            if (a[i][j] != 0){
                b[k][0] = i;
                b[k][1] = j;
                b[k][2] = a[i][j];
                k++;
            }
        }
        b[0][2] = k-1;
    }
    
}

void print_sparse(int b[MAX][3]){
    int i, cols;
    cols = b[0][2];
    printf("\nSparse from - list of 3 triples\n\n");

    for ( i = 0; i < cols; i++)
    {
        printf("%d\t%d\t%d\n",b[i][0], b[i][1], b[i][2]);
    }
    
}