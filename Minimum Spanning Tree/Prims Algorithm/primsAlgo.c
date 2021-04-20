
#include<stdio.h>
#include<stdlib.h>

#define INF 9999
#define MAX 100

int Graph[MAX][MAX],spanning[MAX][MAX],n;

int prims();

int main()
{
	int i,j,total_cost;
	printf("Enter no. of vertices:");
	scanf("%d",&n);
	
	printf("\nEnter the adjacency matrix:\n");
	
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%d",&Graph[i][j]);
	
	total_cost=prims();
	printf("\nspanning tree matrix:\n");
	
	for(i=0;i<n;i++)
	{
		printf("\n");
		for(j=0;j<n;j++)
			printf("%d\t",spanning[i][j]);
	}
	
	printf("\n\nTotal cost of spanning tree=%d",total_cost);
	return 0;
}

int prims()
{
	int cost[MAX][MAX];
	int u,v,minDist,distance[MAX],from[MAX];
	int visited[MAX],no_of_edges,i,minCost,j;
	
	//create cost[][] matrix,spanning[][]
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			if(Graph[i][j]==0)
				cost[i][j]=INF;
			else
				cost[i][j]=Graph[i][j];
				spanning[i][j]=0;
		}
		
	//initialise visited[],distance[] and from[]
	distance[0]=0;
	visited[0]=1;
	
	for(i=1;i<n;i++)
	{
		distance[i]=cost[0][i];
		from[i]=0;
		visited[i]=0;
	}
	
	minCost=0;		//cost of spanning tree
	no_of_edges=n-1;		//no. of edges to be added
	
	while(no_of_edges>0)
	{
		//find the vertex at minimum distance from the tree
		minDist=INF;
		for(i=1;i<n;i++)
			if(visited[i]==0&&distance[i]<minDist)
			{
				v=i;
				minDist=distance[i];
			}
			
		u=from[v];
		
		//insert the edge in spanning tree
		spanning[u][v]=distance[v];
		spanning[v][u]=distance[v];
		no_of_edges--;
		visited[v]=1;
		
		//updated the distance[] array
		for(i=1;i<n;i++)
			if(visited[i]==0&&cost[i][v]<distance[i])
			{
				distance[i]=cost[i][v];
				from[i]=v;
			}
		
		minCost=minCost+cost[u][v];
	}
	
	return(minCost);
}