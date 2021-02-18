#include <stdio.h>
#include <stdlib.h>
#include "Profiler.h"

Profiler profiler("demo");
//structura nodului

typedef struct Node {
	Node* parent;
	int rank;
	int key;
	
}Node;

//crearea unui nou set doar pentru un anumit x
Node* MAKE_SET(int x, int n) {

	Node* node = (Node*)malloc(sizeof(Node));
	
	profiler.countOperation("disjuncte", n, 1);
	node->parent = node;
	node->key = x;
	node->rank = 0;

	return node;

}

Node* FIND_SET(Node* node, int n) {

	profiler.countOperation("disjuncte", n, 1);
	if (node != node->parent) {
		node->parent = FIND_SET(node->parent, n);
		profiler.countOperation("disjuncte", n, 1);
		return node->parent;
	}
	else
		return node;
}

/*LINK.x; y/
1 if x.rank > y.rank
2 y:p = x
3 else x.p = y
4 if x:rank == y:rank
5 y:rank = y.rank + 1*/

//aici se face path compression
Node* LINK_SET(Node* x, Node* y, int n) {

	if (x->rank > y->rank) {
		y->parent = x;
		profiler.countOperation("disjuncte", n, 1);
		return x;
	}
	else
	{
		x->parent = y;
		if (x->rank == y->rank)
			y->rank++;
		profiler.countOperation("disjuncte", n, 2);
		return y;
	}
}

Node* UNION(Node* x, Node* y, int n) {

	Node* z = LINK_SET(FIND_SET(x, n), FIND_SET(y, n), n);
	profiler.countOperation("disjuncte", n, 1);
	return z;
}

struct Edge
{
	int src, dest, weight;
};


struct Graph
{
	
	int V, E;
	struct Edge* edge;
};

struct Graph* createGraph(int V, int E,int n)
{
	struct Graph* graph = new Graph;
	graph->V = V;
	graph->E = E;
	graph->edge = new Edge[E];
	profiler.countOperation("disjuncte", n, 3);
	return graph;
}


struct subset
{
	int parent;
	int rank;
};


int find(struct subset subsets[], int i, int n)
{
	if (subsets[i].parent != i)
		subsets[i].parent = find(subsets, subsets[i].parent,n);
	profiler.countOperation("disjuncte", n, 1);
	return subsets[i].parent;
}


void Union(struct subset subsets[], int x, int y,int n)
{
	int xroot = find(subsets, x,n);
	int yroot = find(subsets, y,n);
	profiler.countOperation("disjuncte", n, 2);

	if (subsets[xroot].rank < subsets[yroot].rank)
		subsets[xroot].parent = yroot;
	else if (subsets[xroot].rank > subsets[yroot].rank)
		subsets[yroot].parent = xroot;

	else
	{
		subsets[yroot].parent = xroot;
		subsets[xroot].rank++;
		profiler.countOperation("disjuncte", n, 2);
	}
}

int myComp(const void* a, const void* b)
{
	struct Edge* a1 = (struct Edge*)a;
	struct Edge* b1 = (struct Edge*)b;
	return a1->weight > b1->weight;
}

void KruskalMST(struct Graph* graph,int n)
{
	int V = graph->V;
	struct Edge result[10000];  
	int e = 0;
	int i = 0;
	profiler.countOperation("disjuncte", n, 3);


	qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);

	
	struct subset *subsets =(struct subset*) malloc(V * sizeof(struct subset));

	for (int v = 0; v < V; ++v)
	{
		subsets[v].parent = v;
		subsets[v].rank = 0;
		profiler.countOperation("disjuncte", n, 2);
	}

	while (e < V - 1)
	{
		struct Edge next_edge = graph->edge[i++];

		int x = find(subsets, next_edge.src,n);
		int y = find(subsets, next_edge.dest,n);

		if (x != y)
		{
			result[e++] = next_edge;
			Union(subsets, x, y,n);
		}
	}

	printf_s("Following are the edges in the constructed MST\n");
	for (i = 0; i < e; ++i)
		printf("%d -- %d == %d\n", result[i].src, result[i].dest,
			result[i].weight);
			
	//return;
}

int main() {

	/*int i;
	Node** p = (Node**)malloc(sizeof(Node*));

	for (i = 0; i < 10; i++)
		*(p + i) = MAKE_SET(i, 10);

	UNION(p[1], p[3], 10);
	UNION(p[2], p[4], 10);
	UNION(p[3], p[2], 10);

	for (int i = 0; i <= 9; i++) {
		printf_s("Nod %d, Parinte %d\n", p[i]->key, p[i]->parent->key);
	}
	getchar();*/

	//struct Graph* graph = createGraph(V, E);

	// add edge 0-1 
	//graph->edge[0].src = 0;
	//graph->edge[0].dest = 1;
	//graph->edge[0].weight = 10;

	int n=0;
	int noduri = 0;
	int muchii = 0;
	while (noduri < 10000) {
		noduri = noduri + 100;
		muchii = muchii + 400;
		struct Graph* graph = createGraph(noduri, muchii,n);
		printf_s("%d ", noduri);
			for (int i = 0; i < noduri; i++)
			{
				graph->edge[i].src = int(rand()%23);
				graph->edge[i].dest = int(rand()%12);
				graph->edge[i].weight = int(rand()%5);

			}
		
		KruskalMST(graph,n);
	}

	profiler.showReport();
	getchar();
	return 0;
	
}