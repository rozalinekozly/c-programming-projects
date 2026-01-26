/*------------------------------------------------------------------------------  
submitter: rozaline kozly
reviewer: oshrat      
-------------------------------------------------------------------------------*/
#include <stddef.h>     /*size_t*/
/*----------------------declaration on aux functions---------------------------*/
void Swap(int*, int*);
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
/*----------------------------------------------------------------------------*/
void Swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
