#include <stdlib.h>
#include <stdio.h>
#include "Profiler.h"

Profiler profiler("Kliste");

typedef struct Node
{
	int data;
	struct Node *next;
 } Node;

void insert(Node **first, int data, Node** last)
{
	Node *aux = (Node*)malloc(sizeof(Node));
	aux->data = data;
	aux->next = NULL;
	if (*first == NULL)
	{
		*first = aux;
		*last = aux;
	}
	else
	{
		(*last)->next = aux;
		*last = aux;
	}
}

void printList(Node *first)
{

	Node *a = first;
	while (a != NULL)
	{
		printf_s(" %d ", a->data);
		a = a->next;
	}
}

Node* sort(Node* list1, Node* list2, int nk, int k)
{
	Node* result = NULL;

	
	if (list1 == NULL)
	{
		if (k == 5)
			profiler.countOperation("K5", nk*k, 1);
		else if (k == 10)
		{
			profiler.countOperation("K10", nk*k, 1);
			profiler.countOperation("kVariabil", k, 1);
		}
		else if (k == 100)
		{
			profiler.countOperation("K100", nk*k, 1);
			profiler.countOperation("kVariabil", k, 1);
		}
		else
			profiler.countOperation("kVariabil", k, 1);

		return (list2);
	}

	else if (list2 == NULL)
	{
		if (k == 5)
			profiler.countOperation("K5", nk*k, 2);
		else if (k == 10)
		{
			profiler.countOperation("K10", nk*k, 2);
			profiler.countOperation("kVariabil", k, 2);
		}
		else if (k == 100)
		{
			profiler.countOperation("K100", nk*k, 2);
			profiler.countOperation("kVariabil", k, 2);
		}
		else
			profiler.countOperation("kVariabil", k, 2);

		return (list1);
	}

	//Alegem prima sau a doua lista si aplicam recurenta;
	if (list1->data <= list2->data)
	{
		result = list1;
		result->next = sort(list1->next, list2, nk, k);

		if (k == 5)
			profiler.countOperation("K5", nk*k, 3);

		else if (k == 10)
		{
			profiler.countOperation("K10", nk*k, 3);
		}

		else if (k == 100)
		{
			profiler.countOperation("K100", nk*k, 3);
		}
		else profiler.countOperation("Kvariabil", k, 3);

	}
	else
	{
		result = list2;
		result->next = sort(list1, list2->next, nk, k);
		if (k == 5)
			profiler.countOperation("K5", nk*k, 3);

		else if (k == 10)
		{
			profiler.countOperation("K10", nk*k, 3);
			profiler.countOperation("kVariabil", k, 3);
		}

		else if (k == 100)
		{
			profiler.countOperation("K100", nk*k, 3);
			profiler.countOperation("kVariabil", k, 3);
		}
		else profiler.countOperation("kVariabil", k, 3);

	}

	return result;
}

Node* mergeKLists(Node* arr[], int last, int nk, int k)
{
	// repeat until only one list is left 
	while (last != 0)
	{
		int i = 0, j = last;

		// (i, j) forms a pair 
		while (i < j)
		{
			// merge List i with List j and store 
			// merged list in List i 
			arr[i] = sort(arr[i], arr[j], nk, k);

			if (k == 5)
				profiler.countOperation("K5", nk*k, 1);
			else if (k == 10)
			{
				profiler.countOperation("K10", nk*k, 1);
				profiler.countOperation("kVariabil", k, 1);
			}
			else if (k == 100)
			{
				profiler.countOperation("K100", nk*k, 1);
				profiler.countOperation("kVariabil", k, 1);
			}
			else profiler.countOperation("kVariabil", k, 1);

			// consider next pair 
			i++, j--;

			// If all pairs are merged, update last 
			if (i >= j)
				last = j;
		}
	}

	return arr[0];
}

int main()
{
	int valoriK[3] = { 5, 10, 100 };
	int nk;

	Node* first[500];
	Node* last[500];

	int valoare, i, j, m, k;
	static int vectori[2000][2000];
	for (m = 0; m < 3; m++)
	{ 
		k = valoriK[m];
		for (nk = 100 / k; nk <= 10000 / k; nk = nk + 100 / k)
		{
			for (i = 0; i < k; i++)
				FillRandomArray(vectori[i], nk, -1000, 1000, false, 1);
			for (j = 0; j < k; j++)
			{
				first[j] = NULL;
				last[j] = NULL;
				for (i = 0; i < nk; i++)
				{
					valoare = vectori[j][i];
					insert(&first[j], valoare, &last[j]);
				}
				//printf_s("Lista este:");
				//printList(first[j]);
				//printf_s("\n\n");
				//getchar();
			}
			Node* head = mergeKLists(first, k - 1, nk, k);
			//printf("Lista este:");
			//printList(head);
			//printf("\n\n");
		}
		
	}
	profiler.createGroup("Result", "K5", "K10", "K100");
	profiler.showReport();
	profiler.reset("0000");
	//getchar();
	for (k = 10; k <= 500; k += 10)
	{
		m = 10000 / k;
		for (i = 0; i < k; i++)
			FillRandomArray(vectori[i], m, -100, 100, false, 1);
		for (j = 0; j < k; j++)
		{
			first[j] = NULL;
			last[j] = NULL;
			for (i = 0; i < m; i++)
			{
				valoare = vectori[j][i];
				insert(&first[j], valoare, &last[j]);
			}
			
		}
		Node* head = mergeKLists(first, k - 1, m, k);
	}
	profiler.showReport();
	return 0;
}