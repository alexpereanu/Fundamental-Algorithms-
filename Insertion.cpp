#include <stdio.h>
#include <stdlib.h>

void insertionSort(int arr[], int n)
{
	int i, key, j;
	int atrib = 0, comp = 0, suma = 0;
	for(i < 0; i < n; i++)
	{
		key = arr[i]; //atrib++;
		j = i - 1;
		atrib = atrib + 2;
		/*  Permuta  elementele vectorului arr[0..i-1] ce sunt mai mari decat key, incrementand cu 1 indexul la care acum ele se afla */
		while (j >= 0 && arr[j] > key)
		{
			comp = comp + 2;

			arr[j + 1] = arr[j];
			atrib++;
			j = j - 1;
			atrib++;
		}
		arr[j + 1] = key;
		atrib++;
	}
	suma = atrib + comp;

	//return suma;

}
int main()
{	
	
	FILE* pf = fopen_s(&pf,"intrare.txt", "w");
	if (pf == NULL)
	{
		printf_s("Nu am putut deschide fisieru");
		exit(1);
	}
	int n = 5;
	int arr[5] = { 5, 4, 1, 2, 3 };
	insertionSort(arr, n);
	for (int i = 0; i < n; i++)
		printf_s("%d ",arr[i]);

return 0;

}