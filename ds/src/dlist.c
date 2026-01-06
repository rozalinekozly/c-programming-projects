/*--------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer : oshrat
version : 1
date : 23 Dec 2025
----------------------------------------------------------------------------*/
#include <assert.h> 		/* assert() */
#include <stdlib.h> 		/* malloc(), free() */
#include "dlist.h"            /* API */

#define TRUE 1
#define FALSE 0

#define SUCCESS  0
#define FAIL 1
#define UNUSED(x)			        ((void)x)
/*----------------------------------------------------------------------------*/
/* node strucutre */
struct dlist_node
{
	/*holds data in an instance*/
	void* data;
	/* pointer to next node*/
	dlist_node_ty* next;
	/* pointer to previous node*/
	dlist_node_ty* prev;
};
/* management list strucutre
   user data is stored between them */
struct dlist
{
	dlist_node_ty head;
	dlist_node_ty tail;
};
/*---------------abstraction layer on iter (conversion)------------------------*/
/* Converts an iterator (public) to a node pointer (private) */
static dlist_node_ty* IterToNode(const dlist_iter_ty iter)
{
	return ((dlist_node_ty*)iter);
}
/* Converts a node pointer (private) to an iterator (public) */
static dlist_iter_ty NodeToIter(const dlist_node_ty* node)
{
	return ((dlist_iter_ty)node);
}
/*----------------------------aux functions ----------------------------------*/
static void IterSetNext(dlist_iter_ty iter, dlist_iter_ty new_next)
{
	IterToNode(iter)->next = IterToNode(new_next);
}
static void IterSetPrev(dlist_iter_ty iter, dlist_iter_ty new_prev)
{
	IterToNode(iter)->prev = IterToNode(new_prev);
}
/*static dlist_iter_ty GetHead(dlist_ty* list)
{
	return (NodeToIter(&list->head));
}*/
/*-----------------------------implementation---------------------------------*/
dlist_ty* DListCreate()
{
	dlist_ty* list = (dlist_ty*)malloc(sizeof(dlist_ty));
	if(NULL == list)
	{
		return NULL;
	}
	
	/*intialize list's fields*/
	list->head.data = NULL;
	list->tail.data = NULL;
	
	list->head.next = &(list->tail);
	list->head.prev = NULL;
	
	list->tail.next = NULL;
	list->tail.prev = &(list->head);
	
	return list;
}
/*----------------------------------------------------------------------------*/
void DListDestroy(dlist_ty* list)
{
	dlist_node_ty* curr_node = NULL;
	dlist_node_ty* next_node = NULL;
	
	if(NULL == list)
	{
		return;
	}
	curr_node = list->head.next;
	while(curr_node != (&list->tail))
	{
		next_node = curr_node->next;
		free(curr_node);
		curr_node = next_node;
	}
	free(list);
	list = NULL;
}
/*----------------------------------------------------------------------------*/
dlist_iter_ty DListEndIter(const dlist_ty* dlist)
{
	return (NodeToIter(&dlist->tail));
}
/*----------------------------------------------------------------------------*/
dlist_iter_ty DListBeginIter(const dlist_ty* dlist)
{
	return (NodeToIter(dlist->head.next));
}
/*----------------------------------------------------------------------------*/
dlist_iter_ty DListIterNext(const dlist_iter_ty iter)
{
	return(NodeToIter(IterToNode(iter)->next));
}
/*----------------------------------------------------------------------------*/
dlist_iter_ty DListIterPrev(const dlist_iter_ty iter)
{
	return(NodeToIter(IterToNode(iter)->prev));
}
/*----------------------------------------------------------------------------*/
void DListIterSetData(dlist_iter_ty iter, void* data_to_set)
{
	IterToNode(iter)->data = data_to_set;
}
/*----------------------------------------------------------------------------*/
void* DListIterGetData(const dlist_iter_ty iter)
{
	return(IterToNode(iter)->data);
}
/*----------------------------------------------------------------------------*/
dlist_iter_ty DListInsertBefore(dlist_ty* dlist, dlist_iter_ty where, void* new_data)
{
	dlist_iter_ty where_old_prev = DListIterPrev(where);
	
	dlist_iter_ty new_node = NodeToIter((dlist_node_ty*)malloc(sizeof(dlist_node_ty)));
	if(NULL == new_data)
	{
		return DListEndIter(dlist);
	}
	
	UNUSED(dlist);
	DListIterSetData(new_node, new_data);
	IterSetNext(new_node, where);
	IterSetPrev(new_node, where_old_prev);
	
	IterSetNext(where_old_prev, new_node);
	IterSetPrev(where, new_node);
	
	return new_node;
}
/*----------------------------------------------------------------------------*/
dlist_iter_ty DListRemove(dlist_iter_ty iter)
{
	dlist_iter_ty iter_prev = DListIterPrev(iter);
	dlist_iter_ty iter_next = DListIterNext(iter);
	
	IterSetPrev(iter_next, iter_prev);
	IterSetNext(iter_prev, iter_next);
	free(iter);
	
	return iter_next;
}
/*----------------------------------------------------------------------------*/
dlist_iter_ty DListPushFront(dlist_ty* dlist, void* new_data)
{
    /* DListInsertBefore handles the malloc, the linking, AND the NULL check */
    return DListInsertBefore(dlist, DListBeginIter(dlist), new_data);
}
/*----------------------------------------------------------------------------*/
void DListPopFront(dlist_ty* dlist)
{
    /* DListRemove handles the neighbor re-linking and the free() */
    DListRemove(DListBeginIter(dlist));
}
/*----------------------------------------------------------------------------*/
dlist_iter_ty DListPushBack(dlist_ty* dlist, void* new_data)
{
    /* Insert right before the Tail dummy */
    return DListInsertBefore(dlist, DListEndIter(dlist), new_data);
}
/*----------------------------------------------------------------------------*/
void DListPopBack(dlist_ty* dlist)
{
    /* Remove the node immediately preceding the tail */
    DListRemove(DListIterPrev(DListEndIter(dlist)));
}
/*----------------------------------------------------------------------------*/
int DListIsEmpty(const dlist_ty* dlist)
{
	if(DListBeginIter(dlist) == DListEndIter(dlist))
	{
		return TRUE;
	}
	return FALSE;
}
/*----------------------------------------------------------------------------*/
int DListIterIsEqual(const dlist_iter_ty iter1, const dlist_iter_ty iter2)
{
	return(IterToNode(iter1) == IterToNode(iter2));
}
/*----------------------------------------------------------------------------*/
dlist_iter_ty DListFind(const dlist_iter_ty from, const dlist_iter_ty to, 
                        is_match_func_ty is_match, void* param)
{
    dlist_iter_ty range_iter = from; 
    assert(NULL != is_match);

    while ((FALSE == DListIterIsEqual(range_iter, to)) && 
           (FALSE == is_match(DListIterGetData(range_iter), param)))
    {
        range_iter = DListIterNext(range_iter); 
    }
    return range_iter;
}
/*----------------------------------------------------------------------------*/
int DListForEach(dlist_iter_ty from, const dlist_iter_ty to,action_func_ty action,
 				 void* param)
{
    int status = 0;
    dlist_iter_ty range_iter = from;

    /* Per description: undefined behavior if action is NULL */
    assert(NULL != action);

    /* Iterate from 'from' up to, but not including, 'to' */
    while (!DListIterIsEqual(range_iter, to) && (0 == status))
    {
        /* Perform action and update status */
        status = action(DListIterGetData(range_iter), param);
        
        /* Move to the next node */
        range_iter = DListIterNext(range_iter);
    }

    return status;
}
/*----------------------------------------------------------------------------*/
int DListMultiFind(const dlist_iter_ty from, const dlist_iter_ty to, 
                   dlist_ty* dest, is_match_func_ty is_match, void* param)
{
	dlist_iter_ty range_iter = (dlist_iter_ty)from; 
	dlist_iter_ty push_back_ret_val = NULL;
	
	assert(NULL != is_match);

	while ((FALSE == DListIterIsEqual(range_iter, to)))
	{
		if(TRUE == is_match(DListIterGetData(range_iter), param))
		{
			push_back_ret_val = DListPushBack(dest, DListIterGetData(range_iter));
			if(NULL == push_back_ret_val)
			{
				return FAIL;
			}
		}
		range_iter = DListIterNext(range_iter);
	
	}
	return SUCCESS;
}
/*----------------------------------------------------------------------------*/
static int CountHelper(void* data, void* param)
{
    /* We don't need the data, just the counter */
    UNUSED(data); 
    
    /* Cast the void* back to a size_t pointer and increment what it points to */
    *(size_t*)param += 1;
    
    return 0; /* Always return 0 so ForEach continues to the next node */
}
/*----------------------------------------------------------------------------*/
size_t DListCount(const dlist_ty* dlist)
{
    size_t count = 0;
    dlist_iter_ty from = DListBeginIter(dlist);
    dlist_iter_ty to = DListEndIter(dlist);

    /* ForEach will call CountHelper for every node in the range */
    DListForEach(from, to, CountHelper, &count);

    return count;
}
/*----------------------------------------------------------------------------*/
void DListSplice(dlist_iter_ty from, dlist_iter_ty to, dlist_iter_ty where)
{
	dlist_iter_ty from_prev = NULL;
	dlist_iter_ty where_prev = NULL;
	dlist_iter_ty to_prev = NULL;
	
	assert(NULL != from && NULL != to && NULL != where);
	
	from_prev = DListIterPrev(from);
	where_prev = DListIterPrev(where);
	to_prev = DListIterPrev(to);
	
	IterSetNext(from_prev, to);
	IterSetPrev(to, from_prev);
	IterSetNext(where_prev, from);
	IterSetPrev(from, where_prev);
	IterSetNext(to_prev, where);
	IterSetPrev(where, to_prev);
}




