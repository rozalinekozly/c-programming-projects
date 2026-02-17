#include <assert.h>     /* assert - used in all functions for parameter validation */
#include <stdlib.h>     /* malloc - PQCreate, free - PQDestroy */
#include <stddef.h>     /* size_t - used throughout for indices and sizes */

#include "utils.h"  /* DEBUG_ONLY, BAD_MEM */
#include "pqueue.h" /* API header - pq_ty, pq_cmp_ty, pq_is_match_ty, 
                                       pq_status_ty, pq_bool_ty */
#include "vector.h"     /* vector_ty, VectorCreate, VectorDestroy, 
                           VectorPushBack, VectorPopBack, 
                           VectorGetAccessToElement, VectorSize */
/*----------------------------------------------------------------------------*/
struct pq
{
    vector_ty* vec;
    pq_cmp_ty cmp;
    const void* param;
};
/*-----------------------auxillary functions-----------------------------------*/
static void** GetStartIMP(pq_ty* pq_)
{
    /* assert valid pq */
    /* assert valid vector */
    /* get pointer to first element (index 0) of vector */
    /* subtract one pointer size to shift back */
    /* return shifted pointer */
    void** start = NULL;
    
    assert(NULL != pq_);
    assert(NULL != pq_->vec);
    
    start = (void**)VectorGetAccessToElement(pq_->vec, 0);
    start = start - 1;
    
    return start;
}
/*----------------------------------------------------------------------------*/
static size_t GetParentIMP(size_t idx_)
{
    /* if idx_ is 1 (root), return 1 */
    /* otherwise return idx/2 */
    assert(idx_ > 0);
    
    return (1 == idx_) ? 1 : idx_ / 2;
}
/*----------------------------------------------------------------------------*/
static size_t RChildIMP(size_t idx_)
{
    /* assert */
    /* return (2*idx_ + 1) */
    assert(idx_ > 0);
    
    return (2 * idx_ + 1);
}
/*----------------------------------------------------------------------------*/
static size_t LChildIMP(size_t idx_)
{
    /* assert */
    /* return (2*idx_) */
    assert(idx_ > 0);
    
    return (2 * idx_);
}
/*----------------------------------------------------------------------------*/
static void SwapIMP(void** arr_, size_t idx1_, size_t idx2_)
{
    /* assert valid array */
    /* use temp variable to swap pointer values */
    /* used by heapify-up and heapify-down to maintain heap property */
    void* temp = NULL;
    
    assert(NULL != arr_);
    
    temp = arr_[idx1_];
    arr_[idx1_] = arr_[idx2_];
    arr_[idx2_] = temp;
}
/*----------------------------------------------------------------------------*/
static size_t FindIMP(pq_ty* pq_, pq_is_match_ty is_match_, void* param_)
{
    /* assert valid pq */
    /* assert valid match function */
    /* iterate through all elements */
        /* if current element matches criteria */
            /* return its index */
    /* return 0 if not found (0 is invalid in 1-based indexing) */
    void** start = NULL;
    size_t size = 0;
    size_t i = 0;
    
    assert(NULL != pq_);
    assert(NULL != is_match_);
    
    start = GetStartIMP(pq_);
    size = VectorSize(pq_->vec);
    
    for (i = 1; i <= size; ++i)
    {
        if (is_match_(start[i], param_))
        {
            return i;
        }
    }
    
    return 0;
}
/*----------------------------------------------------------------------------*/
/*heapifying funcs-------------------------------------------------------------*/
static void HeapifyUpIMP(pq_ty* pq_, size_t idx_)
{
    /* assert valid pq_ */
    /* get start pointer */
    /* current = idx_ */
    /* while current not root and current has higher priority than parent */
        /* swap current with parent */
        /* current = parent */
    void** start = NULL;
    size_t current = 0;
    size_t parent = 0;
    
    assert(NULL != pq_);
    
    start = GetStartIMP(pq_);
    current = idx_;
    
    while (current > 1 && 
           0 > pq_->cmp(start[current], start[GetParentIMP(current)], pq_->param))
    {
        parent = GetParentIMP(current);
        SwapIMP(start, current, parent);
        current = parent;
    }
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
    void** start = NULL;
    size_t current = 0;
    size_t left = 0;
    size_t right = 0;
    size_t priority_child = 0;
    size_t size = 0;
    
    assert(NULL != pq_);
    
    start = GetStartIMP(pq_);
    current = idx_;
    size = VectorSize(pq_->vec);
    
    while (LChildIMP(current) <= size)
    {
        left = LChildIMP(current);
        right = RChildIMP(current);
        priority_child = left;
        
        if (right <= size && 
            0 > pq_->cmp(start[right], start[left], pq_->param))
        {
            priority_child = right;
        }
        
        if (0 > pq_->cmp(start[priority_child], start[current], pq_->param))
        {
            SwapIMP(start, current, priority_child);
            current = priority_child;
        }
        else
        {
            break;
        }
    }
}
/*---------------------------api implementations--------------------------------*/
pq_ty* PQCreate(pq_cmp_ty cmp_, const void* param_)
{
    /* assert cmp_ */
    /* allocate memory for priority queue structure */
    /* handle allocation failure */
    /* create vector */
    /* handle vector creation failure and cleanup */
    /* store comparison function */
    /* store parameter */
    /* return priority queue */
    pq_ty* ret = NULL;
    
    assert(NULL != cmp_);
    
    ret = (pq_ty*)malloc(sizeof(pq_ty));
    if (NULL == ret)
    {
        return NULL;
    }
    
    ret->vec = VectorCreate(1, sizeof(void*));
    if (NULL == ret->vec)
    {
        free(ret);
        DEBUG_ONLY(ret = BAD_MEM(pq_ty*));
    }
    else
    {
        ret->cmp = cmp_;
        ret->param = param_;
    }
    
    return ret;
}
/*----------------------------------------------------------------------------*/
void PQDestroy(pq_ty* pq_)
{
    /* handle NULL input (do nothing) */
    /* destroy underlying vector */
    /* free priority queue structure */
    if (NULL == pq_)
    {
        return;
    }
    
    VectorDestroy(pq_->vec);
    free(pq_);
    DEBUG_ONLY(pq_ = BAD_MEM(pq_ty*));
}
/*----------------------------------------------------------------------------*/
size_t PQCount(const pq_ty* pq_)
{
    /* assert pq_ */
    /* return size of vector */
    assert(NULL != pq_);
    
    return VectorSize(pq_->vec);
}
/*----------------------------------------------------------------------------*/
pq_bool_ty PQIsEmpty(const pq_ty* pq_)
{
    /* assert pq_ */
    /* check if vector is empty */
    /* return appropriate boolean */
    assert(NULL != pq_);
    
    return (0 == VectorSize(pq_->vec));
}
/*----------------------------------------------------------------------------*/
pq_status_ty PQEnqueue(pq_ty* pq_, void* data_)
{
    /* assert pq_ */
    /* add element to end of vector */
    /* handle insertion failure */
    /* restore heap property by bubbling up new element */
    /* return success */
    assert(NULL != pq_);
    assert(NULL != pq_->vec);
    
    if (0 != VectorPushBack(pq_->vec, &data_))
    {
        return PQ_FAIL;
    }
    
    HeapifyUpIMP(pq_, VectorSize(pq_->vec));
    
    return PQ_SUCCESS;
}
/*----------------------------------------------------------------------------*/
void* PQDequeue(pq_ty* pq_)
{
    /* assert pq_ */
    /* assert not empty */
    /* save root element for return */
    /* copy last element to root position */
    /* pop last element */
    /* if heap not empty, heapify down from root */
    /* return saved root */
    void** start = NULL;
    void* ret = NULL;
    
    assert(NULL != pq_);
    assert(!PQIsEmpty(pq_));
    
    start = GetStartIMP(pq_);
    ret = start[1];
    
    start[1] = start[VectorSize(pq_->vec)];
    VectorPopBack(pq_->vec);
    
    if (!PQIsEmpty(pq_))
    {
        HeapifyDownIMP(pq_, 1);
    }
    
    return ret;
}
/*----------------------------------------------------------------------------*/
void* PQPeek(const pq_ty* pq_)
{
    /* assert pq_ */
    /* assert not empty */
    /* return root element without removing */
    void** start = NULL;
    
    assert(NULL != pq_);
    assert(!PQIsEmpty(pq_));
    
    start = GetStartIMP((pq_ty*)pq_);
    
    return start[1];
}
/*----------------------------------------------------------------------------*/
void* PQRemove(pq_ty* pq_, pq_is_match_ty is_match_, void* param_)
{
    /* assert pq_ */
    /* assert is_match_ */
    /* find index of matching element */
    /* if not found return NULL */
    /* save element for return */
    /* replace with last element */
    /* remove last element */
    /* restore heap property both up and down */
    /* return saved element */
    void** start = NULL;
    size_t size = 0;
    size_t idx = 0;
    void* ret = NULL;
    
    assert(NULL != pq_);
    assert(NULL != is_match_);
    
    idx = FindIMP(pq_, is_match_, param_);
    if (0 == idx)
    {
        return NULL;
    }
    
    start = GetStartIMP(pq_);
    size = VectorSize(pq_->vec);
    ret = start[idx];
    
    start[idx] = start[size];
    VectorPopBack(pq_->vec);
    
    if (!PQIsEmpty(pq_))
    {
        HeapifyDownIMP(pq_, idx);
        HeapifyUpIMP(pq_, idx);
    }
    
    return ret;
}
/*----------------------------------------------------------------------------*/
