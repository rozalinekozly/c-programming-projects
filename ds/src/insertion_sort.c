/*------------------------------------------------------------------------------  
submitter: rozaline kozly
reviewer: oshrat      
-------------------------------------------------------------------------------*/
#include <stddef.h>     /*size_t*/
/*----------------------declaration on aux functions---------------------------*/
void Swap(int*, int*);
/*----------------------------------------------------------------------------*/
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
void Swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
