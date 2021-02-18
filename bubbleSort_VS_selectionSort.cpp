#include <stdio.h>
#include <stdlib.h>
#include "Profiler.h"

/*Dupa cum se poate vedea pe grafice,in cazul mediu algoritmul Insertion_sort este cel mai bun dintre cele 3, avand cel mai mic timp de executie.
In schimb, bubble_sort este cel mai slab dintre cele 3, dar in Best Case, bubble_sort este cel mai rapid, nefacand nici o atribuire ci doar un numar mic de comparatii.
In Best Case, insertion ocupa abia locul 2 dintre cei 3 algoritmi. De precizat faptul ca Insertion Sort este foarte,foarte util in momentul in care vectorul nostru este aproape sortat.
La Bubble Sort, algoritmul se comporta astfel: compara 2 cate 2 elemente, iar daca cel de-al doilea este mai mic ca primul atunci le interschimba. Dupa prima iteratie a algoritmului suntem
absolut siguri ca maximul din vectorul nostru va ajunge pe prima pozitie.
La Insertion sort algoritmul este putin mai diferit. Se imparte sirul in 2: un sir sortat iar altul nesortat. Se porneste de la al doilea element din sir si se compara cu primul.
In cazul in care cel de-al doilea element este mai mic, se interschimba cele 2 valori si apoi acestea vor face parte din sirul sortat. La a 2-a iteratie, adica cel de-al 3-lea element din sir,
se verifica daca acesta este mai mic decat ultimul element din sirul sortat. In caz ca este mai mic, algoritmul nostru ii cauta locul in vectorul sortat, il insereaza acolo si trece la urmatorul
element.
In cazul Selection Sort, algoritmul este foarte asemanator cu Insertion Sort. Selection cauta intotdeauna elementul minim din sir si il insereaza in fata
In cazul mediu, toti cei 3 algoritmi au complexitatea O(n^2)
*/

//Declarare profiler
Profiler profiler("Direct Sorting");

//Prototipurile functiilor folosite in program
void read_vector(int **, int *);

void print_vector(int *, int);

void bubble_sort(int *, int);

void swap(int *, int*);

void best_case();

void worstCase();

void averageCase();


int main()
{
	int n, i;
	int *v;

	//read_vector(&v, &n);          Pasul 1

	//print_vector(v, n);           Pasul 1

	//bubble_sort(v, n);		    Pasul 1

	//print_vector(v, n);			Pasul 1

	//best_case();  //				Pasul 2
	//average_case();               TODO
	//worstCase();
	averageCase();
	profiler.showReport();    //	Pasul 2


	getchar();
	return 0;
}
void read_vector(int **v, int *n)
{
	FILE *fIn;
	int i;
	errno_t error;

	if (0 != (error = fopen_s(&fIn, "input.txt", "r")))
	{
		perror("Eroare la citire fisier.\n");
		getchar();
		exit(error);
	}

	fscanf_s(fIn, "%d", n);

	if (NULL == (*v = (int*)calloc(sizeof(int), *n)))
	{
		perror("Eroare la alocare memorie.\n");
		exit(1);
	}

	for (i = 0; i < *n; i++)
	{
		fscanf_s(fIn, "%d", &(*v)[i]);
	}

	fclose(fIn);
}

void print_vector(int *v, int n)
{
	int i;

	printf_s("Vectorul este: \n");

	for (i = 0; i < n; i++)
	{
		printf_s("%d ", v[i]);
	}

	printf_s("\n");
}


//Metoda bubble sort imbunatatita.
// Am ales aceasta metoda deoarece metoda clasica necesita un timp de rulare prea mare.

void bubble_sort(int *v, int n)
{
	int i, j, temp, notSorted;

	notSorted = 1;

	while (notSorted)
	{
		notSorted = 0;
		for (i = 0; i < n - 1; i++)
		{
			profiler.countOperation("Bubble_sort_comparissons", n);
			if (v[i] > v[i + 1])
			{
				profiler.countOperation("Bubble_sort_assignments", n, 3);
				swap(&v[i], &v[i + 1]);
				notSorted = 1;
			}
		}
	}
}

void swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void selection_sort(int* a, int size)
{
	int i, j, min;
	for (i = 0; i < size - 1; i++)
	{
		profiler.countOperation("Selection_sort_assignments", size, 1);
		min = i;
		for (j = i + 1; j < size; j++)
			profiler.countOperation("Selection_sort_comparissons", size, 1);
		if (a[j] < a[min])
			min = j;
		int x = a[i];
		a[i] = a[min];
		a[min] = x;
		profiler.countOperation("Selection_sort_assignments", size, 4);
	}
}

void insertionSort(int* arr, int n)
{
	int i, key, j;
	for (i = 1; i < n; i++)
	{
		key = arr[i]; 
		j = i - 1;
		profiler.countOperation("Insertion_sort_assignments", n, 2);

		/*  Permuta  elementele vectorului arr[0..i-1] ce sunt mai mari decat key, incrementand cu 1 indexul la care acum ele se afla */
		while (j >= 0 && arr[j] > key)
		{
			profiler.countOperation("Insertion_sort_comparissons", n, 2);
			arr[j + 1] = arr[j];
			j = j - 1;
			profiler.countOperation("Insertion_sort_assignments", n, 2);
			
		}
		arr[j + 1] = key;
		profiler.countOperation("Insertion_sort_assignments", n, 1);
	}

}
void best_case()
{
	int *v, n;
	int* selection;
	int* insertion;
	/* Atentie!
	* Trebuie sa alocam memorie pentru vector chiar daca il generam cu FillRandomArray
	* Este mai rapid sa alocam o singura zona de memorie de dimensiune maxima,
	* decat sa alocam zone de memorie la fiecare iteratie din for.
	*/
	if (NULL == (v = (int*)calloc(sizeof(int), 10000)))
	{
		perror("Error at allocating memory.\n");
		getchar();
		exit(1);
	} 
	if (NULL == (selection = (int*)calloc(sizeof(int), 10000)))
	{
		perror("Error at allocating memory.\n");
		getchar();
		exit(1);
	}
	if (NULL == (insertion = (int*)calloc(sizeof(int), 10000)))
	{
		perror("Error at allocating memory.\n");
		getchar();
		exit(1);
	}

	for (n = 100; n <= 10000; n += 200)
	{
		//Initializare operatii
		// In cazul in care nu are loc nicio asignare sau comparatie, graficul va sti sa indice 0.
		profiler.countOperation("Bubble_sort_comparissons", n, 0);
		profiler.countOperation("Bubble_sort_assignments", n, 0);
		profiler.countOperation("Selection_sort_assignments", n, 0);
		profiler.countOperation("Selection_sort_comparissons", n, 0);
		profiler.countOperation("Insertion_sort_assignments", n, 0);
		profiler.countOperation("Insertion_sort_comparissons", n, 0);
		// Generare sir de numere. Semnatura si parametrii functiei sunt in fisierul Profiler de pe moodle.
		FillRandomArray(v, n, 0, 999, false, 1);
		memcpy_s(insertion, n, v, n);
		memcpy_s(selection, n, v, n);
		bubble_sort(v, n);
		//Tot aici v-om executa si ceilalti algoritmi.
		selection_sort(selection,n);
		insertionSort(insertion,n);
		//Dorim sa vedem si numarul total de operatii si nu doar numarul de asignari sau comparatii individual
		profiler.addSeries("Bubble_sort_sum", "Bubble_sort_comparissons", "Bubble_sort_assignments");
		// La fel pentru 
		// Insertion_sort
		profiler.addSeries("Insertion_sort_sum", "Insertion_sort_comparissons", "Insertion_sort_assignments");
		// Selection_sort
		profiler.addSeries("Selection_sort_sum", "Selection_sort_comparissons", "Selection_sort_assignments");

	}

	profiler.createGroup("Best_Case_Assignments", "Bubble_sort_assignments", "Insertion_sort_assignments", "Selection_sort_assignments");
	profiler.createGroup("Best_Case_Comparissons", "Bubble_sort_comparissons", "Insertion_sort_comparissons", "Selection_sort_comparissons");
	profiler.createGroup("Best_Case_Sum", "Bubble_sort_sum", "Selection_sort_sum", "Insertion_sort_sum");

	
	free(v);
	free(selection);
	free(insertion);
}

