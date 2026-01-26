/*------------------------------------------------------------------------------  
submitter: rozaline kozly
reviewer: oshrat      
-------------------------------------------------------------------------------*/
#include <stddef.h>     /*size_t*/
/*----------------------declaration on aux functions---------------------------*/
int* MinInArr(int* arr, size_t arr_size);
void Swap(int*, int*);
/*----------------------------------------------------------------------------*/
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
