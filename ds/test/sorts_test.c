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
/*----------------------------------------------------------------------------*/
int main(void)
{
    TestBinarySearchIterative();
    TestBinarySearchRecursive();
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
