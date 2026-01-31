#ifndef SORTS_H
#define SORTS_H

#include <stddef.h>		/*size_t*/
#include <sys/types.h>	/*ssize_t*/
ssize_t BinarySearchIterative(int arr[], size_t arr_size, int key);

ssize_t BinarySearchRecursive(int* arr, size_t arr_size , int key);

int MergeSort(int* arr_to_sort, size_t num_elements);

void QuickSort(void* base, size_t num_elements, size_t element_size,
               int (*compar)(const void*, const void*));

#endif
