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
void InsertionSort(int* arr, size_t arr_size);
void TestInsertionSort();
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
	TestInsertionSort();
	return 0;
}
void InsertionSort(int* arr, size_t arr_size)
{
	size_t sorted_part = 0;
	int curr = arr[sorted_part];
	int i = 0;
	
	for(sorted_part = 0 ; sorted_part < arr_size ; sorted_part++)
	{
		curr = arr[sorted_part];
		for(i = sorted_part - 1 ; i > 0 ; i--)
		{
			if(curr > arr[i])
			{
				Swap(&arr[i], &arr[i + 1]);
			}
			else
			{
				arr[i + 1] = curr;
				break;
			}
			
		}
	
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
void TestInsertionSort()
{
	int insertion_sort_arr[ARR_SIZE] = {0};
	size_t arr_size = ARR_SIZE;
	
	clock_t insertion_sort_start = 0;
	clock_t insertion_sort_stop = 0;
	double insertion_sort_elapsed = 0;
	
	FillArrayWithRandomIntegers(insertion_sort_arr, arr_size, MAX_INT);
	insertion_sort_start = clock();
	InsertionSort(insertion_sort_arr, arr_size);
	insertion_sort_stop = clock();
	insertion_sort_elapsed = (double)(insertion_sort_stop - insertion_sort_start)/ CLOCKS_PER_SEC;
	
	/*PrintArray(arr, arr_size);*/
	printf("clock time of insertion sort is %f (seconds)\n", insertion_sort_elapsed);

}
