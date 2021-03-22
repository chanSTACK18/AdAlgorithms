#include <stdio.h>
#include <stdlib.h>

#define nV 4
#define INF 999

void printMatrix(int matrix[][nV]);

void floydWarshall(int Graph[][nV])
{
    int matrix[nV][nV], i, j, k;
    for(i = 0; i < nV; i++)
    {
        for(j = 0; j < nV; j++)
        {
            matrix[i][j] = Graph[i][j];
        }
    }
    for(k = 0; k < nV; k++)
    {
        for(i = 0; i < nV; i++)
        {
            for(j = 0; j < nV; j++)
            {
                if(matrix[i][k] + matrix[k][j] < matrix[i][j])
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
            }
        }
    }
    printMatrix(matrix);
}

void printMatrix(int matrix[][nV])
{
	int i, j;
    printf ("The following matrix shows the shortest distances"
            " between every pair of vertices \n");
	for(i = 0; i < nV; i++)
	{
		for(j = 0; j < nV; j++)
		{
			if (matrix[i][j] = INF)
			{
				printf("%7s","INF");
			}
			else
			{
				printf("%7d",matrix[i][j]);
			}
		}
		printf("\n");
	}
}

int main()
{
    int Graph[nV][nV] = {
        {0, 5, INF, 10},
        {INF, 0, 3, INF},
        {INF, INF, 0, 1},
        {INF, INF, INF,1}
    };
    floydWarshall(Graph);

    return 0;
}
