#include "priority_q.h"
#include "vector.h"
/*----------------------------------------------------------------------------*/
#define INITIAL_CAPACITY    1
/*----------------------------------------------------------------------------*/
struct pq
{
    vector_ty* vec;
    pq_cmp_ty cmp;
    void* param;
};
/*-----------------------auxillary functions-----------------------------------*/
static void** GetStartIMP(pq_ty* pq_)
{
    /* assert valid pq */
    /* assert valid vector */
    
    /* get pointer to first element (index 0) of vector */
    /* subtract one pointer size to shift back */
    /* return shifted pointer   */
}
/*----------------------------------------------------------------------------*/
static size_t GetParentIMP(size_t idx_)
{
    /* if idx_ is 1 (root), return 1 */
    /* otherwise return idx/2 */
}
/*----------------------------------------------------------------------------*/
static size_t RChildIMP(size_t idx)
{
	/*assert*/
	/*return (2*i)*/
}
/*----------------------------------------------------------------------------*/
static size_t LChildIMP(size_t idx)
{
	/*assert*/
	/*return (2*i + 1)*/
}
/*----------------------------------------------------------------------------*/
static void SwapIMP(void* a_, void* b_)
{
    /* assert valid pointers */
    
    /* use temp variable to swap pointer values */
    /* use memcpy to copy pointer-sized data */
    /* used by heapify-up and heapify-down to maintain heap property */
}
/*heapifying funcs-------------------------------------------------------------*/
static void HeapifyUpIMP(pq_ty* pq_, size_t idx_)
{
    /* assert valid pq_ */
    
    /* get start pointer */
    /* current = idx_ */
    
    /* while current not root and current has higher priority than parent */
        /* swap current with parent */
        /* current = parent */
    /* used for remove and pop*/
}
/*----------------------------------------------------------------------------*/
static void HeapifyDownIMP(pq_ty* pq_, size_t idx_)
{
    /* assert valid pq */
    
    /* get start pointer */
    /* current = idx_ (starting position passed as argument) */
    
    /* while current has children */
        /* find highest priority child */
        
        /* if child has higher priority than current */
            /* swap current with child */
            /* current = child */
        /* else */
            /* stop */
    /*used for remove and pop*/
}
/*---------------------------api implementations--------------------------------*/
pq_ty* PQCreate(pq_cmp_ty cmp_, void* param_)
{
    /* assert cmp_ */
    /* allocate memory for priority queue structure */
    /* handle allocation failure */
    
    /* create vector*/
    /* handle vector creation failure and cleanup */
    
    /* store comparison function */
    /* store parameter */
    
    /* return priority queue */
}
/*----------------------------------------------------------------------------*/
void PQDestroy(pq_ty* pq_)
{
    /* handle NULL input (do nothing)*/
    
    /* destroy underlying vector */
    /* free priority queue structure */
}
/*----------------------------------------------------------------------------*/
size_t PQCount(const pq_ty* pq_)
{
    /* assert pq_*/
    
    /* return size of vector */
}
/*----------------------------------------------------------------------------*/
pq_bool_ty PQIsEmpty(const pq_ty* pq_)
{
    /* assert pq_*/
    
    /* check if vector is empty */
    /* return appropriate boolean */
}
/*----------------------------------------------------------------------------*/
pq_status_ty PQEnqueue(pq_ty* pq_, void* data_)
{
    /* assert pq_*/
    /* assert data (?)*/
    
    /* add element to end of vector */
    /* handle insertion failure */
    
    /* restore heap property by bubbling up (heapifyUp)new element */
    
    /* return success */
}
/*----------------------------------------------------------------------------*/
void* PQDequeue(pq_ty* pq_)
{
    /* assert pq_ */
    /* assert not empty */
    
    /* save root element for return */
    
    /* copy last element to root position */
    /* pop last element */
    
    /* if heap not empty, heapify down(HeapDown) from root */
    
    /* return saved root (popped element)*/
}
/*----------------------------------------------------------------------------*/
void* PQPeek(const pq_ty* pq_)
{
    /* assert pq_ */
    /* assert not empty */
    
    /* return root element without removing */
}
/*----------------------------------------------------------------------------*/
void* PQRemove(pq_ty* pq_, pq_is_match_ty is_match_, void* param_)
{
    /* assert pq_ */
    /* assert is_match_*/
    
    /* iterate through all elements */
        /* check if current element matches criteria */
        
        /* if match found */
            /* save element for return */
            
            /* replace with last element if not already last */
            /* remove last element */
            
            /* restore heap property both up and down */
            
            /* return saved element */
    
    /* return NULL if not found */
}
/*----------------------------------------------------------------------------*/
