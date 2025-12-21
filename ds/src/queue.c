/*--------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer : oshi
worksheet : 16 (ds - queue)
version : 2
date : 17 Dec 2025
stage : peer-review
----------------------------------------------------------------------------*/
#include <assert.h> 	/* assert() */
#include <stdlib.h> 	/* malloc(), free() */

#include "queue.h"
#include "slist.h"

#define SUCCESS 0
#define FAILED 1

#define FREE(x) 				(free(x), x = NULL)
/*------------------------------queue struct ---------------------------------*/
struct queue
{
	slist_ty *slist;
};
/*------------------------------implementations -------------------------------*/
queue_ty* QueueCreate(void)
{
	queue_ty *queue_p = NULL;

	queue_p = (queue_ty *)malloc(sizeof(queue_ty));
	if (NULL == queue_p)
	{
		return NULL;
	}

	queue_p->slist = SListCreate();
	if (NULL == queue_p->slist)
	{
		free(queue_p);
		return NULL;
	}

	return queue_p;
}

void QueueDestroy(queue_ty* queue_p)
{
	if (NULL == queue_p)
	{
		return;
	}

	SListDestroy(queue_p->slist);
	FREE(queue_p);
}

int QueueEnqueue(queue_ty* queue_p, void* data)
{
	slist_iter_ty dummy = NULL;
	slist_iter_ty res = NULL;

	assert(NULL != queue_p);

	dummy = SListEndIter(queue_p->slist);
	res = SlistInsertBefore(queue_p->slist, dummy, data);

	return SListIterIsEqual(res, dummy) ? FAILED : SUCCESS;
}

void QueueDequeue(queue_ty* queue_p)
{
	slist_iter_ty begin = NULL;

	assert(NULL != queue_p);
	assert(0 == QueueIsEmpty(queue_p));

	begin = SListBeginIter(queue_p->slist);
	SListRemove(begin);
}

void* QueuePeek(const queue_ty* queue_p)
{
	assert(NULL != queue_p);
	assert(0 == QueueIsEmpty(queue_p));

	return SListIterGetData(SListBeginIter(queue_p->slist));
}

int QueueIsEmpty(const queue_ty* queue_p)
{
	assert(NULL != queue_p);

	return SListIterIsEqual(SListBeginIter(queue_p->slist), SListEndIter(queue_p->slist));
}

size_t QueueSize(const queue_ty* queue_p)
{
	assert(NULL != queue_p);

	return SListCount(queue_p->slist);
}
	
void QueueAppend(queue_ty* queue_p1, queue_ty* queue_p2)
{
	assert(queue_p1 != NULL);
	assert(queue_p1 != NULL);
	SListAppend(queue_p1 -> slist, queue_p2 -> slist);
}
