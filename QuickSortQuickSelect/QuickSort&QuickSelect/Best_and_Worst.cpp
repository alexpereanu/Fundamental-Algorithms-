#include <stdio.h>
#include <stdlib.h>
#include "Profiler.h"

Profiler profiler("Best and Worst");

void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

int partition(int arr[], int low, int high, int n, int which)
{
	int pivot=arr[high];
	if (which == 0)
		 pivot = arr[high];
	else
		pivot = arr[high / 2];
	int i = (low - 1);  
	if (which == 0)
		profiler.countOperation("worstCase", n, 2);
	else
		profiler.countOperation("bestCase", n, 2);


	for (int j = low; j <= high - 1; j++)
	{
		
		if (arr[j] <= pivot)
		{
			i++;     
			if (which == 0)
				profiler.countOperation("worstCase", n, 5);
			else
				profiler.countOperation("bestCase", n, 5);
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	if (which == 0)
		profiler.countOperation("worstCase", n, 3);
	else
		profiler.countOperation("bestCase", n, 3);
	return (i + 1);
}


void quickSort(int arr[], int low, int high,int n,int which)
{
	if (low < high)
	{
		
		int pi = partition(arr, low, high, n, which);

		
		quickSort(arr, low, pi - 1,n,which);
		quickSort(arr, pi + 1, high,n,which);
	}
}


void printArray(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d ", arr[i]);
	printf("\n");
}


int main()
{
	/*int arr[] = { 10, 7, 8, 9, 1, 5 };
	int n = sizeof(arr) / sizeof(arr[0]);
	int i;
	int x=0;
	quickSort(arr, 0, n - 1, x, 0);
	printf("Sorted array: ");
	printArray(arr, n);
	getchar();
	*/
	int n, i;
	int worst[10000], best[10000];
	for (n = 100; n <= 10000; n += 100)
	{
		for (i = 100; i <= n; i++)
			worst[i] = i;
		quickSort(worst, 0, n - 1, n, 0);
	}
	for (n = 100; n <= 10000; n += 100)
	{
		FillRandomArray(best, n, 100, 10000, false, 0);
		quickSort(best, 0, n - 1, n, 1);

	}
	profiler.createGroup("Best&Worst", "bestCase", "worstCase");
	profiler.showReport();
	getchar();
	return 0;
}