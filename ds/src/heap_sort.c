#include <stddef.h>     /* size_t */

#include "heap_sort.h"
/*--------------------------forward declarations------------------------------*/
static BuildHeapIMP(int* arr_, size_t arr_size_);
static BuildSortedArrayFromHeapIMP(int* arr, size_t arr_size_);
/*----------------------------------------------------------------------------*/
void HeapSort(int* arr_, size_t arr_size_)
{
	/*asserts*/
	/*construct a valid heap by calling BuildHeapIMP() */
	/*construct a sorted array by calling BuildSortedArrayFromHeapIMP()*/
}

static BuildHeapIMP(int* arr_, size_t arr_size_)
{
	/*asserts*/
	/*iterate on array*/
		/*heapify up */
}

static BuildSortedArrayFromHeapIMP(int* arr, size_t arr_size_)
{
	/*asserts*/
	/*iterate on array*/
		/*swap root with rightmost leaf*/
		/*decrement heap size by 1*/
		/*heapify down "new root"*/
}
