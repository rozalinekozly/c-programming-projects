/*------------------------------------------------------------------------------  
submitter: rozaline kozly
reviewer: oshrat      
-------------------------------------------------------------------------------*/
#include <stddef.h>     /*size_t*/
/* for testing */
#include <stdio.h>	/*printf()*/
#include <stdlib.h>	/*rand(), qsort*/
#include <time.h>	/*clock(), clock_t*/

/*----------------------------------------------------------------------------*/
#define ARR_SIZE	5000
#define MAX_INT		5000

void SelectionSort(int* arr, size_t arr_size);
void TestSelectionSort();
/*----------------------declaration on aux functions---------------------------*/
int* MinInArr(int* arr, size_t arr_size);
void Swap(int*, int*);
/* fucntion that prints the contents of an array */
void PrintArray(int*, size_t);
/*fucntions that generates integers in a given range */
int GenerateRandomIntegers(size_t max_int);
void FillArrayWithRandomIntegers(int* arr, size_t arr_size, size_t max_int);
/*----------------------------------------------------------------------------*/
int main()
{
	TestSelectionSort();
	return 0;
}
void SelectionSort(int* arr, size_t arr_size)
{
	int* placement_to_insert = arr + (arr_size - 1);
	int* curr_min = arr;
	
	while(placement_to_insert >= arr)
	{
		curr_min = MinInArr(arr, placement_to_insert - arr + 1);
		Swap(placement_to_insert, curr_min);
		--placement_to_insert;
	}
}
/*----------------------------------------------------------------------------*/
int* MinInArr(int* arr, size_t arr_size)
{
	size_t i = 0;
	int* min = arr;
	for(i = 0 ; i < arr_size ; i++)
	{
		if(arr[i] < *min)
		{
			min = &arr[i];
		}
	}
	return min;
}
/*----------------------------------------------------------------------------*/
void Swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

/*---------------------AUX FUNCTIONS-------------------------------------------*/
void PrintArray(int* arr, size_t arr_size)
{
	size_t i = 0;
	size_t new_line = 10;
	
	for(i = 0 ; i < arr_size ; i++)
	{
		if(i%new_line == 0)
		{
			printf("\n");
		}
		printf("%d, ", arr[i]);
	}
	printf("\n");
}


int GenerateRandomIntegers(size_t max_int)
{
	return (rand()%max_int);

}

void FillArrayWithRandomIntegers(int* arr, size_t arr_size, size_t max_int)
{
	size_t i = 0;
	
	for(i = 0 ; i < arr_size; i++)
	{
		arr[i] = GenerateRandomIntegers(max_int);
	}
}

void TestSelectionSort()
{
	int selection_sort_arr[ARR_SIZE] = {0};
	
	size_t arr_size = ARR_SIZE;
	
	clock_t selection_sort_start = 0;
	clock_t selection_sort_stop = 0;
	double selection_sort_elapsed = 0;
	
	FillArrayWithRandomIntegers(selection_sort_arr, arr_size, MAX_INT);
	selection_sort_start = clock();
	SelectionSort(selection_sort_arr, arr_size);
	selection_sort_stop = clock();
	selection_sort_elapsed = (double)(selection_sort_stop - selection_sort_start)/ CLOCKS_PER_SEC;
	
	/*PrintArray(arr, arr_size);*/
	printf("clock time of selection sort is %f (seconds)\n", selection_sort_elapsed);
}
