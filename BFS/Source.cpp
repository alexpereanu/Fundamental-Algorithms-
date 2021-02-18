#include <stdio.h>
#include <stdlib.h>
#include "Profiler.h"
#define SIZE 100

Profiler profiler("BFS");

struct queue {
	int items[SIZE];
	int front;
	int rear;
};
struct node
{
	int vertex;
	struct node* next;
};

struct node* createNode(int);

struct Graph
{
	int numVertices;
	struct node** adjLists;
	int* visited;
};

struct queue* createQueue();
void enqueue(struct queue* q, int);
int dequeue(struct queue* q);
void display(struct queue* q);
int isEmpty(struct queue* q);
void printQueue(struct queue* q);


void bfs(struct Graph* graph, int startVertex,int n,int x) {

	struct queue* q = createQueue();

	graph->visited[startVertex] = 1;
	if (x == 0)
		profiler.countOperation("BFS", n, 1);
	else
		profiler.countOperation("BFS2", n, 1);
	enqueue(q, startVertex);

	while (!isEmpty(q)) {
		//printQueue(q);
		int currentVertex = dequeue(q);
		if (x == 0)
			profiler.countOperation("BFS", n, 1);
		else
			profiler.countOperation("BFS2", n, 1);

		struct node* temp = graph->adjLists[currentVertex];
		if (x == 0)
			profiler.countOperation("BFS", n, 1);
		else
			profiler.countOperation("BFS2", n, 1);

		while (temp) {
			int adjVertex = temp->vertex;
			if (x == 0)
				profiler.countOperation("BFS", n, 1);
			else
				profiler.countOperation("BFS2", n, 1);
			if (graph->visited[adjVertex] == 0) {
				graph->visited[adjVertex] = 1;
				if (x == 0)
					profiler.countOperation("BFS", n, 1);
				else
					profiler.countOperation("BFS2", n, 1);
				
				enqueue(q, adjVertex);
			}
			temp = temp->next;
			if (x == 0)
				profiler.countOperation("BFS", n, 1);
			else
				profiler.countOperation("BFS2", n, 1);
		}
	}
}

struct node* createNode(int v)
{
	struct node* newNode = (node*)malloc(sizeof(struct node));
	newNode->vertex = v;
	newNode->next = NULL;
	return newNode;
}
struct Graph* createGraph(int vertices)
{
	struct Graph* graph = (Graph*)malloc(sizeof(struct Graph));
	graph->numVertices = vertices;

	graph->adjLists = (node**)malloc(vertices * sizeof(struct node*));
	graph->visited = (int*)malloc(vertices * sizeof(int));


	int i;
	for (i = 0; i < vertices; i++) {
		graph->adjLists[i] = NULL;
		graph->visited[i] = 0;
		//profiler.countOperation("BFS", n, 2);
	}
	//profiler.countOperation("BFS", n, 4);
	return graph;
}

void addEdge(struct Graph* graph, int src, int dest,int n,int x)
{
	// Add edge from src to dest
	struct node* newNode = createNode(dest);
	newNode->next = graph->adjLists[src];
	graph->adjLists[src] = newNode;

	// Add edge from dest to src
	newNode = createNode(src);
	newNode->next = graph->adjLists[dest];
	graph->adjLists[dest] = newNode;
	if (x == 0)
		profiler.countOperation("BFS", n, 1);
	else
		profiler.countOperation("BFS2", n, 1);
}

struct queue* createQueue() {
	struct queue* q = (queue*)malloc(sizeof(struct queue));
	q->front = -1;
	q->rear = -1;
	return q;
}


int isEmpty(struct queue* q) {
	if (q->rear == -1)
		return 1;
	else
		return 0;
}

void enqueue(struct queue* q, int value) {
	if (q->rear == SIZE - 1)
		printf("\nQueue is Full!!");
	else {
		if (q->front == -1)
			q->front = 0;
		q->rear++;
		q->items[q->rear] = value;
	}
}

int dequeue(struct queue* q) {
	int item;
	if (isEmpty(q)) {
		printf("Queue is empty");
		item = -1;
	}
	else {
		item = q->items[q->front];
		q->front++;
		if (q->front > q->rear) {
			//printf("Resetting queue");
			q->front = q->rear = -1;
		}
	}
	return item;
}

void printQueue(struct queue *q) {
	int i = q->front;

	if (isEmpty(q)) {
		printf("Queue is empty");
	}
	else {
		printf("\nQueue contains \n");
		for (i = q->front; i < q->rear + 1; i++) {
			printf("%d ", q->items[i]);
		}
	}
}


int main()
{
	/*struct Graph* graph = createGraph(6);
	addEdge(graph, 0, 1);
	addEdge(graph, 0, 2);
	addEdge(graph, 1, 2);
	addEdge(graph, 1, 4);
	addEdge(graph, 1, 3);
	addEdge(graph, 2, 4);
	addEdge(graph, 3, 4);

	bfs(graph, 0);*/



	int n=1000,E;
	int V = 100;
	struct Graph* graph = createGraph(100);
	int x = 0;
	for (E = 1000; E < 4600; E += 100)
	{
		int noduri[4600];
		FillRandomArray(noduri, 4600, 10, 100, false, 0);
		//printf_s("feri");
		for (int i = 0; i < E; i++)
			addEdge(graph, noduri[i], i%100,n,0);
		//printf_s("feri");
		bfs(graph, 0, n,0);
		n += 100;
		//if (E == 1000)
			//profiler.reset();
	}
	

	 n = 100;
	 E = 4500;
	 V = 100;
	for (V = 100; V < 210; V += 10)
	{
		int noduri[4500];
		FillRandomArray(noduri, 4500, 10, 100, false, 0);
		//printf_s("feri");
		for (int i = 0; i < E; i++)
			addEdge(graph, noduri[i], i % 100, n,1);
		//printf_s("feri");
		bfs(graph, 0, n,1);
		n += 10;
		if (E == 1000)
			profiler.reset();
	}
	profiler.createGroup("BFS_Rez", "BFS", "BFS2");
	//profiler.showReport();
	getchar();

	return 0;
}



