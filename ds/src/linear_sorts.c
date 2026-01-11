#include <stdio.h>	/*printf()*/
#include <stdlib.h>	/*rand(), qsort*/
#include <time.h>	/*clock(), clock_t*/
/*----------------------------------------------------------------------------*/
#define ARR_SIZE	5000
#define MAX_INT		100
/*-----------------------------AUX FUNCTIONS---------------------------------------*/
/*fucntions that generates integers in a given range */
int GenerateRandomIntegers(size_t max_int);
void FillArrayWithRandomIntegers(int* arr, size_t arr_size, size_t max_int);
void PrintArray(int* arr, size_t arr_size);
void TestCountingSort();
void CountingSort(int* arr, size_t arr_size);
/*----------------------------------------------------------------------------*/
int main()
{
	TestCountingSort();
	return 0;
}
/*----------------------------------------------------------------------------*/
void TestCountingSort()
{
	int counting_sort_arr[ARR_SIZE] = {0};
	size_t arr_size = ARR_SIZE;
	
	FillArrayWithRandomIntegers(counting_sort_arr, arr_size, MAX_INT);
	CountingSort(counting_sort_arr, arr_size);
	/*PrintArray(counting_sort_arr, arr_size);*/
}
/*----------------------------------------------------------------------------*/
void CountingSort(int* arr, size_t arr_size)
{
	size_t hist[MAX_INT + 1] = {0};
	size_t i = 0;
	size_t j = 0;
	
	for(i = 0 ; i < arr_size ; i++)
	{
		++hist[arr[i]];
	}
	i = 0;
	
	while(j < arr_size)
	{
		while(hist[i] > 0)
		{
			arr[j] = i;
			--hist[i];
			++j;
		}
		i++;
	}
}

/*----------------------------------------------------------------------------*/
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


