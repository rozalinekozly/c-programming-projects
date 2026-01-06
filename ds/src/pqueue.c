/*--------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer : steve
version : 1
date : 6 Jan 2026
----------------------------------------------------------------------------*/
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "sorted_list.h"
#include "pqueue.h"

struct pq
{
    sorted_list_ty* lst;
};

pq_ty* PQCreate(pq_cmp_ty cmp, void* param)
{
    pq_ty* q = (pq_ty*)malloc(sizeof(pq_ty));
    if (NULL == q)
    {
        return NULL;
    }

    /* We use the Sorted List to handle the heavy lifting of ordering */
    q->lst = SortedListCreate(cmp, param);
    if (NULL == q->lst)
    {
        free(q);
        return NULL;
    }

    return q;
}

void PQDestroy(pq_ty* q)
{
    if (NULL == q)
    {
        return;
    }

    SortedListDestroy(q->lst);
    free(q);
    q = NULL;
}

size_t PQCount(const pq_ty* q)
{
    assert(NULL != q);
    return SortedListCount(q->lst);
}

bool_ty PQIsEmpty(const pq_ty* q)
{
    assert(NULL != q);
    return (bool_ty)SortedListIsEmpty(q->lst);
}

status_ty PQEnqueue(pq_ty* q, void* data)
{
    sorted_list_iter_ty iter;
    assert(NULL != q);

    iter = SortedListInsert(q->lst, data);

    /* If SortedListInsert returns EndIter, it means allocation failed */
    if (SortedListIterIsEqual(iter, SortedListEndIter(q->lst)))
    {
        return FAIL;
    }

    return SUCCESS;
}

void* PQDequeue(pq_ty* q)
{
    void* data = NULL;
    assert(NULL != q);
    assert(!PQIsEmpty(q));

    /* Data is at the beginning because the list is sorted */
    data = SortedListIterGetData(SortedListBeginIter(q->lst));
    SortedListRemove(SortedListBeginIter(q->lst));

    return data;
}

void* PQPeek(const pq_ty* q)
{
    assert(NULL != q);
    assert(!PQIsEmpty(q));

    return SortedListIterGetData(SortedListBeginIter(q->lst));
}

void* PQRemove(pq_ty* q, pq_is_match_ty is_match, void* param)
{
    sorted_list_iter_ty found_iter;
    void* data = NULL;

    assert(NULL != q);
    assert(NULL != is_match);

    /* Search the sorted list for the specific element */
    found_iter = SortedListFindIf(SortedListBeginIter(q->lst), 
                                  SortedListEndIter(q->lst), 
                                  is_match, 
                                  param);

    /* If we didn't find it, return NULL */
    if (SortedListIterIsEqual(found_iter, SortedListEndIter(q->lst)))
    {
        return NULL;
    }

    data = SortedListIterGetData(found_iter);
    SortedListRemove(found_iter);

    return data;
}
