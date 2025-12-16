/*--------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer : nimrod
worksheet : 14 (ds - slist)
version : 2
date : 16 Dec 2025
stage : mimit
----------------------------------------------------------------------------*/
#include <assert.h> 					/* assert() */
#include <stdlib.h> 					/* malloc(), free() */
#include "slist.h"

#define TRUE 1
#define FALSE 0

#define UNUSED(x)			      ((void)x)
#define FREE(x) 				(free(x), x = NULL)

/*------------- aux functions (hidden from end-user)--------------------------*/
/* conversion from iter to node pointer (adds an abstraction layer */
static slist_node_ty* IterToNode(slist_iter_ty iter);
/* sets the node's that iter points at to point as next at iter_next */
static void IterSetNext(slist_iter_ty iter, slist_iter_ty iter_next);
/* removes the node the iter points at */
static void IterRemove(slist_iter_ty iter);
/* returns is the passed iter points at the tail of the list */
static int IsItTheTail(slist_iter_ty iter);
/* sets new_tail as the tail of the the list (pointed at by the old tail data)*/
static void SetNewTail(slist_iter_ty new_tail);
/*----------------------------------------------------------------------------*/
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
static slist_node_ty* IterToNode(slist_iter_ty iter)
{
	return (slist_node_ty*)iter;
}
static int IsItTheTail(slist_iter_ty iter)
{
	return (NULL == IterToNode(iter)->next);
}
/* set next pointer */
static void IterSetNext(slist_iter_ty iter, slist_iter_ty iter_next)
{
	IterToNode(iter)->next = IterToNode(iter_next);
}

static void IterRemove(slist_iter_ty iter)
{
	slist_node_ty* node_p = IterToNode(iter);
	assert(NULL != iter);
	FREE(node_p);
}

static void SetNewTail(slist_iter_ty new_tail)
{
	assert(NULL == IterNext(new_tail));
	((slist_ty*)IterGetData(new_tail))->tail = IterToNode(new_tail);
}
/*------------------setters and getters from iterator--------------------------*/
/* getters */
void* IterGetData(slist_iter_ty iter)
{
	return IterToNode(iter)->data;
}

/* get the tail */
slist_iter_ty SListEndIter(slist_ty* slist_p)
{
	assert(NULL != slist_p);
	return (slist_iter_ty)slist_p->tail;
}

/* get the head */
slist_iter_ty SListBeginIter(slist_ty* slist_p)
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


/*this function provides the user a way to make iter points at next node in list */
slist_iter_ty IterNext(slist_iter_ty iter)
{
	return (slist_iter_ty)IterToNode(iter)->next;
}

/* comparing between two iterators */
int IterIsEqual(slist_iter_ty iter1, slist_iter_ty iter2)
{
	return (iter1 == iter2);
}

/* create */
slist_ty* SListCreate(void)
{
	slist_ty* list_p = NULL;
	slist_node_ty* dummy_p = NULL;

	list_p = (slist_ty*)malloc(sizeof(slist_ty));
	
	if (NULL == list_p)
	{
		return NULL;
	}

	dummy_p = (slist_node_ty*)malloc(sizeof(slist_node_ty));
	
	if (NULL == dummy_p)
	{
	FREE(list_p);
	return NULL;
	}

	dummy_p->data = list_p;
	dummy_p->next = NULL;

	list_p->head = dummy_p;
	list_p->tail = dummy_p;

	return list_p;
}

size_t SListCount(const slist_ty* slist_p)
{
	slist_iter_ty list_itr = slist_p -> head;
	slist_iter_ty end = SListEndIter((slist_ty*)slist_p);
      size_t count = 0;
      
      while(list_itr != end)
      {
      	++count;
      	list_itr = IterNext(list_itr);
      }
      
      return count;
}

void SListDestroy(slist_ty* slist_p)
{
	slist_iter_ty curr_iter = NULL;
	slist_iter_ty next_iter = NULL;
	slist_iter_ty end_iter = NULL;

	if (NULL == slist_p)
	{
		return;
	}

	curr_iter = SListBeginIter(slist_p);
	end_iter = SListEndIter(slist_p);

	while (FALSE == IterIsEqual(curr_iter, end_iter))
	{
		next_iter = IterNext(curr_iter);
		IterRemove(curr_iter);
		curr_iter = next_iter;
	}

	IterRemove(end_iter);
	FREE(slist_p);
}

slist_iter_ty SListRemove(slist_iter_ty iter)
{
	slist_iter_ty iter_next = NULL;
	assert(FALSE == IsItTheTail(iter));
	iter_next = IterNext(iter);

	IterSetData(iter, IterGetData(iter_next));
	IterSetNext(iter, IterNext(iter_next));

	if (TRUE == IsItTheTail(iter_next))
	{
		SetNewTail(iter);
	}

	IterRemove(iter_next);
	return iter;
}

/*-----------------------------insertion --------------------------------------*/
slist_iter_ty SlistInsertBefore(slist_ty* slist_p, slist_iter_ty where_iter,
void* new_data)
{
	slist_iter_ty iter_next = NULL;
	slist_iter_ty end = NULL;

	assert(NULL != slist_p);
	assert(NULL != where_iter);

	iter_next = (slist_iter_ty)malloc(sizeof(slist_node_ty));
	
	if (NULL == iter_next)
	{
		return SListEndIter(slist_p);
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
slist_iter_ty SListFind(slist_iter_ty from, slist_iter_ty to, match_func_ty is_match, void* param)
{
	assert(NULL != is_match);

	while ((FALSE == IterIsEqual(from, to)) &&
	(FALSE == is_match(IterGetData(from), param)))
	{
		from = IterNext(from);
	}

	return from;
}

int SListForEach(slist_iter_ty from, slist_iter_ty to, action_func_ty action, void *param)
{
	int action_result = TRUE;
	
	assert(NULL != action);

	while ((FALSE == IterIsEqual(from, to)) && (TRUE == action_result))
	{
		action_result = action(IterGetData(from), param);
		from = IterNext(from);
	}

	return action_result;
}
