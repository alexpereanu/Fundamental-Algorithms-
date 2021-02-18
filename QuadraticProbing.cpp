#include <stdio.h>
#include <stdlib.h>
#include "Profiler.h"
#define SIZE 10007

Profiler profiler("Hash");

int arr[SIZE];


int hashing(int key)
{
	return key % SIZE;
}

int cauta(int key)
{
	int nr = 0;
	int h = 1;

	int index = hashing(key);
	while (arr[index] != NULL)
	{
		nr++;
		if (arr[index] == key)
			return index + 1;
		index = (index + (h * h)) % SIZE;
		h++;
	}
	return 0 - nr;
}

void inserare(int key)
{
	int index = hashing(key);
	int h = 1;

	while (arr[index] != NULL)
	{
		index = (index + (h * h)) % SIZE;
		h++;
	}
	arr[index] = key;
}

int sterge(int key)
{
	int index = hashing(key);
	int ok = 0;
	int h = 1;

	while (arr[index] != NULL)
	{
		if (arr[index] == key)
		{
			ok = 1;
			arr[index] = NULL;
			return ok;
		}
		index = (index + (h * h)) % SIZE;
		h++;
	}
	return ok;
}

void stergetot()
{
	int i;
	for (i = 0; i < SIZE; i++)
	{
		if (arr[i] != NULL)arr[i] = NULL;
	}
}

void afisare()
{
	int i = 0;
	for (i = 0; i < SIZE; i++)
	{
		if (arr[i] != NULL)
			printf(" (%d)", arr[i]);
		else
			printf(" NULL ");
	}
	printf("\n");
}

int main()
{
	int a[SIZE], b[SIZE], c[1501];
	int i, j, k, m, s, ss, nrgasit, nrnegasit, sumagasit, maximgasit, ngas, nnegas, maximnegasit, sumanegasit;
	FillRandomArray(a, SIZE, 0, 200000, true);
	int alfa[4] = { 85,90,95,99 };

	for (j = 0; j < 4; j++)
	{
		sumagasit = 0;
		maximgasit = -1;
		ngas = 0;
		nnegas = 0;
		maximnegasit = -1;
		sumanegasit = 0;
		for (k = 0; k < 5; k++)
		{
			FillRandomArray(a, SIZE, 0, 200000, true);
			FillRandomArray(b, SIZE, 0, 10006, true);
			FillRandomArray(c, 1500, 250000, 300000);
			int proc = SIZE * alfa[j] / 100;
			for (i = 0; i < proc; i++)
			{
				inserare(a[i]);
			}

			for (m = 0; m < 1550; m++)
			{
				s = cauta(a[b[m]]);
				if (s >= 0)
				{
					nrgasit = s - hashing(a[b[m]]);
					if (nrgasit < 0)
						nrgasit = SIZE - 1 - hashing(a[b[m]]) + s;
					sumagasit += nrgasit;
					if (nrgasit > maximgasit)
						maximgasit = nrgasit;
					ngas++;
				}
				else
				{
					nnegas++;
					nrnegasit = 0 - s + 1;
					sumanegasit += nrnegasit;
					if (nrnegasit > maximnegasit)maximnegasit = nrnegasit;
				}
			}
			for (m = 0; m < 1450; m++)
			{
				s = cauta(c[m]);
				nnegas++;
				nrnegasit = 0 - s + 1;
				sumanegasit += nrnegasit;
				if (nrnegasit > maximnegasit)
					maximnegasit = nrnegasit;
			}
			stergetot();
		}
		sumagasit = sumagasit / 5 / ngas;
		sumanegasit = sumanegasit / 5 / nnegas;
		printf("\n\nPentru factorul de umplere %d%%:\n", alfa[j]);
		printf("Efort mediu gasite: %d\n", sumagasit);
		printf("Efort maxim gasite: %d\n", maximgasit);
		printf("Efort mediu negasite: %d\n", sumanegasit);
		printf("Efort maxim negasite: %d\n", maximnegasit);
	}
	getchar();
	
}
