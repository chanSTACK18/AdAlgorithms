/*
 ============================================================================
 Name        : sparseMatrix.c
 Author      : CodeSTACK
 Version     : v0.1.2
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include<stdio.h>
#define SpROW 50
#define ROW 20
#define COL 20

/*Begin of main*/
int main()
{
	int mat[ROW][COL],sparse[SpROW][3];
	int i,j,none_Zero = 0, rows, cols,SparseRow,Sparse;

	//taking inputs
	printf("\nEnter the size of Matrices(rows & cols): ");
	scanf("%d%d",&rows,&cols);

	for(i=0;i<rows;i++)
		for(j=0;j<cols;j++)
		{
			//taking inputs of rows and columns
			printf("[%d][%d]: ",i,j);
			scanf("%d",&mat[i][j]);
		}

	//printing entered matrix
	printf("Entered matrix is : \n");
	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)
		{
			printf("%6d",mat[i][j]);
			if(mat[i][j] != 0)
				none_Zero++;
		}
	printf("\n");
	}

	SparseRow = none_Zero+1;
	sparse[0][0] = rows;
	sparse[0][1] = cols;
	sparse[0][2] = none_Zero;
	Sparse = 1;

	for(i=0;i<rows;i++)
		for(j=0;j<cols;j++)
		{
			if(mat[i][j]!=0)
			{
				sparse[Sparse][0] = i+1;
				sparse[Sparse][1] = j+1;
				sparse[Sparse][2] = mat [i][j];
				Sparse++;
			}
	}

	//printing sparse matrix
	printf("Sparse matrix is :\n");
	for(i=0;i<SparseRow;i++)
	{
		for(j=0;j<3;j++)
			printf("%5d",sparse[i][j]);
		printf("\n");
	}
}

