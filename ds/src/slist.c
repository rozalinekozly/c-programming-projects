/*--------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer  : nimrod
worksheet : 14 (ds - slist)
version   : 1
date      : 14 Dec 2025
stage     : intial
----------------------------------------------------------------------------*/
#include <assert.h> 			/* assert() */
#include <stdlib.h> 			/* malloc(), free() */
#include "../include/slist.h"

#define TRUE 1
#define FALSE 0

#define UNUSED(x)			 ((void)x)
#define FREE(x)			 (free(x), x = NULL)

/* node strucutre */
struct slist_node
{
	slist_node_ty* next;
	void* data;
};

/* managing list strucutre */
struct slist
{
	slist_node_ty* head;
	slist_node_ty* tail;
};

/*--------------------------implementation-------------------------------------*/

/* fuctions that translate from iter to node , hidden from the user */
static slist_node_ty* IterToNode(slist_iter_ty iter)
{
	return (slist_node_ty*)iter;
}

/*------------------setters and getters from iterator--------------------------*/
/* getters */
void* IterGetData(slist_iter_ty iter)
{
	return (IterToNode(iter) -> data);
}

/* get the tail */
slist_iter_ty SListEndIter(const slist_ty* slist_p)
{
	assert(NULL != slist_p);
	return ((slist_iter_ty)slist_p -> tail);
}
/* get the head */
slist_iter_ty SListBeginIter(const slist_ty* slist_p)
{
	assert(NULL != slist_p);
	
	return (slist_iter_ty)slist_p->head;
}
/* setters */
/* set data */
void IterSetData(slist_iter_ty iter, void* data)
{
	IterToNode(iter)->data = data;
}
/* set next pointer */
static void IterSetNext(slist_iter_ty iter, slist_iter_ty iter_next)
{
	IterToNode(iter)->next = IterToNode(iter_next);
}
/*this function provides the user a way to make iter points at next node in list */
slist_iter_ty IterNext(slist_iter_ty iter)
{
	return IterToNode(iter)->next;
}

/* comparing between two iterators */
int IterIsEqual(slist_iter_ty iter1, slist_iter_ty iter2)
{
	assert(NULL != iter1 && NULL != iter2); 
	return (iter1 == iter2);
}



static int IsItTheTail(slist_iter_ty iter)
{
	return (NULL == (IterToNode(iter) -> next));
}




/* create*/
slist_ty* SListCreate(void)
{
	/* managing node */
	slist_ty* list_p = NULL;
	/*first node in list is the tail (dummy)*/
	slist_node_ty* dummy_p = NULL;
	
	/* create a managing structure */
	list_p =  (slist_ty*)malloc(sizeof(slist_ty));
	if (NULL == list_p)
	{
		return NULL;
	}
	/* create the only node currently in the list (the dummy) */
	dummy_p = (slist_node_ty*)malloc(sizeof(slist_node_ty));
	if (NULL == dummy_p)
	{
		/* free allocated memeory so far before exiting */
		FREE(list_p);
		return NULL;
	}
	
	/* tail holds a pointer to the managing struct */
	dummy_p -> data = list_p;
	dummy_p -> next = NULL;
	
	list_p -> head = dummy_p;
	list_p -> tail = dummy_p;
	
	return list_p;
}

size_t SListCount(const slist_ty* slist_p)
{
	slist_iter_ty list_iterator = NULL;
	size_t counter = 0;
	assert(NULL != slist_p);
	
	list_iterator = SListBeginIter(slist_p);
	list_tail = SListEndIter(slist_p);
	while(list_iterator != list_tail)
	{
		++counter;
		list_iterator ->= next;
	
	}
	
	return counter;	
}

/* destroy - remove */
/* an aux function that deletes the node pointed at by iter */
static void IterRemove(slist_iter_ty iter)
{
	slist_node_ty* node_p = IterToNode(iter);
	assert(NULL != iter);
	FREE(node_p);
}

