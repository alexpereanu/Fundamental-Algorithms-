#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1000000

# include "Profiler.h"
int v[MAX_SIZE];
int top = -1;

Profiler profiler("DFS");

void push(int x)
{
	if (top == MAX_SIZE)
	{
		printf_s("Stiva full");
		return;
	}
	else
	{
		top = top + 1;
		v[top] = x;
	}
}

void pop(int v[MAX_SIZE])
{
	if (top == -1)
	{
		printf("Stiva este goala");
		return;
	}
	else
		top = top - 1;
	
}

int varfStiva()
{
	int aux = v[top];
	v[top] = 0;
	top--;
	return aux;
}

int IsEmpty(int v[MAX_SIZE])
{
	if (top == -1)
		return 1;
	else return 0;
}



struct node
{
	int vertex;
	struct node* next;
};

struct node* createNode(int v);

struct Graph
{
	int numVertices;
	int* visited;
	struct node** adjLists; 
};

struct Graph* createGraph(int vertices,int n)
{
	struct Graph* graph = (Graph*)malloc(sizeof(struct Graph));
	graph->numVertices = vertices;
	profiler.countOperation("DFS", n, 2);

	graph->adjLists = (node**)malloc(vertices * sizeof(struct node*));

	graph->visited = (int*)malloc(vertices * sizeof(int));
	profiler.countOperation("DFS", n, 2);

	int i;
	for (i = 0; i < vertices; i++) {
		graph->adjLists[i] = NULL;
		graph->visited[i] = 0;
		profiler.countOperation("DFS", n, 2);
	}
	return graph;
}

void addEdge(struct Graph* graph, int src, int dest, int n)
{
	// Add edge from src to dest
	struct node* newNode = createNode(dest);
	newNode->next = graph->adjLists[src];
	graph->adjLists[src] = newNode;
	profiler.countOperation("DFS", n, 3);


	// Add edge from dest to src
	newNode = createNode(src);
	newNode->next = graph->adjLists[dest];
	graph->adjLists[dest] = newNode;
	profiler.countOperation("DFS", n, 3);
}

void printGraph(struct Graph* graph)
{
	int v;
	for (v = 0; v < graph->numVertices; v++)
	{
		struct node* temp = graph->adjLists[v];
		printf("\n Adjacency list of vertex %d\n ", v);
		while (temp)
		{
			printf("%d -> ", temp->vertex);
			temp = temp->next;
		}
		printf("\n");
	}
}

struct node* createNode(int v)
{
	struct node* newNode = (node*)malloc(sizeof(struct node));
	newNode->vertex = v;
	newNode->next = NULL;
	return newNode;
}

void DFS(struct Graph* graph, int vertex, int n) {


	int nrc = 0, h, w;

	graph->visited[vertex] = 1;
	push(vertex);

	while (IsEmpty(v) != 1 && nrc != graph->numVertices)
	{
		h = varfStiva();
		graph->visited[h] = 1;
		profiler.countOperation("DFS", n, 2);
		profiler.countOperation("DFS", n, 2);

		
		printf_s("%d ", h);
		node* temp = graph->adjLists[h];
		nrc++;
		profiler.countOperation("DFS", n, 2);

		while (temp)
		{
			int adjVertex = temp->vertex;
			profiler.countOperation("DFS", n, 1);
			profiler.countOperation("DFS", n, 1);

			if (graph->visited[adjVertex] == 0)
			{
				profiler.countOperation("DFS", n, 1);
				push(adjVertex);
			}
			temp = temp->next;
			profiler.countOperation("DFS", n, 1);
		}
	}
}


int main()
{

	int n = 0;
	struct Graph* graph = createGraph(7,n);
	addEdge(graph, 0, 1,n);
	addEdge(graph, 0, 2,n);
	addEdge(graph, 1, 2,n);
	addEdge(graph, 2, 3,n);
	addEdge(graph, 3, 4,n);
	addEdge(graph, 4, 5, n);
	addEdge(graph, 5, 6, n);
	


	printGraph(graph);

	DFS(graph, 1, n);
	getchar();

	/*int n=0,E;
	int V = 100;
	int noduri[4600];

	for (E = 1000; E < 4600; E += 100)
	{
		struct Graph* graph = createGraph(100);
		FillRandomArray(noduri, 4600, 10, 100, false, 0);
		printf_s("feri");
		for (int i = 0; i < E; i++)
			addEdge(graph, noduri[i],i%85,n);
		DFS(graph, 0, n);
		n += 100;
	}

	n = 100;
	E = 4500;
	V = 100;

	for (V = 100; V < 210; V += 10)
	{
		struct Graph* graph = createGraph(V,n);
		FillRandomArray(noduri, 4500, 10, 100, false, 0);
		//printf_s("feri");
		for (int i = 0; i < E; i++)
			addEdge(graph, noduri[i], rand()%85, n);
		//printf_s("feri");
		DFS(graph, 0, n);
		n += 10;
	}
	profiler.showReport();
	getchar();
	*/
	
	//getchar();
	return 0;
}




