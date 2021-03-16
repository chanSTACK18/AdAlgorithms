#include<stdio.h>
#include<conio.h>
#define INFINITY 9999
#define MAX 10

void dijkstra(int Graph[MAX][MAX],int n,int startNode);


void dijkstra(int Graph[MAX][MAX],int n,int startNode)
{
	int cost[MAX][MAX], Dist[MAX],pred[MAX];
	int visited[MAX],count,minDist,nextNode,i,j;
	
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			if(Graph[i][j]==0)
				cost[i][j]=INFINITY;
			else
				cost[i][j]=Graph[i][j];
	
	
	for(i=0;i<n;i++)
	{
		Dist[i]=cost[startNode][i];
		pred[i]=startNode;
		visited[i]=0;
	}
	
	Dist[startNode]=0;
	visited[startNode]=1;
	count=1;
	
	while(count<n-1)
	{
		minDist=INFINITY;
		
		
		for(i=0;i<n;i++)
			if(Dist[i]<minDist&&!visited[i])
			{
				minDist=Dist[i];
				nextNode=i;
			}
			
			//check if a better path exists through nextNode			
			visited[nextNode]=1;
			for(i=0;i<n;i++)
				if(!visited[i])
					if(minDist+cost[nextNode][i]<Dist[i])
					{
						Dist[i]=minDist+cost[nextNode][i];
						pred[i]=nextNode;
					}
		count++;
	}
	
	for(i=0;i<n;i++)
		if(i!=startNode)
		{
			printf("\nDistance of node%d=%d",i, Dist[i]);
			printf("\nPath=%d",i);
			
			j=i;
			do
			{
				j=pred[j];
				printf("<-%d",j);
			}while(j!=startNode);
	}
}

int main()
{
	int Graph[MAX][MAX],i,j,n,u;
	printf("Enter no. of vertices:");
	scanf("%d",&n);
	printf("\nEnter the adjacency matrix:\n");
	
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%d",&Graph[i][j]);
	
	printf("\nEnter the starting node:");
	scanf("%d",&u);
	dijkstra(Graph,n,u);
	
	return 0;
}