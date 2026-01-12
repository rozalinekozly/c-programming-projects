#include <stdio.h>	/*printf()*/
#include <stdlib.h>	/*rand(), qsort*/
#include <time.h>	/*clock(), clock_t*/
/*----------------------------------------------------------------------------*/
#define ARR_SIZE	5000
#define MAX_INT		100
/*-------------------------SORTING FUNCTIONS-----------------------------------*/
void CountingSort(int* arr, size_t arr_size);
void RadixSort(int* arr, size_t arr_Size);
/*-------------------------TESTING FUNCTIONS-----------------------------------*/
void TestCountingSort();
void TestingRadixSort();
/*-----------------------------AUX FUNCTIONS-----------------------------------*/
/*fucntions that generates integers in a given range */
int GenerateRandomIntegers(size_t max_int);
void FillArrayWithRandomIntegers(int* arr, size_t arr_size, size_t max_int);
void PrintArray(int* arr, size_t arr_size);
int getMax(int arr[], size_t n);
void CountingSortForRadix(int arr[], int n, int exp);

/*----------------------------------------------------------------------------*/
int main()
{
	TestCountingSort();
	TestingRadixSort();
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

void TestingRadixSort()
{
    	int radix_sort_arr[ARR_SIZE] = {0};
	size_t arr_size = ARR_SIZE;
	
	FillArrayWithRandomIntegers(radix_sort_arr, arr_size, MAX_INT);
	RadixSort(radix_sort_arr, arr_size);
	PrintArray(radix_sort_arr, arr_size);

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

void RadixSort(int* arr, size_t n)
{
    /* Find the maximum number to know number of digits*/
    int m = getMax(arr, n);
    int exp = 0;
    

    /* Do counting sort for every digit. Note that instead
     of passing digit number, exp is passed. exp is 10^i
     where i is current digit number*/
    for (exp = 1; m / exp > 0; exp *= 10)
        CountingSortForRadix(arr, n, exp);
}

/*----------------------------------------------------------------------------*/
/*
    a helper function that takes an array, it's size and the exp (digit to sort 
    according to it) and sorts the array based on that digit
*/

int getMax(int arr[], size_t n)
{
    int mx = arr[0];
    size_t i = 0;
    for (i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

/* A function to do counting sort of arr[] according to
 the digit represented by exp.*/
void CountingSortForRadix(int arr[], int n, int exp)
{
    /* output array*/
    int* output = NULL;
    int i = 0, count[10] = { 0 };

    output = (int*)malloc(n*sizeof(int));
    if(NULL == output)
    {
        return;
    }
    /* Store count of occurrences in count[]*/
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    /* Change count[i] so that count[i] now contains actual
     position of this digit in output[]*/
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    /* Build the output array*/
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    /* Copy the output array to arr[], so that arr[] now
     contains sorted numbers according to current digit*/
    for (i = 0; i < n; i++)
        arr[i] = output[i];
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


