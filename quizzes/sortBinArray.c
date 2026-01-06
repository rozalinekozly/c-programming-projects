/*-----------------------------------------------------------------------------
	quiz: sort array of 0s and 1s
	date: 04-01-2025
------------------------------------------------------------------------------*/
#include <stdio.h>		/* printf()*/
#include <stddef.h>		/* size_t*/
/*----------------------------------------------------------------------------*/
#define ARR_SIZE(arr)	(sizeof(arr)/sizeof(arr[0]))
/*---------------------auxillary functions -----------------------------------*/
void Swap(size_t *a, size_t *b)
{
    size_t tmp = *a;
    *a = *b;
    *b = tmp;
}

size_t FindNxtZero(size_t *arr, size_t arr_size, size_t start_idx)
{
    size_t nxt_zero = start_idx + 1;

    while (nxt_zero < arr_size && arr[nxt_zero] != 0)
    {
        ++nxt_zero;
    }

    return (nxt_zero);
}

size_t FindNxtOne(size_t *arr, size_t arr_size, size_t start_idx)
{
    size_t nxt_one = start_idx + 1;

    while (nxt_one < arr_size && arr[nxt_one] != 1)
    {
        ++nxt_one;
    }

    return (nxt_one);
}

void SortBinArray(size_t *arr, size_t arr_size)
{
    size_t curr_zero = FindNxtZero(arr, arr_size, (size_t)-1);
    size_t curr_one  = FindNxtOne(arr, arr_size, (size_t)-1);

    while (curr_zero < arr_size && curr_one < arr_size)
    {
        if (curr_zero > curr_one)
        {
            Swap(&arr[curr_zero], &arr[curr_one]);

            curr_one = FindNxtOne(arr, arr_size, curr_one);
            curr_zero = FindNxtZero(arr, arr_size, curr_zero);
        }
        else
        {
            curr_zero = FindNxtZero(arr, arr_size, curr_zero);
        }
    }
}

void PrintArray(size_t* arr, size_t size, char* label)
{
    size_t i = 0;
    printf("%s: ", label);
    for (i = 0; i < size; i++)
    {
        printf("%lu ", arr[i]);
    }
    printf("\n");
}

int main()
{
    size_t arr1[] = {1, 1, 0, 0};
    size_t n1 = ARR_SIZE(arr1);
    size_t arr2[] = {0, 0, 1, 1};
    size_t n2 = ARR_SIZE(arr2);
    size_t arr3[] = {1, 0, 1, 0, 1, 0};
    size_t n3 = ARR_SIZE(arr3);
    
    printf("--- Test Case 1 ---\n");
    PrintArray(arr1, n1, "Before");
    SortBinArray(arr1, n1);
    PrintArray(arr1, n1, "After ");
    printf("Expected: 0 0 1 1\n\n");

    printf("--- Test Case 2 ---\n");
    PrintArray(arr2, n2, "Before");
    SortBinArray(arr2, n2);
    PrintArray(arr2, n2, "After ");
    printf("Expected: 0 0 1 1\n\n");

    printf("--- Test Case 3 ---\n");
    PrintArray(arr3, n3, "Before");
    SortBinArray(arr3, n3);
    PrintArray(arr3, n3, "After ");
    printf("Expected: 0 0 0 1 1 1\n");

    return (0);
}
