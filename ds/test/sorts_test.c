/*
submitter: rozaline 
------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

#include "sorts.h"
/*----------------------------------------------------------------------------*/
#define ARR_SIZE 					10
#define SIZEOF_ARR(arr)			(sizeof(arr) / sizeof(arr[0]))
/*----------------------------------------------------------------------------*/
static void TestBinarySearchIterative(void);
static void TestBinarySearchRecursive(void);
static void TestMergeSort(void);
/*----------------------------------------------------------------------------*/
static void PrintArray(int* arr, size_t size);
static int IsSorted(int* arr, size_t size);
/*----------------------------------------------------------------------------*/
int main(void)
{
    TestBinarySearchIterative();
    TestBinarySearchRecursive();
    TestMergeSort();
    return(0);
}
/*----------------------------------------------------------------------------*/
static void TestBinarySearchIterative(void)
{
    int sorted_arr[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    size_t size = SIZEOF_ARR(sorted_arr);
    int keys[] = {1, 7, 19, 2, 20};
    int expected[] = {0, 3, 9, -1, -1};
    size_t num_tests = SIZEOF_ARR(keys);
    size_t i = 0;
    int result = 0;
    
    printf("------------ Testing Binary Search Iterative ------------\n");
    
    for (i = 0; i < num_tests; i++)
    {
        result = BinarySearchIterative(sorted_arr, size , keys[i]);
        if (result == expected[i])
        {
            printf("[PASS] key=%d, index=%d\n", keys[i], result);
        }
        else
        {
            printf("[FAIL] key=%d, expected=%d, got=%d\n", keys[i], expected[i], result);
        }
    }
}
/*----------------------------------------------------------------------------*/
static void TestBinarySearchRecursive(void)
{
    int sorted_arr[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    size_t size = SIZEOF_ARR(sorted_arr);
    int keys[] = {1, 7, 19, 2, 20};
    int expected[] = {0, 3, 9, -1, -1};
    size_t num_tests = SIZEOF_ARR(keys);
    size_t i = 0;
    int result = 0;
    
    printf("------------ Testing Binary Search Recursive ------------\n");
    
    for (i = 0; i < num_tests; i++)
    {
        result = BinarySearchRecursive(sorted_arr, size , keys[i]);
        if (result == expected[i])
        {
            printf("[PASS] key=%d, index=%d\n", keys[i], result);
        }
        else
        {
            printf("[FAIL] key=%d, expected=%d, got=%d\n", keys[i], expected[i], result);
        }
    }
}
/*----------------------------------------------------------------------------*/
static void TestMergeSort(void)
{
    int arr1[] = {64, 34, 25, 12, 22, 11, 90};
    int arr2[] = {5, 2, 8, 1, 9};
    int arr3[] = {1};
    int arr4[] = {3, 3, 3, 3};
    int arr5[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    
    int* arrays[5];
    size_t sizes[5];
    /* if u had time add this to each test and print it (to ecentuate dealing with edge 
    case and no need to print actual values)*/
   /* const char* descriptions[] = {"random", "small array", "single element", 
                                  "all equal", "reverse sorted"};*/
    size_t num_tests = 5;
    size_t i = 0;
    
    arrays[0] = arr1;
    arrays[1] = arr2;
    arrays[2] = arr3;
    arrays[3] = arr4;
    arrays[4] = arr5;
    
    sizes[0] = SIZEOF_ARR(arr1);
    sizes[1] = SIZEOF_ARR(arr2);
    sizes[2] = SIZEOF_ARR(arr3);
    sizes[3] = SIZEOF_ARR(arr4);
    sizes[4] = SIZEOF_ARR(arr5);
    
    printf("------------ Testing Merge Sort ------------\n");
    
    for (i = 0; i < num_tests; i++)
    {
        printf("Test %lu: ", (unsigned long)(i + 1);
        PrintArray(arrays[i], sizes[i]);
        MergeSort(arrays[i], sizes[i]);
        printf("Result: ");
        PrintArray(arrays[i], sizes[i]);
        
        if (IsSorted(arrays[i], sizes[i]))
        {
            printf("[PASS]\n");
        }
        else
        {
            printf("[FAIL]\n");
        }
    }
}
/*----------------------------------------------------------------------------*/
static void PrintArray(int* arr, size_t size)
{
    size_t i = 0;
    
    for (i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
/*----------------------------------------------------------------------------*/
static int IsSorted(int* arr, size_t size)
{
    size_t i = 0;
    
    if (size <= 1)
    {
        return 1;
    }
    
    for (i = 0; i < size - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            return 0;
        }
    }
    
    return 1;
}
/*----------------------------------------------------------------------------*/
