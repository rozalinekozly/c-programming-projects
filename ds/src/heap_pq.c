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
static size_t ParentIMP(size_t idx)
{
	/*assert*/
	/*return (idx/2)*/
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
static void HeapifyUp(pq_ty* pq_, size_t idx_)
{
    /* assert valid priority queue */
    
    /* while not at root */
        /* find parent */
        
        /* compare current with parent */
        
        /* if current has higher priority */
            /* swap with parent */
            /* move up to parent position */
        /* otherwise */
            /* stop, heap property satisfied */
}
/*heapifying funcs-------------------------------------------------------------*/
static void HeapifyDown(pq_ty* pq_, size_t idx_)
{
    /* assert valid priority queue */
    
    /* while has children */
        /* find left child */
        
        /* if no children, stop */
        
        /* assume left child has highest priority */
        
        /* if right child exists */
            /* compare left and right children */
            /* pick child with higher priority */
        
        /* compare current with highest priority child */
        
        /* if child has higher priority */
            /* swap with child */
            /* move down to child position */
        /* otherwise */
            /* stop, heap property satisfied */
}

/*---------------------------api implementations--------------------------------*/
pq_ty* PQCreate(pq_cmp_ty cmp_, void* param_)
{
    /* assert cmp_ */
    /* allocate memory for priority queue structure */
    /* handle allocation failure */
    
    /* create underlying vector storage */
    /* handle vector creation failure and cleanup */
    
    /* store comparison function */
    /* store parameter */
    
    /* return priority queue */
}
/*----------------------------------------------------------------------------*/
void PQDestroy(pq_ty* pq_)
{
    /* handle NULL input */
    
    /* destroy underlying vector */
    /* free priority queue structure */
}
/*----------------------------------------------------------------------------*/
size_t PQCount(const pq_ty* pq_)
{
    /* assert valid priority queue */
    
    /* return number of elements in vector */
}
/*----------------------------------------------------------------------------*/
pq_bool_ty PQIsEmpty(const pq_ty* pq_)
{
    /* assert valid priority queue */
    
    /* check if vector is empty */
    /* return appropriate boolean */
}
/*----------------------------------------------------------------------------*/
pq_status_ty PQEnqueue(pq_ty* pq_, void* data_)
{
    /* assert valid priority queue */
    /* assert valid data */
    
    /* add element to end of vector */
    /* handle insertion failure */
    
    /* restore heap property by bubbling up new element */
    
    /* return success */
}
/*----------------------------------------------------------------------------*/
void* PQDequeue(pq_ty* pq_)
{
    /* assert valid priority queue */
    /* assert not empty */
    
    /* save root element for return */
    
    /* move last element to root position */
    /* remove last element */
    
    /* restore heap property by sinking down root */
    
    /* return saved root */
}
/*----------------------------------------------------------------------------*/
void* PQPeek(const pq_ty* pq_)
{
    /* assert valid priority queue */
    /* assert not empty */
    
    /* return root element without removing */
}
/*----------------------------------------------------------------------------*/
void* PQRemove(pq_ty* pq_, pq_is_match_ty is_match_, void* param_)
{
    /* assert valid priority queue */
    /* assert valid match function */
    
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

/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
