#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

#define MAX 50
#define INF 9999

int i,j,k,a,b,u,v,n,no_edges=1;
int min,minCost=0,cost[MAX][MAX],parent[MAX];
int find(int);
int uni(int,int);
void main()
{
	printf("\n\tImplementation of Kruskal algorithm\n");
	printf("\nEnter the no. of vertices:");
	scanf("%d",&n);
	printf("\nEnter the cost adjacency matrix:\n");
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			scanf("%d",&cost[i][j]);
			if(cost[i][j]==0)
				cost[i][j]=INF;
		}
	}
	printf("The edges of Minimum Cost Spanning Tree are\n");
	while(no_edges < n)
	{
		for(i=1,min=INF;i<=n;i++)
		{
			for(j=1;j <= n;j++)
			{
				if(cost[i][j] < min)
				{
					min=cost[i][j];
					a=u=i;
					b=v=j;
				}
			}
		}
		u=find(u);
		v=find(v);
		if(uni(u,v))
		{
			printf("%d edge (%d,%d) =%d\n",no_edges++,a,b,min);
			minCost +=min;
		}
		cost[a][b]=cost[b][a] = INF;
	}
	printf("\n\tMinimum cost = %d\n",minCost);
}
int find(int i)
{
	while(parent[i])
	i=parent[i];
	return i;
}
int uni(int i,int j)
{
	if(i!=j)
	{
		parent[j]=i;
		return 1;
	}
	return 0;
}