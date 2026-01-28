#ifndef SORTS_H
#define SORTS_H

#include <stddef.h>		/*size_t*/

int BinarySearchIterative(int arr[], size_t arr_size, int key);

int BinarySearchRecursive(int* arr, size_t arr_size , int key);

int MergeSort(int* arr_to_sort, size_t num_elements);

void QuickSort(void* base, size_t num_elements, size_t element_size,
               int (*compar)(const void*, const void*));

#endif
