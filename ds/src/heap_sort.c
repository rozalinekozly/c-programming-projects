#include <stddef.h>     /* size_t */

#include "heap_sort.h"
/*--------------------------forward declarations------------------------------*/
static BuildHeapIMP(int* arr_, size_t arr_size_);
static BuildSortedArrayFromHeapIMP(int* arr, size_t arr_size_);
static int* GetStartIMP(int* arr);
/*----------------------------------------------------------------------------*/
void HeapSort(int* arr_, size_t arr_size_)
{
	/*asserts*/
	/*construct a valid heap by calling BuildHeapIMP() */
	/*construct a sorted array by calling BuildSortedArrayFromHeapIMP()*/
}
/*----------------------------------------------------------------------------*/
static BuildHeapIMP(int* arr_, size_t arr_size_)
{
	/*asserts*/
	/* get start pointer */
	/*iterate on array*/
		/*heapify up */
}
/*----------------------------------------------------------------------------*/
static BuildSortedArrayFromHeapIMP(int* arr, size_t arr_size_)
{
	/*asserts*/
	/* get start pointer */
	/*iterate on array*/
		/*swap root with rightmost leaf*/
		/*decrement heap size by 1*/
		/*heapify down "new root"*/
}
/*----------------------------------------------------------------------------*/
static int* GetStartIMP(int* arr)
{
    /* assert valid arr */
    /* get pointer to first element (index 0) */
    /* subtract one pointer size to shift back */
    /* return shifted pointer */
}
