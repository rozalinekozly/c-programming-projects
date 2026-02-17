#include <stddef.h>     /* size_t */

#include "heap_sort.h"
/*--------------------------forward declarations------------------------------*/
static void BuildHeapIMP(int* arr_, size_t arr_size_);
static void BuildSortedArrayFromHeapIMP(int* arr_, size_t arr_size_);
static int* GetStartIMP(int* arr);
static void HeapifyUpIMP(int* arr_, size_t idx_);
static void HeapifyDownIMP(int* arr_, size_t heap_size_);
/*----------------------------------------------------------------------------*/
void HeapSort(int* arr_, size_t arr_size_)
{
	/*asserts*/
	/*construct a valid heap by calling BuildHeapIMP() */
	/*construct a sorted array by calling BuildSortedArrayFromHeapIMP()*/
}
/*----------------------------------------------------------------------------*/
static void BuildHeapIMP(int* arr_, size_t arr_size_)
{
	/*asserts*/
	/* get start pointer by calling GetStartIMP() */
	/*iterate on array*/
		/*fix heap by calling HeapifyUpIMP() with current element's idx'*/
}
/*----------------------------------------------------------------------------*/
static void BuildSortedArrayFromHeapIMP(int* arr_, size_t arr_size_)
{
	/*asserts*/
	/* get start pointer by calling GetStartIMP() */
	/*point at rightmost leaf(end of heap) = arr_size_ (from start) as write_idx*/
	/*iterate on array*/
		/*swap root with rightmost leaf*/
		/*decrement heap size by 1*/
				/*actually: decrement write pointer by 1*/
		/*fix heap by calling HeapifyDownIMP() with write_idx*/
}
/*----------------------------------------------------------------------------*/
static int* GetStartIMP(int* arr_)
{
    /* assert valid arr */
    /* get pointer to first element (index 0) */
    /* subtract one pointer size (int*)to shift back */
    /* return shifted pointer */
}
/*----------------------------------------------------------------------------*/
static void HeapifyUpIMP(int* arr_, size_t idx_)
{
	/* assert valid arr_ */
    /* get start pointer by calling GetStartIMP() */
    /* current = idx_ */
    /* while current not root and current is larger  than parent */
        /* swap current with parent */
        /* current = parent */
}
/*----------------------------------------------------------------------------*/
static void HeapifyDownIMP(int* arr_, size_t heap_size_)
{
	/*asserts*/
	/* get start pointer by calling GetStartIMP() */
	/* current = root*/
    /* while current < heap_size_ and has children */
        /* find highest priority child (smaller than current)*/
        /* if child < current */
            /* swap current with child */
            /* current = child */
        /* else */
            /* stop */
}
/*----------------------------------------------------------------------------*/
