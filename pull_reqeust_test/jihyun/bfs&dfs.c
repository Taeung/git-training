#if 0 //1260
#include <stdio.h>
#include <stdlib.h>
int maze[1001][1001]={0};
int visitedBFS[1001]={0};
int visitedDFS[1001]={0};
int que[1001]={0};
int N,M,start;
int head=0, tail=0;

doDFS(int v);
doBFS(int v);

void push_q(int v);
int deque();
int isQueEmpty();
void add_vertex(int v1, int v2);

int main(void)
{

	int v1, v2;
	int i;
	scanf("%d %d %d", &N,&M,&start);

	
	for(i=0;i<M;i++)
	{
		scanf("%d %d",&v1,&v2);
		add_vertex(v1,v2);
	}
	
	doDFS(start);
	printf("\n");
	doBFS(start);
}

void add_vertex(int v1, int v2)
{
	maze[v1][v2] = 1;
	maze[v2][v1] = 1;
}

doDFS(int v)
{
	int i;
	printf("%d ",v);
	visitedDFS[v] = 1;
	for(i=1;i<=N;i++)
	{
		if(maze[v][i] == 1 && visitedDFS[i] == 0)
			doDFS(i);
	}
	return;
}

doBFS(int v)
{
	int i;
	int k;
	push_q(v);
	visitedBFS[v] = 1;
	
	while(isQueEmpty()==0)
	{
		k = deque();
		printf("%d ",k);
		for(i=1;i<=N;i++)
		{
			if(maze[k][i] == 1 && visitedBFS[i] == 0)
			{
			
				push_q(i);
				visitedBFS[i] = 1;
			}
		}
	}

}

int deque()
{
 	return que[head++];
}
void push_q(int v)
{
	que[tail++] = v;
}

int isQueEmpty()
{
	if(head == tail)
	{
		return 1;
	}
	else return 0;
}

#endif

#if 0 //10451
#include <stdio.h>

int maze[1001][1001]={0};
int visited[1001]={0};
int cnt=0;
int N;
int start;
int stack[1001]={0};
int top;

void doDFS(int v);

int main(void)
{
	int testcase,M;
	int i,j,k;
	int arr[1001]={0};
	scanf("%d",&testcase);
	
	for(i=0;i<testcase;i++)
	{
		scanf("%d",&N);
		for(j=1;j<=N;j++)
		{
			scanf("%d",&arr[j]);
		}
		
		for(j=1;j<=N;j++)
		{
			maze[j][arr[j]] = 1;
			maze[arr[j]][j] = 1;
		}
		
		for(j=1;j<=N;j++)
		{
			if(visited[j] == 0)
			{
				doDFS(j);
				cnt++;
			}
		}
		printf("%d\n",cnt);
		
		cnt =0;
		top =0;
		for(j=1;j<=N;j++)
		{
			visited[j] =0;
			stack[j] = 0;
		}
		for(j=1;j<=N;j++)
		{
			for(k=1;k<=N;k++)
			{
				maze[j][k] = 0;
			}
		}
		
	}

	
}

void doDFS(int v)
{
	int i;
	int k;
	int check=0;
	visited[v] = 1;
	stack[top++] = v;
	while(top >0)
	{
		k = stack[top-1];
		check = 0;
		
		for(i=1;i<=N;i++)
		{
			if(maze[k][i] == 1 && visited[i] == 0)
			{
				stack[top++] = i;
				visited[i] = 1;
				check = 1;
				break;
			}	
		}
		if(check == 0) top--;
	}
	

}
#endif

