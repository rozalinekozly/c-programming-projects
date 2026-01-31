#include <stdio.h>
#include <stdlib.h>
#include "sorts.h"

#define ARR_SIZE 10
#define TEST_ARR_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

static void TestBinarySearchIterative(void);
static void TestBinarySearchRecursive(void);
static void TestMergeSort(void);
static void TestQuickSort(void);
static int CompareInts(const void* a, const void* b);
static void PrintArray(int* arr, size_t size);
static int IsSorted(int* arr, size_t size);

int main(void)
{
    TestBinarySearchIterative();
    TestBinarySearchRecursive();
    TestMergeSort();
    TestQuickSort();
    
    return 0;
}

static void TestBinarySearchIterative(void)
{
    int sorted_arr[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    size_t size = TEST_ARR_SIZE(sorted_arr);
    int keys[] = {1, 7, 19, 2, 20};
    int expected[] = {0, 3, 9, -1, -1};
    size_t num_tests = TEST_ARR_SIZE(keys);
    size_t i = 0;
    int result = 0;
    
    printf("------------ Testing Binary Search Iterative ------------\n");
    
    for (i = 0; i < num_tests; i++)
    {
        result = BinarySearchIterative(sorted_arr, 0, size - 1, keys[i]);
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

static void TestBinarySearchRecursive(void)
{
    int sorted_arr[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    size_t size = TEST_ARR_SIZE(sorted_arr);
    int keys[] = {1, 7, 19, 2, 20};
    int expected[] = {0, 3, 9, -1, -1};
    size_t num_tests = TEST_ARR_SIZE(keys);
    size_t i = 0;
    int result = 0;
    
    printf("------------ Testing Binary Search Recursive ------------\n");
    
    for (i = 0; i < num_tests; i++)
    {
        result = BinarySearchRecursive(sorted_arr, 0, size - 1, keys[i]);
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

static void TestMergeSort(void)
{
    int arr1[] = {64, 34, 25, 12, 22, 11, 90};
    int arr2[] = {5, 2, 8, 1, 9};
    int arr3[] = {1};
    int arr4[] = {3, 3, 3, 3};
    size_t size1 = TEST_ARR_SIZE(arr1);
    size_t size2 = TEST_ARR_SIZE(arr2);
    size_t size3 = TEST_ARR_SIZE(arr3);
    size_t size4 = TEST_ARR_SIZE(arr4);
    
    printf("------------ Testing Merge Sort ------------\n");
    
    printf("Before: ");
    PrintArray(arr1, size1);
    MergeSort(arr1, size1);
    printf("After:  ");
    PrintArray(arr1, size1);
    if (IsSorted(arr1, size1))
    {
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }
    
    printf("Before: ");
    PrintArray(arr2, size2);
    MergeSort(arr2, size2);
    printf("After:  ");
    PrintArray(arr2, size2);
    if (IsSorted(arr2, size2))
    {
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }
    
    MergeSort(arr3, size3);
    if (IsSorted(arr3, size3))
    {
        printf("[PASS] single element\n");
    }
    
    MergeSort(arr4, size4);
    if (IsSorted(arr4, size4))
    {
        printf("[PASS] all equal\n");
    }
}

static void TestQuickSort(void)
{
    int arr1[] = {64, 34, 25, 12, 22, 11, 90};
    int arr2[] = {5, 2, 8, 1, 9};
    int arr3[] = {1};
    int arr4[] = {3, 3, 3, 3};
    size_t size1 = TEST_ARR_SIZE(arr1);
    size_t size2 = TEST_ARR_SIZE(arr2);
    size_t size3 = TEST_ARR_SIZE(arr3);
    size_t size4 = TEST_ARR_SIZE(arr4);
    
    printf("------------ Testing Quick Sort ------------\n");
    
    printf("Before: ");
    PrintArray(arr1, size1);
    QuickSort(arr1, size1, sizeof(int), CompareInts);
    printf("After:  ");
    PrintArray(arr1, size1);
    if (IsSorted(arr1, size1))
    {
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }
    
    printf("Before: ");
    PrintArray(arr2, size2);
    QuickSort(arr2, size2, sizeof(int), CompareInts);
    printf("After:  ");
    PrintArray(arr2, size2);
    if (IsSorted(arr2, size2))
    {
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }
    
    QuickSort(arr3, size3, sizeof(int), CompareInts);
    if (IsSorted(arr3, size3))
    {
        printf("[PASS] single element\n");
    }
    
    QuickSort(arr4, size4, sizeof(int), CompareInts);
    if (IsSorted(arr4, size4))
    {
        printf("[PASS] all equal\n");
    }
}

static int CompareInts(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}

static void PrintArray(int* arr, size_t size)
{
    size_t i = 0;
    
    for (i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

static int IsSorted(int* arr, size_t size)
{
    size_t i = 0;
    
    for (i = 0; i < size - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            return 0;
        }
    }
    
    return 1;
}
