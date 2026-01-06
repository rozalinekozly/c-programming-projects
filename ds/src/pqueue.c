#include "sorted_list.h"
#include "priority_queue.h"


typedef struct priority_queue
{
	sorted_list_ty* lst;
	
} priority_queue_ty;

static int IsMatchTaskId(void* task_data, void* uid_param);


priority_queue_ty* PriorityQueueCreate(priority_queue_cmp_func_ty cmp, void* param)
{
	/* 1: create queue and validate null */
	/* 2: create sorted list with cmp func and param */
	/* 3: return q */
}

void PriorityQueueDestroy(priority_queue_ty* q)
{
	/* 1: if queue is null return */
	/* 2: destroy sorted list */
	/* 3: free queue */
}

size_t PriorityQueueCount(const priority_queue_ty* q)
{
	/* 1: return sorted list count */
}

int PriorityQueueIsEmpty(const priority_queue_ty* q)
{
	/* 1: return sorted list is empty */
}

int PriorityQueueEnqueue(priority_queue_ty* q, task_ty* tsk)
{
	/* 1: call to sorted list insert on (q->lst, tsk) */
	/* 2: return !! on returned value*/
}

task_ty* PriorityQueueDequeue(priority_queue_ty* q)
{
	/* 1: call to sorted list remove on sorted list head */
}

task_ty* PriorityQueueRemove(priority_queue_ty* q, uid_ty id)
{
	/* 1: call to sorted list findif on id and is match */
	/* 2: call to sorted list remove on returned value */
}

task_ty* PriorityQueuePeek(const priority_queue_ty* q)
{
	/* 1: return sorted list head */
}

static int IsMatchTaskId(void* task_data, void* uid_param)
{
	task_ty* tsk = (task_ty*)task_data;
	uid_ty* id = (uid_ty*)uid_param;
	
	return TaskGetUid(tsk) == *id;
}

