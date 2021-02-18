#include <stdio.h>
#include <stdlib.h>
#include "Profiler.h"
/*Se observa din grafic numarul mai mic de pasi realizat de construirea TopDown , datorat complexitatii O(nlogn) , fata de O(n^2) a construirii BottomUp
Metoda TopDown este mai eficienta, datorita faptului ca fiecare element inserat se verifica cu cate un parinte, iar in cazul favorabil
nu este nevoie de foarte multe schimbari iar in cazul BottomUp este nevoie de verificarea tutror stramosilor si interschimbarea, unde este cazul, pentru toate elementele.*/
Profiler profiler("Heap");

struct my_Heap {
	int n;
	int *v;
};

void change_parent(int a[], int i, int n);
void swap(int* a, int* b)
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
		profiler.countOperation("Bottom_Up", n);
	}

	if (dr < my_Heap->n && (my_Heap->v[dr] > my_Heap->v[maxim]))
	{
		maxim = dr;
		profiler.countOperation("Bottom_Up", n);
	}

	if (maxim != i)
	{
		swap(&my_Heap->v[maxim], &my_Heap->v[i]);
		profiler.countOperation("Bottom_Up", n, 3);
		heapify_bottom_up(my_Heap, maxim, n);
	}
}

void heapify_top_down(int a[], int n)
{
	int i;
	for (i = 1;i < n;i++)
		change_parent(a, i, n);
}

void change_parent(int a[], int i, int n)
{
	int k = a[i];
	int par = i / 2;
	while (a[par] < k && i != 0)
	{
		a[i] = a[par];
		i = par;
		par = i / 2;
		profiler.countOperation("Top_Down", n, 5);
	}
	a[i] = k;
	profiler.countOperation("Top_Down", n, 3);
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
		swap(&Heap->v[0], &Heap->v[Heap->n - 1]);
		Heap->n--;
		heapify_bottom_up(Heap, 0, n);
	}
}

int main()
{
	//Mai jos verificam faptul ca algoritmii sunt buni.
	int n=8, i;
	int v[] = { 10, 5, 7, 9, 11, 50, 2, -1 };
	int b[] = { 10, 5, 7, 9, 11, 50, 2, -1 };
	heapSort(v, n);
	printf("\nHeap-ul Bottom_Up este:\n");
	for (i = 0; i < n; i++)
		printf("%d ", v[i]);
	heapify_top_down(b, n);
	printf("\nHeap-ul Top_Down este:\n");
	for (i = 0; i < n; i++)
		printf("%d ", b[i]);
	profiler.reset();

	//Cazul mediu statistic.
	int x[100000], y[100000];
	for(i=0; i<5; i++)
		for (n = 100; n <= 100000; n += 100)
		{
			FillRandomArray(x, n, 10, 10000, false, 0);
			memcpy_s(y, n, x, n);
			heapSort(x, n);
			heapify_top_down(y, n);
		}
	profiler.divideValues("Bottom_Up", 5);
	profiler.divideValues("Top_Down", 5);
	profiler.createGroup("Rezultate_Heap", "Bottom_Up", "Top_Down");
	profiler.showReport();
	getchar();
	return 0;
}