/* in case of deletion of the node pointing at the tail, must perform some adjastment */
static void SetNewTail(slist_iter_ty new_tail)
{
	/*make sure we are dealing with a dummy (tail)*/
	assert(NULL == IterNext(new_tail));
	/* set the managing strucutre's data -> tail to point at
	    new tail */
	((slist_ty*)(IterGetData(new_tail))) -> tail = new_tail;	
}

void SListDestroy(slist_ty* slist_p)
{
	/* curr iter points at current node to delete, next iter holds next node
	   from current in order not to lose track of the list. and end holds the tail*/
	slist_iter_ty curr_iter = NULL;
	slist_iter_ty next_iter = NULL;
	slist_iter_ty end_iter = NULL;
	/* perform nothing */
	if (NULL == slist_p)
	{
		return;
	}

	curr_iter = SListBeginIter(slist_p);
	end_iter = SListEndIter(slist_p);
	/* keep removing till we got to the tail */
	while (FALSE == IterIsEqual(curr_iter, end_iter))
	{
		next_iter = IterNext(curr_iter);
		IterRemove(curr_iter);
		cur_iter = next_iter;
	}
	
	/* remove tail (dummy node) */
	IterRemove(end_iter);
	/* preventing dangling pointers */
	curr_iter = NULL;
	end_iter = NULL;
	FREE(slist_p);
}

slist_iter_ty SListRemove(slist_iter_ty iter)
{
	slist_iter_ty iter_next = IterNext(iter);
	/* make node that iter points at to be an exact copy of it's next node 
	   (So we can delete next node in O(1) */
	/* important : even if the next itr is the tail, the node now
	    contains the managing strucutre in it's data*/
	IterSetData(iter, IterGetData(iter_next));
	IterSetNext(iter, IterNext(iter_next));
	/* if the next is the tail (basically trying to delete a node before the tail) */
	if (TRUE == IsItTheTail(iter_next))
	{
		/* then copying data and next to the new node is not
		    enough, must update the managing structure about the new tail */
		SetNewTail(iter);
	}
	/* safely can remove the next node*/
	IterRemove(iter_next);
	/*preventing dangling pointers */
	iter_next = NULL;	
	return iter;
}
/*-----------------------------insertion --------------------------------------*/
slist_iter_ty SListInsertBefore(slist_ty* slist_p, slist_iter_ty where_iter, void* new_data)
{
	slist_iter_ty iter_next = NULL;
	slist_iter_ty end = NULL;
	
	assert(NULL != slist_p);
	assert(NULL != new_data);
	
	iter_next = (slist_iter_ty)malloc(sizeof(slist_node_ty));
	if (NULL == iter_next)
	{
		return slist_p->tail;
	}
	
	IterSetData(iter_next, IterGetData(where_iter));
	IterSetNext(iter_next, IterNext(where_iter));
	
	end = SListEndIter(slist_p);
	if (TRUE == IterIsEqual(where_iter, end))
	{
		slist_p->tail = IterToNode(iter_next);
	}
	
	IterSetData(where_iter, new_data);
	IterSetNext(where_iter, iter_next);
	
	return where_iter;		
}
/*-----------------------------search----------------------------------------*/

slist_iter_ty SListFind(slist_iter_ty from, slist_iter_ty to, 
							match_func_ty is_match, void* param)
{
	assert(NULL != is_match);
	assert(NULL != param);
	
	while (	(FALSE == IterIsEqual(from, to)) && 
			(FALSE == is_match(from->data, param))	)
	{
		from = IterNext(from); 
	}
	
	return from;
}

			  




int SListForEach( slist_iter_ty from, slist_iter_ty to, 
				  action_func_ty action,  void *param)
{
	int action_result = TRUE;
	
	assert(NULL != action);
	assert(NULL != param);
	
	while ((FALSE == IterIsEqual(from, to)) && (TRUE == action_result))
	{
		action_result = action(from->data, param);
		from = IterNext(from); 
	}
	
	return action_result;
}
	
