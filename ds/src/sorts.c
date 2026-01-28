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
static int BinarySearchRecursiveWrapped(int arr[], int left, int right , int key);
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
int BinarySearchRecursive(int* arr, size_t arr_size, int key)
{
	int left = 0;
	int right = arr_size - 1;
	
	 if (arr_size == 0)
    {
        return NOT_FOUND;
    }
	return BinarySearchRecursiveWrapped(arr, left, right, key);
}
static int BinarySearchRecursiveWrapped(int arr[], int left, int right , int key)
{
	int mid = 0;
	
	if(left > right)
	{
		return NOT_FOUND;
	}
	mid = (right + left) / 2;
	
	if(key == arr[mid])
	{
		return mid;
	}
	if(key > arr[mid])
	{
		return BinarySearchRecursiveWrapped(arr, mid + 1, right, key);  
	}
	else
	{
		return BinarySearchRecursiveWrapped(arr, left, mid - 1, key);  
	}
}

