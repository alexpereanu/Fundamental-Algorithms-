#include <stdio.h>
#include <stdlib.h>
#include "Profiler.h"
#define MAXSIZE 10000
Profiler profiler("QuickSort");

void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
	array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition(int arr[], int low, int high, int n)
{
	int pivot = arr[high]; 
	int dim = high + 1;// pivot 
	int i = (low - 1);  // Index of smaller element 
	profiler.countOperation("quickSort", n , 2);

	for (int j = low; j <= high - 1; j++)
	{
		if (arr[j] <= pivot)
		{
			i++;    
			profiler.countOperation("quickSort", n , 5);
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	profiler.countOperation("quickSort", n , 3);

	return (i + 1);
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quickSort(int arr[], int low, int high, int n )
{
	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
		   at right place */
		
		int pi = partition(arr, low, high, n);

		// Separately sort elements before 
		// partition and after partition 

		quickSort(arr, low, pi - 1, n);
		quickSort(arr, pi + 1, high,n);
	}
}


void printArray(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d ", arr[i]);
	printf("\n");
}


struct my_Heap {
	int n;
	int *v;
};

void swap2(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

void heapify_bottom_up(struct my_Heap* my_Heap, int i, int n)
{
	int maxim = i;
	int st = 2 * i + 1;
	int dr = 2 * i + 2;

	if (st < my_Heap->n && (my_Heap->v[st] > my_Heap->v[maxim]))
	{
		maxim = st;
		profiler.countOperation("BottomUp", n);
	}

	if (dr < my_Heap->n && (my_Heap->v[dr] > my_Heap->v[maxim]))
	{
		maxim = dr;
		profiler.countOperation("BottomUp", n);
	}

	if (maxim != i)
	{
		swap2(&my_Heap->v[maxim], &my_Heap->v[i]);
		profiler.countOperation("BottomUp", n, 3);
		heapify_bottom_up(my_Heap, maxim, n);
	}
}

struct my_Heap* create_heap(int n, int* v)
{
	struct my_Heap* my_Heap = (struct my_Heap*)malloc(sizeof(struct my_Heap));
	my_Heap->n = n;
	my_Heap->v = v;
	for (int i = (my_Heap->n - 2) / 2; i >= 0; i--)
		heapify_bottom_up(my_Heap, i, n);
	return my_Heap;
}

void heapSort(int* v, int n)
{
	struct my_Heap* Heap = create_heap(n, v);
	while (Heap->n > 1)
	{
		swap2(&Heap->v[0], &Heap->v[Heap->n - 1]);
		Heap->n--;
		profiler.countOperation("BottomUp", n, 4);
		heapify_bottom_up(Heap, 0, n);
	}
}

int main()
{

	int arr[] = { 10, 7, 8, 9, 1, 5 };
	int n = sizeof(arr) / sizeof(arr[0]);
	quickSort(arr, 0, n - 1,n);
	printf("Sorted array: ");
	printArray(arr, n);

	n = 8;
	int i;
	int x[] = { 10, 5, 7, 9, 11, 50, 2, -1 };
	heapSort(x, n);
	printf("\nHeap-ul Bottom_Up este:\n");
	for (i = 0; i < n; i++)
		printf("%d ", x[i]);

	//profiler.reset();
	
	//QUICK_SELECT
	/*
	int partition(int arr[], int l, int r)
{
	int x = arr[r], i = l;
	for (int j = l; j <= r - 1; j++) {
		if (arr[j] <= x) {
			swap(&arr[i], &arr[j]);
			i++;
		}
	}
	swap(&arr[i], &arr[r]);
	return i;
}

// This function returns k'th smallest
// element in arr[l..r] using QuickSort
// based method.  ASSUMPTION: ALL ELEMENTS
// IN ARR[] ARE DISTINCT
int kthSmallest(int arr[], int l, int r, int k)
{

	if (k > 0 && k <= r - l + 1) {

	
		int index = partition(arr, l, r);

		
		if (index - l == k - 1)
			return arr[index];

		if (index - l > k - 1)
			return kthSmallest(arr, l, index - 1, k);

		return kthSmallest(arr, index + 1, r,
							k - index + l - 1);
	}

	return INT_MAX;
}
	*/
	int a[100000], v[100000];
	for(i = 0; i < 5; i++)
		for (n = 100; n <= 10000; n += 100)
		{
			FillRandomArray(v, n, 10, 10000, false, 0);
			memcpy_s(a, n, v, n);
			quickSort(v, 0, n - 1, n);
			heapSort(a, n);

		}
	profiler.divideValues("quickSort", 5);
	profiler.divideValues("BottomUp", 5);
	profiler.createGroup("Rezultate_finale", "quickSort", "BottomUp");
	profiler.showReport();
	getchar();

	return 0;
}