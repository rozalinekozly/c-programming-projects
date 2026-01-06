#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include "sorted_list.h"

struct sorted_list
{
    dlist_ty* list;
    sorted_list_cmp_func_ty cmp;
    void* param;
};

/* --- Internal Conversion Helpers --- */
/* These stay inside the ifdef because their logic changes based on mode */
#ifndef NDEBUG
static dlist_iter_ty SIterToDIter(sorted_list_iter_ty s_iter)
{
    return s_iter.d_iter;
}

static sorted_list_iter_ty DIterToSIter(dlist_iter_ty iter, const sorted_list_ty* lst)
{
    sorted_list_iter_ty s_iter;
    s_iter.d_iter = iter;
    s_iter.sorted_lst = lst;
    return s_iter;
}

static const sorted_list_ty* SIterToSList(sorted_list_iter_ty s_iter)
{
    return s_iter.sorted_lst;
}
#else /* Release Mode (-DNDEBUG) */
static dlist_iter_ty SIterToDIter(sorted_list_iter_ty s_iter)
{
    return s_iter;
}

static sorted_list_iter_ty DIterToSIter(dlist_iter_ty iter, const sorted_list_ty* lst)
{
    (void)lst;
    return iter;
}

static const sorted_list_ty* SIterToSList(sorted_list_iter_ty s_iter)
{
    (void)s_iter;
    return NULL;
}
#endif /* End of Conversion Helpers */

/*------------------------------------------------------------------------- */

sorted_list_ty* SortedListCreate(sorted_list_cmp_func_ty cmp, void* param)
{
    sorted_list_ty* lst = (sorted_list_ty*)malloc(sizeof(sorted_list_ty));
    if (NULL == lst) return NULL;

    lst->list = DListCreate();
    if (NULL == lst->list)
    {
        free(lst);
        return NULL;
    }
    lst->cmp = cmp;
    lst->param = param;
    return lst;
}

void SortedListDestroy(sorted_list_ty* lst)
{
    if (NULL != lst)
    {
        DListDestroy(lst->list);
        free(lst);
    }
}

size_t SortedListCount(const sorted_list_ty* lst)
{
    assert(NULL != lst);
    return DListCount(lst->list);
}

int SortedListIsEmpty(const sorted_list_ty* lst)
{
    assert(NULL != lst);
    return DListIsEmpty(lst->list);
}

sorted_list_iter_ty SortedListBeginIter(const sorted_list_ty* lst)
{
    assert(NULL != lst);
    return DIterToSIter(DListBeginIter(lst->list), lst);
}

sorted_list_iter_ty SortedListEndIter(const sorted_list_ty* lst)
{
    assert(NULL != lst);
    return DIterToSIter(DListEndIter(lst->list), lst);
}

sorted_list_iter_ty SortedListIterNext(sorted_list_iter_ty iter)
{
    return DIterToSIter(DListIterNext(SIterToDIter(iter)), SIterToSList(iter));
}

sorted_list_iter_ty SortedListIterPrev(sorted_list_iter_ty iter)
{
    return DIterToSIter(DListIterPrev(SIterToDIter(iter)), SIterToSList(iter));
}

int SortedListIterIsEqual(sorted_list_iter_ty iter1, sorted_list_iter_ty iter2)
{
    return DListIterIsEqual(SIterToDIter(iter1), SIterToDIter(iter2));
}

void* SortedListIterGetData(sorted_list_iter_ty iter)
{
    return DListIterGetData(SIterToDIter(iter));
}

sorted_list_iter_ty SortedListInsert(sorted_list_ty* lst, void* new_data)
{
    sorted_list_iter_ty curr;
    assert(NULL != lst);

    curr = SortedListBeginIter(lst);

    while (!SortedListIterIsEqual(curr, SortedListEndIter(lst)) &&
           lst->cmp(SortedListIterGetData(curr), new_data, lst->param) < 0)
    {
        curr = SortedListIterNext(curr);
    }

    return DIterToSIter(DListInsertBefore(lst->list, SIterToDIter(curr), new_data), lst);
}

sorted_list_iter_ty SortedListRemove(sorted_list_iter_ty iter)
{
    dlist_iter_ty d_iter = SIterToDIter(iter);
    const sorted_list_ty* lst = SIterToSList(iter);
    return DIterToSIter(DListRemove(d_iter), lst);
}

void SortedListIterSetData(sorted_list_ty* lst, sorted_list_iter_ty iter, void* new_data)
{
    SortedListRemove(iter);
    SortedListInsert(lst, new_data);
}

int SortedListForEach(sorted_list_iter_ty from, sorted_list_iter_ty to,
                      sorted_list_action_func_ty action, void* param)
{
    return DListForEach(SIterToDIter(from), SIterToDIter(to), action, param);
}

sorted_list_iter_ty SortedListFind(sorted_list_ty* lst, void* data)
{
    sorted_list_iter_ty iter;
    sorted_list_iter_ty end;

    assert(NULL != lst);
    iter = SortedListBeginIter(lst);
    end = SortedListEndIter(lst);

    while (!SortedListIterIsEqual(iter, end))
    {
        int res = lst->cmp(SortedListIterGetData(iter), data, lst->param);
        if (0 == res) return iter;
        if (res > 0) break;
        iter = SortedListIterNext(iter);
    }
    return end;
}

sorted_list_iter_ty SortedListFindIf(sorted_list_iter_ty from, sorted_list_iter_ty to,
                                     sorted_list_is_match_func_ty is_match, void* param)
{
    while (!SortedListIterIsEqual(from, to))
    {
        if (is_match(SortedListIterGetData(from), param)) return from;
        from = SortedListIterNext(from);
    }
    return to;
}

void SortedListMerge(sorted_list_ty* dest, sorted_list_ty* src)
{
    dlist_iter_ty dest_it, src_from, src_to;
    assert(NULL != dest && NULL != src && dest != src);

    dest_it = DListBeginIter(dest->list);
    src_from = DListBeginIter(src->list);

    while (!DListIterIsEqual(src_from, DListEndIter(src->list)))
    {
        while (!DListIterIsEqual(dest_it, DListEndIter(dest->list)) &&
               dest->cmp(DListIterGetData(dest_it), DListIterGetData(src_from), dest->param) < 0)
        {
            dest_it = DListIterNext(dest_it);
        }

        if (DListIterIsEqual(dest_it, DListEndIter(dest->list)))
        {
            DListSplice(src_from, DListEndIter(src->list), dest_it);
            break;
        }

        src_to = src_from;
        while (!DListIterIsEqual(src_to, DListEndIter(src->list)) &&
               dest->cmp(DListIterGetData(src_to), DListIterGetData(dest_it), dest->param) <= 0)
        {
            src_to = DListIterNext(src_to);
        }

        DListSplice(src_from, src_to, dest_it);
        src_from = src_to;
    }
}
