/*
submitter: rozaline 
------------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
/*----------------------------------------------------------------------------*/
#include "sorts.h"		/*API*/
/*----------------------------------------------------------------------------*/
#define NOT_FOUND		-1
/*----------------------------------------------------------------------------*/
static int BinarySearchRecursiveWrapped(int arr[], int left, int right , int key);
static void MergeSortWrapper(int* arr, int* temp, size_t left, size_t right);
static void Merge(int* arr, int* temp, size_t left, size_t mid, size_t right);
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
/*----------------------------------------------------------------------------*/
int MergeSort(int* arr_to_sort, size_t num_elements)
{
    int* temp = NULL;
    
    assert(arr_to_sort != NULL);
    
    if (num_elements <= 1)
    {
        return 0;
    }
    
    temp = (int*)malloc(num_elements * sizeof(int));
    if (NULL == temp)
    {
        return -1;
    }
    
    MergeSortWrapper(arr_to_sort, temp, 0, num_elements - 1);
    
    free(temp);
    
    return 0;
}
/*----------------------------------------------------------------------------*/
static void MergeSortWrapper(int* arr, int* temp, size_t left, size_t right)
{
    size_t mid = 0;
    
    if (left >= right)
    {
        return;
    }
    
    mid = left + (right - left) / 2;
    
    MergeSortWrapper(arr, temp, left, mid);
    MergeSortWrapper(arr, temp, mid + 1, right);
    Merge(arr, temp, left, mid, right);
}
/*----------------------------------------------------------------------------*/
static void Merge(int* arr, int* temp, size_t left, size_t mid, size_t right)
{
    size_t i = left;
    size_t j = mid + 1;
    size_t k = left;
    
    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
        {
            temp[k++] = arr[i++];
        }
        else
        {
            temp[k++] = arr[j++];
        }
    }
    
    while (i <= mid)
    {
        temp[k++] = arr[i++];
    }
    
    while (j <= right)
    {
        temp[k++] = arr[j++];
    }
    
    for (i = left; i <= right; i++)
    {
        arr[i] = temp[i];
    }
}

