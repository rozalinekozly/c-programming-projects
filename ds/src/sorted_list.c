/*--------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer : ?
worksheet : 25 (ds - sorted list)
version : 1
date : 25 Dec 2025
stage : writing-code
----------------------------------------------------------------------------*/
#include <assert.h> 		/* assert() */
#include <stdlib.h> 		/* malloc(), free() */
#include "dlist.h"            /* API */

#define TRUE 1
#define FALSE 0

#define UNUSED(x)			      ((void)x)
#define FREE(x) 				(free(x), x = NULL)

/*------------- aux functions (hidden from end-user)--------------------------*/

/*----------------------------------------------------------------------------*/
/* node strucutre */
struct sorted_list
{
	dlist_ty* dlist;
	sorted_list_cmp_func_ty cmp;
	void* param;
}
/*--------------------------implementation-------------------------------------*/
sorted_list_ty* SortedListCreate(sorted_list_cmp_func_ty cmp, void* param)
{	
	sorted_list_ty* list = NULL;
	
	assert(NULL != cmp);
	
	list = (sorted_list_ty*)malloc(sizeof(sorted_list_ty));
	if(NULL == list)
	{
		return NULL;
	}
	
	list->dlist = DListCreate();
	if(NULL == list->dlist)
	{
		DListDestroy(list->dlist);
		free(list);
	}
	
	list->cmp = cmp;
	list->param = param;
	
	return list;
}
/*----------------------------------------------------------------------------*/
void SortedListDestroy(sorted_list_ty* lst)
{
	DListDestroy(list->dlist);
	free(lst);
}
/*----------------------------------------------------------------------------*/
size_t SortedListCount(const sorted_list_ty* lst)
{
	size_t count = 0;
	
	assert(dlist != NULL);
	
	count = DListCount(dlist);
	
	return count;
}
/*----------------------------------------------------------------------------*/
int SortedListIsEmpty(const sorted_list_ty* lst)
{
	return DListIsEmpty(lst);
}
/*----------------------------------------------------------------------------*/
void* SortedListIterGetData(sorted_list_iter_ty iter)
{
	/* add a mid interpeter from sorted list to dlist */
	return DListIterGetData(iter->dlist);
}
/*----------------------------------------------------------------------------*/
void SortedListIterSetData(sorted_list_ty* lst, sorted_list_iter_ty iter,
                            void* new_data)
{
	/* add a transition from dlist iter <-> sorted list iter */
	DListIterSetData(lst->dlist, iter, new_data);
}
/*----------------------------------------------------------------------------*/
sorted_list_iter_ty SortedListEndIter(const sorted_list_ty* lst)
{
	/*apply the conversion from dlist ptr to sorted list ptr */
	return DListEndIter(lst->dlist);
}
/*----------------------------------------------------------------------------*/
sorted_list_iter_ty SortedListBeginIter(const sorted_list_ty* lst)
{
	/*apply the conversion from dlist ptr to sorted list ptr */
	DListBeginIter(lst->dlist);
}
/*----------------------------------------------------------------------------*/
sorted_list_iter_ty SortedListIterNext(sorted_list_iter_ty iter)
{
	/*apply the conversion from dlist ptr to sorted list ptr */
	return DListIterNext(iter->dlist);
}
/*----------------------------------------------------------------------------*/
sorted_list_iter_ty SortedListIterPrev(sorted_list_iter_ty iter)
{
	/*apply the conversion from dlist ptr to sorted list ptr */
	return DListIterPrev(iter->dlist);
}
/*----------------------------------------------------------------------------*/
int SortedListIterIsEqual( sorted_list_iter_ty iter1, sorted_list_iter_ty iter2)
{
	return DListIterIsEqual(iter1->dlist, iter2->dlist);
}
/*----------------------------------------------------------------------------*/
int SortedListForEach(sorted_list_iter_ty from, sorted_list_iter_ty to, 
					   sorted_list_action_func_ty action, void* param);
{
	/*apply the conversion from dlist ptr to sorted list ptr on from and to*/
	return DListForEach(from, to, action, param);
}
/*----------------------------------------------------------------------------*/
sorted_list_iter_ty SortedListFind(sorted_list_ty* lst, void* data)
{
	/*apply the conversion from dlist ptr to sorted list ptr on ret value and args*/
	return DListFind(SortedListBeginIter(lst), SortedListEndIter(lst), lst->cmp, data);
}
/*----------------------------------------------------------------------------*/
sorted_list_iter_ty SortedListFindIf( sorted_list_iter_ty from,sorted_list_iter_ty to, 
					                  sorted_list_is_match_func_ty is_match,
					                  void* param)
{	
	/*apply the conversion from dlist ptr to sorted list ptr on ret value and args*/
	return DListFind(from, to, is_match, param);
}
/*----------------------------------------------------------------------------*/


