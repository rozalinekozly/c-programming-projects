#include <stdlib.h>
#include <assert.h>
#include "sorted_list.h"

static dlist_iter_ty SIterToDIter(sorted_list_iter_ty s_iter);
static sorted_list_iter_ty DIterToSIter(dlist_iter_ty iter, const sorted_list_ty* lst);
static const sorted_list_ty* SIterToSList(sorted_list_iter_ty s_iter);

struct sorted_list
{
	dlist_ty* list;
	sorted_list_cmp_func_ty cmp;
	void* param;
};

sorted_list_ty* SortedListCreate(sorted_list_cmp_func_ty cmp, void* param)
{
	sorted_list_ty* lst = NULL;

	assert(NULL != cmp);

	lst = (sorted_list_ty*)malloc(sizeof(sorted_list_ty));
	if (NULL == lst)
	{
		return NULL;
	}

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
if (NULL == lst)
{
return;
}

DListDestroy(lst->list);
free(lst);
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

sorted_list_iter_ty SortedListInsert(sorted_list_ty* lst, void* new_data)
{
sorted_list_iter_ty iter;
sorted_list_iter_ty end;
dlist_iter_ty d_new;

assert(NULL != lst);

iter = SortedListBeginIter(lst);
end = SortedListEndIter(lst);

while (!SortedListIterIsEqual(iter, end) &&
lst->cmp(SortedListIterGetData(iter), new_data, lst->param) < 0)
{
iter = SortedListIterNext(iter);
}

d_new = DListInsertBefore(lst->list, SIterToDIter(iter), new_data);
return DIterToSIter(d_new, lst);
}

sorted_list_iter_ty SortedListRemove(sorted_list_iter_ty iter)
{
dlist_iter_ty d_iter;
const sorted_list_ty* lst;

assert(NULL != SIterToDIter(iter));

d_iter = SIterToDIter(iter);
lst = SIterToSList(iter);
d_iter = DListRemove(d_iter);

return DIterToSIter(d_iter, lst);
}

void* SortedListIterGetData(sorted_list_iter_ty iter)
{
	assert(NULL != SIterToDIter(iter));
	return DListIterGetData(SIterToDIter(iter));
}

void SortedListIterSetData(sorted_list_ty* lst, sorted_list_iter_ty iter, void* new_data)
{
	assert(NULL != lst);
	assert(NULL != SIterToDIter(iter));

	SortedListRemove(iter);
	SortedListInsert(lst, new_data);
}
----------------------------------------------------------------------------*/
sorted_list_iter_ty SortedListEndIter(const sorted_list_ty* lst)
{
	assert(NULL != lst);
	return DIterToSIter(DListEndIter(lst->list), lst);
}
----------------------------------------------------------------------------*/
sorted_list_iter_ty SortedListBeginIter(const sorted_list_ty* lst)
{
	assert(NULL != lst);
	return DIterToSIter(DListBeginIter(lst->list), lst);
}
----------------------------------------------------------------------------*/
sorted_list_iter_ty SortedListIterNext(sorted_list_iter_ty iter)
{
	dlist_iter_ty d_next;
	const sorted_list_ty* lst;

	assert(NULL != SIterToDIter(iter));

	d_next = DListIterNext(SIterToDIter(iter));
	lst = SIterToSList(iter);

	return DIterToSIter(d_next, lst);
}
----------------------------------------------------------------------------*/
sorted_list_iter_ty SortedListIterPrev(sorted_list_iter_ty iter)
{
	dlist_iter_ty d_prev;
	const sorted_list_ty* lst;

	assert(NULL != SIterToDIter(iter));

	d_prev = DListIterPrev(SIterToDIter(iter));
	lst = SIterToSList(iter);

	return DIterToSIter(d_prev, lst);
}
----------------------------------------------------------------------------*/
int SortedListIterIsEqual(sorted_list_iter_ty iter1, sorted_list_iter_ty iter2)
{
	assert(NULL != SIterToDIter(iter1));
	assert(NULL != SIterToDIter(iter2));
	assert(SIterToSList(iter1) == SIterToSList(iter2));

	return DListIterIsEqual(SIterToDIter(iter1), SIterToDIter(iter2));
}

int SortedListForEach(sorted_list_iter_ty from, sorted_list_iter_ty to,
sorted_list_action_func_ty action, void* param)
{
	assert(NULL != action);
	assert(NULL != SIterToDIter(from));
	assert(NULL != SIterToDIter(to));
	assert(SIterToSList(from) == SIterToSList(to));

	return DListForEach(SIterToDIter(from), SIterToDIter(to), action, param);
}
----------------------------------------------------------------------------*/
sorted_list_iter_ty SortedListFind(sorted_list_ty* lst, void* data)
{
	sorted_list_iter_ty iter;
	sorted_list_iter_ty end;
	int cmp_res;

	assert(NULL != lst);

	iter = SortedListBeginIter(lst);
	end = SortedListEndIter(lst);

	while (!SortedListIterIsEqual(iter, end))
	{
		cmp_res = lst->cmp(SortedListIterGetData(iter), data, lst->param);

	if (0 == cmp_res)
	{
		return iter;
	}

	if (0 < cmp_res)
	{
		break;
	}

	iter = SortedListIterNext(iter);
	}

	return end;
}
----------------------------------------------------------------------------*/
sorted_list_iter_ty SortedListFindIf(sorted_list_iter_ty from, sorted_list_iter_ty to,
sorted_list_is_match_func_ty is_match, void* param)
{
	assert(NULL != is_match);
	assert(NULL != SIterToDIter(from));
	assert(NULL != SIterToDIter(to));
	assert(SIterToSList(from) == SIterToSList(to));

	while (!SortedListIterIsEqual(from, to))
	{
		if (is_match(SortedListIterGetData(from), param))
		{
			return from;
		}

	from = SortedListIterNext(from);
	}

	return to;
}
----------------------------------------------------------------------------*/
void SortedListMerge(sorted_list_ty* dest, sorted_list_ty* src)
{
	dlist_iter_ty dest_it;
	dlist_iter_ty dest_end;
	dlist_iter_ty src_it;
	dlist_iter_ty src_end;
	dlist_iter_ty run_from;
	dlist_iter_ty run_to;

	assert(NULL != dest);
	assert(NULL != src);
	assert(NULL != dest->cmp);

	dest_it = DListBeginIter(dest->list);
	dest_end = DListEndIter(dest->list);
	src_it = DListBeginIter(src->list);
	src_end = DListEndIter(src->list);

	while (!DListIterIsEqual(src_it, src_end))
	{
		if (DListIterIsEqual(dest_it, dest_end))
		{
			DListSplice(src_it, src_end, dest_end);
			break;
		}

		while (!DListIterIsEqual(dest_it, dest_end) && dest->cmp(DListIterGetData(dest_it),
		DListIterGetData(src_it), dest->param) < 0)
		{
			dest_it = DListIterNext(dest_it);
		}

		if (DListIterIsEqual(dest_it, dest_end))
		{
			DListSplice(src_it, src_end, dest_end);
			break;
		}

		run_from = src_it;
		run_to = src_it;

		while (!DListIterIsEqual(run_to, src_end) && dest->cmp(DListIterGetData(run_to),
		DListIterGetData(dest_it), dest->param) <= 0)
		{
			run_to = DListIterNext(run_to);
		}

		DListSplice(run_from, run_to, dest_it);
		src_it = run_to;
	}
}
----------------------------------------------------------------------------*/
#ifndef NDEBUG
static dlist_iter_ty SIterToDIter(sorted_list_iter_ty s_iter)
{
	return s_iter.d_iter;
}

static sorted_list_iter_ty DIterToSIter(dlist_iter_ty iter,
const sorted_list_ty* lst)
{
sorted_list_iter_ty s_iter;
s_iter->d_iter = iter;
s_iter->sorted_lst = lst;
return s_iter;
}

static const sorted_list_ty* SIterToSList(sorted_list_iter_ty s_iter)
{
return s_iter->sorted_lst;
}
	
#endif
