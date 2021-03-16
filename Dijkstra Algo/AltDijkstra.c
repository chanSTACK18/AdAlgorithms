// Implementation of Dijkstra Algorithm.

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>

#define MAX 10
#define INFINITY 9999

void Dijkstra(int Graph[MAX][MAX], int n, int start);

void Dijkstra(int Graph[MAX][MAX], int n, int start)
{
	int cost[MAX][MAX], dist[MAX], pred[MAX];
	int visited[MAX], count, minDist, nextNode,i,j;
	
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			if(Graph[i][j]==0)
			{
				cost[i][j] = INFINITY;
			}
			else
			{
				cost[i][j] = Graph[i][j];
			}
		}
	}
	for( i = 0; i<n; i++)
	{
		dist[i] = cost[start][i];
		pred[i] = start;
		visited[i] = 0;
	}
	dist[start] = 0;
	visited[start] = 1;
	count =1;
	
	while(count < n-1)
	{
		minDist = INFINITY;
	}
	for(i = 0; i < n; i++)
	{
		if (dist[i] < minDist && !visited[i])
		{
			minDist = dist[i];
			nextNode = 1;
		}
	}
	visited[nextNode] = 1;
	for(i = 0; i < n; i++)
	{
		if(!visited[i])
		{
			if (minDist+cost[nextNode][i]<dist[i]){
				dist[i] = minDist + cost[nextNode][i];
				pred[i] = nextNode;
			}
			count++;
		}
	}
	for(i = 0; i < n; i++)
	{
		if(i != start)
		{
			printf("Distance from source to %d: %d", i, dist[i]);
		}
	}
}

int main()
{
	int Graph[MAX][MAX], i, j, n, u;
	
	printf("\nEnter Number of Vertices: ");
	scanf("%d",&n);
	
	printf("\nEnter the Adjacency matrix:\n ");
	for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
	        scanf("%d",&Graph[i][j]);

	printf("\nEnter the starting Node: \n");
	scanf("%d",&u);
	


//	n = 7;
	
		
/*	Graph[0][0] = 0;
	Graph[0][1] = 0;
	Graph[0][2] = 1;
	Graph[0][3] = 2;
	Graph[0][4] = 0;
	Graph[0][5] = 0;
	Graph[0][6] = 0;
	
	Graph[1][0] = 0;
	Graph[1][1] = 2;
	Graph[1][2] = 0;
	Graph[1][3] = 0;
	Graph[1][4] = 0;
	Graph[1][5] = 3;
	Graph[1][6] = 0;
	
	Graph[2][0] = 1;
	Graph[2][1] = 2;
	Graph[2][2] = 0;
	Graph[2][3] = 1;
	Graph[2][4] = 3;
	Graph[2][5] = 0;
	Graph[2][6] = 0;
	
	Graph[3][0] = 2;
	Graph[3][1] = 0;
	Graph[3][2] = 1;
	Graph[3][3] = 0;
	Graph[3][4] = 0;
	Graph[3][5] = 0;
	Graph[3][6] = 1;
	
	Graph[4][0] = 0;
	Graph[4][1] = 0;
	Graph[4][2] = 3;
	Graph[4][3] = 0;
	Graph[4][4] = 0;
	Graph[4][5] = 2;
	Graph[4][6] = 0;
	
	Graph[5][0] = 0;
	Graph[5][1] = 3;
	Graph[5][2] = 0;
	Graph[5][3] = 0;
	Graph[5][4] = 2;
	Graph[5][5] = 0;
	Graph[5][6] = 1;
	
	Graph[6][0] = 0;
	Graph[6][1] = 0;
	Graph[6][2] = 0;
	Graph[6][3] = 1;
	Graph[6][4] = 0;
	Graph[6][5] = 1;
	Graph[6][6] = 0;   */    	
//	u = 0;
	Dijkstra(Graph, n, u);
	
	return 0;  
}