void worstCase()
{
		int *v, n;
		int* selection;
		int* insertion;
		if (NULL == (v = (int*)calloc(sizeof(int), 10000)))
		{
			perror("Error at allocating memory.\n");
			getchar();
			exit(1);
		}
		if (NULL == (selection = (int*)calloc(sizeof(int), 10000)))
		{
			perror("Error at allocating memory.\n");
			getchar();
			exit(1);
		}
		if (NULL == (insertion = (int*)calloc(sizeof(int), 10000)))
		{
			perror("Error at allocating memory.\n");
			getchar();
			exit(1);
		}

		for (n = 100; n <= 10000; n += 200)
		{
			
			profiler.countOperation("Bubble_sort_comparissons", n, 0);
			profiler.countOperation("Bubble_sort_assignments", n, 0);
			profiler.countOperation("Selection_sort_assignments", n, 0);
			profiler.countOperation("Selection_sort_comparissons", n, 0);
			profiler.countOperation("Insertion_sort_assignments", n, 0);
			profiler.countOperation("Insertion_sort_comparissons", n, 0);
			
			FillRandomArray(v, n, 0, 999, false, 2);
			memcpy_s(insertion, n, v, n);
			memcpy_s(selection, n, v, n);
			
			bubble_sort(v, n);
			selection_sort(selection, n);
			insertionSort(insertion, n);

			profiler.addSeries("Bubble_sort_sum", "Bubble_sort_comparissons", "Bubble_sort_assignments");
			profiler.addSeries("Insertion_sort_sum", "Insertion_sort_comparissons", "Insertion_sort_assignments");
			profiler.addSeries("Selection_sort_sum", "Selection_sort_comparissons", "Selection_sort_assignments");

		}

		profiler.createGroup("Worst_Case_Assignments", "Bubble_sort_assignments", "Insertion_sort_assignments", "Selection_sort_assignments");
		profiler.createGroup("Worst_Case_Comparissons", "Bubble_sort_comparissons", "Insertion_sort_comparissons", "Selection_sort_comparissons");
		profiler.createGroup("Worst_Case_Sum", "Bubble_sort_sum", "Selection_sort_sum", "Insertion_sort_sum");

		
		free(v);
		free(selection);
		free(insertion);
}

