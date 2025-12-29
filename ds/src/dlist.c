/*--------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer : oshrat
worksheet : (ds - dlist)
version : 1
date : 23 Dec 2025
stage :  writing code
----------------------------------------------------------------------------*/
#include <assert.h> 		/* assert() */
#include <stdlib.h> 		/* malloc(), free() */
#include "dlist.h"            /* API */

#define TRUE 1
#define FALSE 0

#define SUCCESS  0
#define FAIL 1
#define UNUSED(x)			        ((void)x)
#define FREE(x) 					(free(x), x = NULL)

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
/*----------------------------aux functions ----------------------------------*/
/*--------------------abstraction layer on iter ------------------------------*/
/* add that this is a pointer to node not actual node! */
static dlist_node_ty* IterToNode(const dlist_iter_ty iter)
{
	return ((dlist_node_ty*)iter);
}
static dlist_iter_ty NodeToIter(const dlist_node_ty* node)
{
	return ((dlist_iter_ty)node);
}
/*----------------------------aux functions ----------------------------------*/
/*
	takes an iterator and sets it's next to be the second passed argument.
*/
static void IterSetNext(dlist_iter_ty iter, dlist_iter_ty new_next)
{
	IterToNode(iter)->next = IterToNode(new_next);
}
static void IterSetPrev(dlist_iter_ty iter, dlist_iter_ty new_prev)
{
	IterToNode(iter)->prev = IterToNode(new_prev);
}
static dlist_iter_ty GetHead(dlist_ty* list)
{
	return (NodeToIter(&list->head));
}
/*----------------------------------------------------------------------------*/
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
	list->head.prev = NULL;
	
	return list;
}
/*----------------------------------------------------------------------------*/
/*
	using remove function may cause an overhead, since remove makes sure prev 
	node points at the new node, wheras in destroy we just free first mode
	and carry on.
*/
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
/* change implementation using insert function*/
dlist_iter_ty DListPushFront(dlist_ty* dlist, void* new_data)
{
	dlist_iter_ty new_node = NodeToIter((dlist_node_ty*)malloc(sizeof(dlist_node_ty)));
	dlist_iter_ty old_start = DListBeginIter(dlist);
	dlist_iter_ty head = GetHead(dlist);
	
	DListIterSetData(new_node, new_data);
	IterSetNext(head, new_node);
	IterSetPrev(new_node, head);
	IterSetNext(new_node, old_start);
	IterSetPrev(old_start, new_node);
	
	return new_node;
}
/*----------------------------------------------------------------------------*/
/* change implementation using remove function*/
void DListPopFront(dlist_ty* dlist)
{
	dlist_iter_ty head = GetHead(dlist);
	dlist_iter_ty node_to_rmv = DListBeginIter(dlist);
	dlist_iter_ty new_start = DListIterNext(node_to_rmv);
	
	IterSetNext(head, new_start);
	IterSetPrev(new_start, head);
	
	free(node_to_rmv);
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
/* implement is using foreach() */
size_t DListCount(const dlist_ty* dlist)
{
	dlist_iter_ty list_iter = DListBeginIter(dlist);
	dlist_iter_ty list_tail = DListEndIter(dlist);
	size_t counter = 0;
	
	while(list_iter != list_tail)
	{
		++counter;
		list_iter = DListIterNext(list_iter);
	}
	return counter;
}
/*----------------------------------------------------------------------------*/
/* change implementation using insert function did not pass tests something wrong! */
dlist_iter_ty DListPushBack(dlist_ty* dlist, void* new_data)
{
	/* add assert! */
	dlist_iter_ty new_node = NodeToIter((dlist_node_ty*)malloc(sizeof(dlist_node_ty)));
	dlist_iter_ty old_end = DListEndIter(dlist)->prev;
	dlist_iter_ty tail = DListEndIter(dlist);
	if(NULL == new_node)
	{
		return DListEndIter(dlist);
	}

	
	DListIterSetData(new_node, new_data);
	IterSetPrev(tail, new_node);
	IterSetNext(new_node, tail);
	IterSetNext(old_end, new_node);
	IterSetPrev(new_node, old_end);
	
	return new_node;	
}
/*----------------------------------------------------------------------------*/
/* change implementation using remove function*/
void DListPopBack(dlist_ty* dlist)
{
	dlist_iter_ty tail = DListEndIter(dlist);
	dlist_iter_ty node_to_rmv = DListIterPrev(DListEndIter(dlist));
	dlist_iter_ty new_end = DListIterPrev(node_to_rmv);
	
	IterSetNext(new_end, tail);
	IterSetPrev(tail, new_end);
	
	free(node_to_rmv);
}
/*----------------------------------------------------------------------------*/
dlist_iter_ty DListInsertBefore(dlist_ty* dlist, dlist_iter_ty where, void* new_data)
{
	dlist_iter_ty where_old_prev = DListIterPrev(where);
	dlist_iter_ty new_node = NodeToIter((dlist_node_ty*)malloc(sizeof(dlist_node_ty)));
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
int DListIterIsEqual(const dlist_iter_ty iter1, const dlist_iter_ty iter2)
{
	return(IterToNode(iter1) == IterToNode(iter2));
}
/*----------------------------------------------------------------------------*/
dlist_iter_ty DListFind(const dlist_iter_ty from, const dlist_iter_ty to, 
						 is_match_func_ty is_match, void* param)
{
	dlist_iter_ty range_iter = (dlist_iter_ty)from; 
	
	assert(NULL != is_match);

	/* while range_iter is still in the range, and haven't found a matching yet
	   continue traversing on the list and make rang_iter to point on next node
	   in the list */
	while ((FALSE == DListIterIsEqual(range_iter, to)) && 
	      (FALSE == is_match(DListIterGetData(range_iter), param)))
	{
		range_iter = DListIterNext(from);
	}
	return range_iter;
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




