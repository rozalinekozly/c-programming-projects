/*
submitter: rozaline 
reviewer: shalev
------------------------------------------------------------------------------*/
#include <assert.h>		/*assert()*/
#include <stdlib.h>		/*malloc(), free()*/
#include <sys/types.h>	/*ssize_t*/
/*----------------------------------------------------------------------------*/
#include "sorts.h"		/*API*/
/*----------------------------------------------------------------------------*/
#define NOT_FOUND		-1
/*----------------------------------------------------------------------------*/
static size_t BinarySearchRecursiveWrapped(int arr[], ssize_t left, ssize_t right , int key);

static void MergeSortWrapper(int* arr, int* temp, size_t left, size_t right);
static void Merge(int* arr, int* temp, size_t left, size_t mid, size_t right);

static void QuickSortWrapper(void* base, ssize_t left, ssize_t right, size_t element_size,
                              int (*compar)(const void*, const void*));
static ssize_t Partition(void* base, ssize_t left, ssize_t right, size_t element_size,
                        int (*compar)(const void*, const void*));
static void Swap(void* a, void* b, size_t size);
/*----------------------------------------------------------------------------*/
ssize_t BinarySearchIterative(int arr[], size_t arr_size, int key)
{
	ssize_t left = 0;
	ssize_t right = arr_size - 1;
    ssize_t mid = 0;
    
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
            right = mid - 1;
        }
    }
    
    return (NOT_FOUND);
}
/*----------------------------------------------------------------------------*/
ssize_t BinarySearchRecursive(int* arr, size_t arr_size, int key)
{
	ssize_t left = 0;
	ssize_t right = arr_size - 1;
	
	 if (0 == arr_size)
    {
        return NOT_FOUND;
    }
	return BinarySearchRecursiveWrapped(arr, left, right, key);
}
/*----------------------------------------------------------------------------*/
static size_t BinarySearchRecursiveWrapped(int arr[], ssize_t left, ssize_t right , int key)
{
	ssize_t mid = 0;
	
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
        return -1; /*change this to failed */
    }
    
    MergeSortWrapper(arr_to_sort, temp, 0, num_elements - 1);
    
    free(temp);
    
    return 0; /* this to success*/
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
    /*return status*/
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
/*----------------------------------------------------------------------------*/
void QuickSort(void* base, size_t num_elements, size_t element_size,
               int (*compar)(const void*, const void*))
{
    assert(base != NULL);
    assert(compar != NULL);
    
    if (num_elements <= 1)
    {
        return;
    }
    
    QuickSortWrapper(base, 0, (ssize_t)(num_elements - 1), element_size, compar);
}
/*----------------------------------------------------------------------------*/
static void QuickSortWrapper(void* base, ssize_t left, ssize_t right, size_t element_size,
                              int (*compar)(const void*, const void*))
{
    ssize_t pivot_index = 0;
    
    if (left >= right)
    {
        return;
    }
    
    pivot_index = Partition(base, left, right, element_size, compar);
    
    QuickSortWrapper(base, left, pivot_index - 1, element_size, compar);
    QuickSortWrapper(base, pivot_index + 1, right, element_size, compar);
}
/*----------------------------------------------------------------------------*/
static ssize_t Partition(void* base, ssize_t left, ssize_t right, size_t element_size,
                        int (*compar)(const void*, const void*))
{
    char* arr = (char*)base;
    void* pivot = arr + right * element_size;
    ssize_t i = left;
    ssize_t j = left;
    
    for (j = left; j < right; j++)
    {
        if (compar(arr + j * element_size, pivot) < 0)
        {
            Swap(arr + i * element_size, arr + j * element_size, element_size);
            i++;
        }
    }
    
    Swap(arr + i * element_size, arr + right * element_size, element_size);
    
    return i;
}
/*----------------------------------------------------------------------------*/
static void Swap(void* a, void* b, size_t size)
{
    char temp;
    char* p1 = (char*)a;
    char* p2 = (char*)b;
    size_t i = 0;
    
    for (i = 0; i < size; i++)
    {
        temp = p1[i];
        p1[i] = p2[i];
        p2[i] = temp;
    }
}