void averageCase()
{
	int *v, n;
	int* selection;
	int* insertion;
	if (NULL == (v = (int*)calloc(sizeof(int), 10000)))
	{
		perror("Error at allocating memory.\n");
		getchar();
		exit(1);
	}
	if (NULL == (selection = (int*)calloc(sizeof(int), 10000)))
	{
		perror("Error at allocating memory.\n");
		getchar();
		exit(1);
	}
	if (NULL == (insertion = (int*)calloc(sizeof(int), 10000)))
	{
		perror("Error at allocating memory.\n");
		getchar();
		exit(1);
	}
	for (int j = 0; j < 5; j++)
	{
		for (n = 100; n <=6500; n += 100)
		{

			profiler.countOperation("Bubble_sort_comparissons", n, 0);
			profiler.countOperation("Bubble_sort_assignments", n, 0);
			profiler.countOperation("Selection_sort_assignments", n, 0);
			profiler.countOperation("Selection_sort_comparissons", n, 0);
			profiler.countOperation("Insertion_sort_assignments", n, 0);
			profiler.countOperation("Insertion_sort_comparissons", n, 0);

			FillRandomArray(v, n, 0, 999, false, 0);
			memcpy_s(insertion, n, v, n);
			memcpy_s(selection, n, v, n);

			bubble_sort(v, n);
			selection_sort(selection, n);
			insertionSort(insertion, n);
			if (j == 0)
			{
				profiler.addSeries("Bubble_sort_sum_1", "Bubble_sort_comparissons", "Bubble_sort_assignments");
				profiler.addSeries("Insertion_sort_sum_1", "Insertion_sort_comparissons", "Insertion_sort_assignments");
				profiler.addSeries("Selection_sort_sum_1", "Selection_sort_comparissons", "Selection_sort_assignments");
				profiler.createGroup("Average_case_1", "Bubble_sort_sum_1", "Insertion_sort_sum_1", "Selection_sort_sum_1");
			}
			if (j == 1)
			{
				profiler.addSeries("Bubble_sort_sum_2", "Bubble_sort_comparissons", "Bubble_sort_assignments");
				profiler.addSeries("Insertion_sort_sum_2", "Insertion_sort_comparissons", "Insertion_sort_assignments");
				profiler.addSeries("Selection_sort_sum_2", "Selection_sort_comparissons", "Selection_sort_assignments");
				profiler.createGroup("Average_case_2", "Bubble_sort_sum_2", "Insertion_sort_sum_2", "Selection_sort_sum_2");
			}
			if (j == 2)
			{
				profiler.addSeries("Bubble_sort_sum_3", "Bubble_sort_comparissons", "Bubble_sort_assignments");
				profiler.addSeries("Insertion_sort_sum_3", "Insertion_sort_comparissons", "Insertion_sort_assignments");
				profiler.addSeries("Selection_sort_sum_3", "Selection_sort_comparissons", "Selection_sort_assignments");
				profiler.createGroup("Average_case_3", "Bubble_sort_sum_3", "Insertion_sort_sum_3", "Selection_sort_sum_3");
			}
			if (j == 3)
			{
				profiler.addSeries("Bubble_sort_sum_4", "Bubble_sort_comparissons", "Bubble_sort_assignments");
				profiler.addSeries("Insertion_sort_sum_4", "Insertion_sort_comparissons", "Insertion_sort_assignments");
				profiler.addSeries("Selection_sort_sum_4", "Selection_sort_comparissons", "Selection_sort_assignments");
				profiler.createGroup("Average_case_4", "Bubble_sort_sum_4", "Insertion_sort_sum_4", "Selection_sort_sum_4");
			}
			if (j == 4)
			{
				profiler.addSeries("Bubble_sort_sum_5", "Bubble_sort_comparissons", "Bubble_sort_assignments");
				profiler.addSeries("Insertion_sort_sum_5", "Insertion_sort_comparissons", "Insertion_sort_assignments");
				profiler.addSeries("Selection_sort_sum_5", "Selection_sort_comparissons", "Selection_sort_assignments");
				profiler.createGroup("Average_case_5", "Bubble_sort_sum_5", "Insertion_sort_sum_5", "Selection_sort_sum_5");
			}

		}
		
		profiler.addSeries("Bubble_sort_average_sum", "Bubble_sort_sum_1", "Bubble_sort_sum_2");
		profiler.addSeries("Bubble_sort_average_sum", "Bubble_sort_sum_3", "Bubble_sort_sum_4");
		profiler.addSeries("Bubble_sort_average_sum", "Bubble_sort_sum_5", " ");
		profiler.divideValues("Bubble_sort_average_sum", 5);

		profiler.addSeries("Selection_sort_average_sum", "Selection_sort_sum_1", "Selection_sort_sum_2");
		profiler.addSeries("Selection_sort_average_sum", "Selection_sort_sum_3", "Selection_sort_sum_4");
		profiler.addSeries("Selection_sort_average_sum", "Selection_sort_sum_5", " ");
		profiler.divideValues("Selection_sort_average_sum", 5);

		profiler.addSeries("Insertion_sort_average_sum", "Insertion_sort_sum_1", "Insertion_sort_sum_2");
		profiler.addSeries("Insertion_sort_average_sum", "Insertion_sort_sum_3", "Insertion_sort_sum_4");
		profiler.addSeries("Insertion_sort_average_sum", "Insertion_sort_sum_5", " ");
		profiler.divideValues("Insertion_sort_average_sum", 5);
		

		profiler.createGroup("Average_Case_Assignments", "Bubble_sort_assignments", "Insertion_sort_assignments", "Selection_sort_assignments");
		profiler.createGroup("Average_Case_Comparissons", "Bubble_sort_comparissons", "Insertion_sort_comparissons", "Selection_sort_comparissons");
		profiler.createGroup("Average_Case_Sum", "Bubble_sort_average_sum", "Selection_sort_average_sum", "Insertion_sort_average_sum");
	}


	free(v);
	free(selection);
	free(insertion);
}