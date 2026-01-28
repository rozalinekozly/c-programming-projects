/*
submitter: rozaline 
------------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <assert.h>
/*----------------------------------------------------------------------------*/
#include "sorts.h"		/*API*/
/*----------------------------------------------------------------------------*/
#define NOT_FOUND		-1
/*----------------------------------------------------------------------------*/
int BinarySearchIterative(int arr[], size_t arr_size, int key)
{
	int left = 0;
	int right = arr_size - 1;
    int mid = 0;
    
    assert(arr != NULL);
    
    while (left <= right)
    {
        mid = left + (right - left) / 2;
        
        if (arr[mid] == key)
        {
            return (mid);
        }
        
        if (arr[mid] < key)
        {
            left = mid + 1;
        }
        else
        {
            if (mid == 0)
            {
                break;
            }
            right = mid - 1;
        }
    }
    
    return (NOT_FOUND);
}
/*----------------------------------------------------------------------------*/

