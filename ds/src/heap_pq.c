#include "priority_q.h"   /* pq_ty, pq_cmp_ty, etc. */
#include "vector.h"       /* underlying data structure */
/*----------------------------------------------------------------------------*/
#define INITIAL_CAPACITY    10
/*----------------------------------------------------------------------------*/
struct pq
{
    vector_ty* vec;       /* pointer to dynamic array (vector) */
    pq_cmp_ty cmp;        /* comparison function pointer - FIX: use pq_cmp_ty */
    void* param;          /* comparison func parameter */
};
/*----------------------------------------------------------------------------*/
pq_ty* PQCreate(pq_cmp_ty cmp_, void* param_)
{
    /* allocate memory for pq_ty struct */
    
    /* check allocation success, if failed return NULL */
    
    /* create vector with capacity = INITIAL_CAPACITY and element_size = sizeof(void*) */
    
    /* check vector creation success, cleanup pq if fails */
    
    /* store cmp_ function pointer in pq struct */
    
    /* store param_ in pq struct */
    
    /* return pq pointer */
}
/*----------------------------------------------------------------------------*/
void PQDestroy(pq_ty* pq_)
{
    /* if pq_ is NULL, return (do nothing) */
    
    /* destroy the vector using VectorDestroy */
    
    /* free the pq struct */
}
/*----------------------------------------------------------------------------*/
size_t PQCount(const pq_ty* pq_)
{
    /* assert pq_ not NULL */
    
    /* return VectorSize(pq_->vec) */
}
/*----------------------------------------------------------------------------*/
pq_bool_ty PQIsEmpty(const pq_ty* pq_)
{
    /* assert pq_ not NULL */
    
    /* if VectorSize(pq_->vec) == 0 */
        /* return PQ_TRUE */
    /* else */
        /* return PQ_FALSE */
}
/*----------------------------------------------------------------------------*/
