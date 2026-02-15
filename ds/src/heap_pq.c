#include <vector.h>		/* underlying data strucutre */

struct heap
{
    vector_ty* vec;              /* pointer to dynamic array (vector) */
    compare_func_ty cmp;         /* comparison function pointer */
};

pq_ty* PQCreate(pq_cmp_ty cmp, void* param)
{
	/* allocate memory for heap_ty struct */
	
	/* check allocation success, if failed return NULL*/
	
	/* create vector with capacity = intial number (defined) and element_size = sizeof(void*) */
	
	/* check vector creation success, cleanup heap if fails */
	
	/* store cmp function pointer in heap struct */
	
	/*return heap pointer */
}
