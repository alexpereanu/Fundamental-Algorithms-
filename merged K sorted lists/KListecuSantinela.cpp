#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "Profiler.h"


#define INFINITY INT_MAX
#define LCHILD(x) 2*x+1
#define RCHILD(x) 2*x+2
#define PARENT(x) (x - 1)/2

Profiler profiler("Merge k sorted lists");

int nrOfElements;
int nrOfLists;

typedef struct node {
	int key;
	struct node *next;
	struct node*previous;
}NodeT;

typedef struct sentinel {
	NodeT *head;
	NodeT *tail;
	int nrOfNodes;
}Sentinel;

typedef struct nod_heap {
	int data;
}nod_heap;

typedef struct minHeap {
	int size;
	nod_heap* elem;
}minHeap;



Sentinel *sentinels;

NodeT* create_node(int key);
int peek(Sentinel*);
void delete_first(Sentinel *sentinel);
void add_last(Sentinel *sentinel, int key);
void init_sentinels(Sentinel*sentinels, int number);
void create_lists(int, int);
void print_vector(int *, int);
void print_list(Sentinel *, int);
void insertNode(minHeap* hp, int data);
void deleteNode(minHeap *hp);
void heapify(minHeap *hp, int i);
void swap(nod_heap *n1, nod_heap *n2);
void buildMinHeap(minHeap *hp, int *arr, int size);
void preorderTraversal(minHeap *hp, int i);
minHeap initMinHeap(int size);
void levelOrderTraversal(minHeap *hp);
int top1(minHeap* hp);







int main()
{
	int *vector;
	minHeap* heap = &initMinHeap(1);

	nrOfElements = 50;
	nrOfLists = 5;

	create_lists(nrOfElements, nrOfLists);

	for (int i = 0; i < nrOfLists; i++)
	{

		print_list(sentinels, i);
	}

	print_list(head, 0);
	getchar();
	

	/*
	minHeap* heap = &initMinHeap(50);
	int* arr;
	arr = (int*)malloc(50 * sizeof(int));
	FillRandomArray(arr, 50, 10, 1000, false, 1);
	for (int i = 0; i < 50; i++)
		insertNode(heap, arr[i]);
	levelOrderTraversal(heap);
	getchar();*/

	return 0;
}

void print_list(Sentinel *sentinel, int i)
{
	NodeT *aux = sentinel[i].head;
	int number = sentinel[i].nrOfNodes;
	printf("List %d:\n", i);
	while (number > 0)
	{
		printf("%d -> ", aux->key);
		number--;
		aux = aux->next;
	}
	printf("NULL\n");
}

void print_vector(int *vector, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", vector[i]);
	}
	printf("\n");
}

void create_lists(int n, int k)
{
	int *vector;
	int nrOfElementsInAList = n / k; //Atentie trebuie tratate toate cazurile de dimensiune
	int currentElement = 0;

	vector = (int *)malloc(sizeof(int)*n);
	if (NULL == vector)
	{
		perror("Error at allocating memory for the lists total elements.\n");
		exit(2);
	}


	sentinels = (Sentinel*)malloc(sizeof(Sentinel)*k);

	if (NULL == sentinels)
	{
		perror("Error at allocating memory for the sentinel.\n");
		exit(2);
	}

	init_sentinels(sentinels, k);
	FillRandomArray(vector, n, 10, 1000, false, 1);
	/*
	minHeap* heap = &initMinHeap(50);
	int* arr;
	arr = (int*)malloc(50 * sizeof(int));
	FillRandomArray(arr, 50, 10, 1000, false, 1);
	for (int i = 0; i < 50; i++)
		insertNode(heap, arr[i]);
	levelOrderTraversal(heap);
	getchar();*/

	print_vector(vector, n);

	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < nrOfElementsInAList; j++)
		{
			add_last((sentinels + i), vector[currentElement + j]);
		}
		currentElement += nrOfElementsInAList;
	}
	struct node* head = NULL, *last;
	minHeap* heap = &initMinHeap(0);
	for (int i = 0; i < n; i++)
		insertNode(heap, vector[i]);
	while (heap->size != 0)
	{
		struct node* top = top1(heap);
		deleteNode(heap);
		if (top->next != NULL)
			insertNode(heap,top->next->key);
		if (head == NULL)
		{
			head = top;
			last = top;
		}
		else
		{
			last->next = top;
			last = top;
		}

	}
	
}

NodeT *create_node(int key)
{
	NodeT *newNode = (NodeT *)malloc(sizeof(NodeT));
	if (NULL == newNode)
	{
		perror("Error at allocating memory for a new node.\n");
		exit(2);
	}
	newNode->next = NULL;
	newNode->previous = NULL;
	newNode->key = key;
	return newNode;
}

