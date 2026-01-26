#include <stdio.h>	/*printf()*/
#include <stdlib.h>	/*rand(), qsort*/
#include <time.h>	/*clock(), clock_t*/
/*----------------------------------------------------------------------------*/
#define ARR_SIZE	5000
#define MAX_INT		5000

typedef int (*compar)(const void *, const void*);

/*---------------------SORTING FUNCTIONS--------------------------------------*/
void BubbleSort(int* arr, size_t arr_size);
void SelectionSort(int* arr, size_t arr_size);
void InsertionSort(int* arr, size_t arr_size);
/*----------------------------------------------------------------------------*/
/* fucntion that prints the contents of an array */
void PrintArray(int*, size_t);
/* swap function*/
void Swap(int*, int*);
/*fucntions that generates integers in a given range */
int GenerateRandomIntegers(size_t max_int);
void FillArrayWithRandomIntegers(int* arr, size_t arr_size, size_t max_int);
int CompareFunction(const void* a, const void* b);
int* MinInArr(int* arr, size_t arr_size);
/*---------------------TESTING FUNCTIONS--------------------------------------*/
void TestBubbleSort();
void TestSelectionSort();
void TestInserionTest();
/*----------------------------------------------------------------------------*/
int main()
{
	TestBubbleSort();
	TestSelectionSort();
	TestInserionTest();
	return 0;
}
/*----------------------------------------------------------------------------*/
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

void TestInserionTest()
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
/*---------------------AUX FUNCTIONS-------------------------------------------*/
void Swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

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
