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

typedef int (*compar)(const void *, const void*);

/*----------------------------------------------------------------------------*/
/* fucntion that prints the contents of an array */
void PrintArray(int*, size_t);
/*fucntions that generates integers in a given range */
int GenerateRandomIntegers(size_t max_int);
void FillArrayWithRandomIntegers(int* arr, size_t arr_size, size_t max_int);
int CompareFunction(const void* a, const void* b);
/*----------------------declaration on aux functions---------------------------*/
void TestBubbleSort();
void Swap(int*, int*);
/*-----------------------------------------------------------------------------*/
int main()
{
	TestBubbleSort();
	return 0;
}
/*-----------------------------------------------------------------------------*/
void BubbleSort(int* arr, size_t arr_size)
{
	size_t curr_iter = 0;
	size_t nxt_iter = 0;
	
	for(curr_iter = 0 ; curr_iter < arr_size ; ++curr_iter)
	{

		for(nxt_iter = 0 ; nxt_iter < arr_size ; ++nxt_iter)
		{
			if(arr[nxt_iter] < arr[curr_iter])
			{
				Swap(&arr[nxt_iter], &arr[curr_iter]);
			}
		}

	}
}
/*----------------------------------------------------------------------------*/
void Swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int CompareFunction(const void* a, const void* b)
{
	int element_a = *(int*)a;
	int element_b = *(int*)b;
	
	if(element_a > element_b)
	{
		return element_a;
	}
	return element_b;
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

void TestBubbleSort()
{
	int bubble_sort_arr[ARR_SIZE] = {0};
	int qsort_arr[ARR_SIZE] = {0};
	size_t arr_size = ARR_SIZE;
	
	clock_t bubble_sort_start = 0;
	clock_t bubble_sort_stop = 0;
	double bubble_sort_elapsed = 0;
	
	clock_t qsort_start = 0;
	clock_t qsort_stop = 0;
	double qsort_elapsed = 0;
	
	FillArrayWithRandomIntegers(bubble_sort_arr, arr_size, MAX_INT);
	FillArrayWithRandomIntegers(qsort_arr, arr_size, MAX_INT);
	
	bubble_sort_start = clock();
	BubbleSort(bubble_sort_arr, arr_size);
	bubble_sort_stop = clock();
	bubble_sort_elapsed = (double)(bubble_sort_stop - bubble_sort_start)/ CLOCKS_PER_SEC;
	
	qsort_start = clock();
	qsort(qsort_arr, arr_size, sizeof(int), CompareFunction);
	qsort_stop = clock();
	qsort_elapsed = (double)(qsort_stop - qsort_start)/ CLOCKS_PER_SEC;
	
	/*PrintArray(arr, arr_size);*/
	printf("clock time of qsort is %f (seconds)\n", qsort_elapsed);
	printf("clock time of bubble sort is %f (seconds)\n", bubble_sort_elapsed);
	
}