void add_last(Sentinel *sentinel, int key)
{
	if (NULL == sentinel->head)
	{
		sentinel->head = create_node(key);
		sentinel->tail = sentinel->head;
		sentinel->nrOfNodes = 1;
	}
	else {
		NodeT *newNode = create_node(key);
		newNode->previous = sentinel->tail;
		sentinel->tail->next = newNode;
		sentinel->head->previous = newNode;
		sentinel->tail = newNode;
		sentinel->tail->next = sentinel->head;
		sentinel->nrOfNodes++;
	}
}

int peek(Sentinel *sentinel)
{
	if (0 != sentinel->nrOfNodes)
	{
		return sentinel->head->key;
	}
	else {
		return INFINITY;
	}
}

void delete_first(Sentinel *sentinel)
{
	if (0 != sentinel->nrOfNodes)
	{
		NodeT *aux = sentinel->head;
		sentinel->tail->next = sentinel->head->next;
		sentinel->head = sentinel->head->next;
		sentinel->head->previous = sentinel->tail;
		free(aux);
		sentinel->nrOfNodes--;
	}
}

void init_sentinels(Sentinel*sentinels, int number)
{
	for (int i = 0; i < number; i++)
	{
		sentinels[i].head = NULL;
		sentinels[i].tail = NULL;
		sentinels[i].nrOfNodes = 0;
	}
}

minHeap initMinHeap(int size) {
	minHeap hp;
	hp.size = 0;
	return hp;
}

void insertNode(minHeap* hp, int data) {
	// allocating space
	if (hp->size) {
		hp->elem = (nod_heap*)realloc(hp->elem, (hp->size + 1) * sizeof(nod_heap));
	}
	else {
		hp->elem = (nod_heap*)malloc(sizeof(nod_heap));
	}

	// initializing the node with value
	nod_heap nd;
	nd.data = data;

	// Positioning the node at the right position in the min heap
	int i = (hp->size)++;
	while (i && nd.data < hp->elem[PARENT(i)].data) {
		hp->elem[i] = hp->elem[PARENT(i)];
		i = PARENT(i);
	}
	hp->elem[i] = nd;
	
}

void deleteNode(minHeap *hp) {
	if (hp->size) {
		printf("Deleting node %d\n\n", hp->elem[0].data);
		hp->elem[0] = hp->elem[--(hp->size)];
		hp->elem = (nod_heap*)realloc(hp->elem, hp->size * sizeof(nod_heap));
		heapify(hp, 0);
	}
	else {
		printf("\nMin Heap is empty!\n");
		free(hp->elem);
	}
}

void heapify(minHeap *hp, int i) {
	int smallest = (LCHILD(i) < hp->size && hp->elem[LCHILD(i)].data < hp->elem[i].data) ? LCHILD(i) : i;
	if (RCHILD(i) < hp->size && hp->elem[RCHILD(i)].data < hp->elem[smallest].data) {
		smallest = RCHILD(i);
	}
	if (smallest != i) {
		swap(&(hp->elem[i]), &(hp->elem[smallest]));
		heapify(hp, smallest);
	}
}

void swap(nod_heap *n1, nod_heap *n2) {
	nod_heap temp = *n1;
	*n1 = *n2;
	*n2 = temp;
}

void buildMinHeap(minHeap *hp, int *arr, int size) {
	int i;

	// Insertion into the heap without violating the shape property
	for (i = 0; i < size; i++) {
		if (hp->size) {
			hp->elem =(nod_heap*)realloc(hp->elem, (hp->size + 1) * sizeof(nod_heap));
		}
		else {
			hp->elem = (nod_heap*)malloc(sizeof(nod_heap));
		}
		nod_heap nd;
		nd.data = arr[i];
		hp->elem[(hp->size)++] = nd;
	}

	// Making sure that heap property is also satisfied
	for (i = (hp->size - 1) / 2; i >= 0; i--) {
		heapify(hp, i);
	}
}

void preorderTraversal(minHeap *hp, int i) {
	if (LCHILD(i) < hp->size) {
		preorderTraversal(hp, LCHILD(i));
	}
	if (RCHILD(i) < hp->size) {
		preorderTraversal(hp, RCHILD(i));
	}
	printf("%d ", hp->elem[i].data);
}

void levelOrderTraversal(minHeap *hp) {
	int i;
	for (i = 0; i < hp->size; i++) {
		printf("%d ", hp->elem[i].data);
	}
}

void isEmpty(minHeap* heap)
{

}

struct node* mergeKSortedList(Sentinel* sentinel, int k)
{
	struct node* head = NULL, *last;
	minHeap* heap = &initMinHeap(0);
	


}