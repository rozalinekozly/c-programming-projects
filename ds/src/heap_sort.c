#include <stddef.h>		/* size_t */

#include "heap_sort.h"	/*API*/
/*--------------------------forward declarations------------------------------*/
static void BuildHeapIMP(int* arr_, size_t arr_size_);
static void BuildSortedArrayFromHeapIMP(int* arr_, size_t arr_size_);
static int* GetStartIMP(int* arr);
static void HeapifyUpIMP(int* arr_, size_t idx_);
static void HeapifyDownIMP(int* arr_, size_t heap_size_);
static void SwapIMP(int* arr_, size_t idx1_, size_t idx2_);
static size_t GetParentIMP(size_t idx_);
static size_t RChildIMP(size_t idx_);
static size_t LChildIMP(size_t idx_);
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
		/*call SwapIMP on root with rightmost write_idx*/
		/*decrement heap size by 1*/
				/*actually: decrement write pointer by 1*/
		/*fix heap by calling HeapifyDownIMP() with write_idx as heap size*/
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
    /* while current not root and current > than parent call GetParentIMP() to get parent */
        /* call SwapIMP on current with parent */
        /* current = parent */
}
/*----------------------------------------------------------------------------*/
static void HeapifyDownIMP(int* arr_, size_t heap_size_)
{
	/*asserts*/
	/* get start pointer by calling GetStartIMP() */
	/* current = root*/
    /* while current < heap_size_ and has children */
        /* find maximum child, call LChildIMP() and RChildIMP() for children */
        /* if child > current */
            /* call SwapIMP on current with child */
            /* current = child */
        /* else */
            /* stop */
}
/*----------------------------------------------------------------------------*/
static void SwapIMP(int* arr_, size_t idx1_, size_t idx2_)
{
    /* assert valid array */
    /* use temp variable to swap values */
}
/*----------------------------------------------------------------------------*/
static size_t GetParentIMP(size_t idx_)
{
    /* assert*/
    /* return idx/2 */
}
/*----------------------------------------------------------------------------*/
static size_t RChildIMP(size_t idx_)
{
    /* assert */
    /* return (2*idx_ + 1)*/
}
/*----------------------------------------------------------------------------*/
static size_t LChildIMP(size_t idx_)
{
    /* assert */
    /* return (2*idx_)*/
}
