/*--------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer : steve
version : 1
date : 6 Jan 2026
----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

#include "pqueue.h"

/* Simple Task structure for testing */
typedef struct task
{
    int id;
    int priority; /* Lower number = Higher priority */
} task_ty;

/* --- Helper Functions --- */

/* Higher priority means a SMALLER priority number */
static int TaskCmp(const void* data1, const void* data2, const void* param)
{
    task_ty* t1 = (task_ty*)data1;
    task_ty* t2 = (task_ty*)data2;
    (void)param;

    return (t1->priority - t2->priority);
}

/* Match based on Task ID */
static int MatchId(const void* data, void* param)
{
    return (((task_ty*)data)->id == *(int*)param);
}

/* --- Test Functions --- */

void TestPQBasic(void)
{
    pq_ty* pq = PQCreate(TaskCmp, NULL);
    task_ty t1 = {101, 3}; /* Low priority */
    task_ty t2 = {102, 1}; /* High priority */
    task_ty t3 = {103, 2}; /* Medium priority */
    
    printf("[TEST] Basic Enqueue/Dequeue/Peek\n");

    PQEnqueue(pq, &t1);
    PQEnqueue(pq, &t2);
    PQEnqueue(pq, &t3);

    if (PQCount(pq) == 3) 
    {
    	printf("  [PASS] Count is 3\n");
    }
    
    /* Peek should show the highest priority (t2) */
    if (((task_ty*)PQPeek(pq))->id == 102)
    {
    	printf("  [PASS] Peeked highest priority task (102)\n");
    } 

    /* Dequeue should return them in order: 102, 103, 101 */
    if (((task_ty*)PQDequeue(pq))->id == 102) 
    {
    	printf("  [PASS] Dequeued 102\n");
    }
    if (((task_ty*)PQDequeue(pq))->id == 103)
    {
    	printf("  [PASS] Dequeued 103\n");
    } 
    if (((task_ty*)PQDequeue(pq))->id == 101)
    {
    	printf("  [PASS] Dequeued 101\n");
    }

    if (PQIsEmpty(pq))
    {
    	printf("  [PASS] Queue is now empty\n");
    } 

    PQDestroy(pq);
}

void TestPQRemove(void)
{
    pq_ty* pq = PQCreate(TaskCmp, NULL);
    task_ty t1 = {10, 1};
    task_ty t2 = {20, 2};
    task_ty t3 = {30, 3};
    int id_to_remove = 20;
    task_ty* removed;

    printf("\n[TEST] PQRemove (Targeted removal)\n");

    PQEnqueue(pq, &t1);
    PQEnqueue(pq, &t2);
    PQEnqueue(pq, &t3);

    removed = (task_ty*)PQRemove(pq, MatchId, &id_to_remove);

    if (removed != NULL && removed->id == 20)
    {
        printf("  [PASS] Successfully removed task 20 from the middle\n");
    }
    
    if (PQCount(pq) == 2) 
    {
    	printf("  [PASS] Count is now 2\n");
    }

    /* Verify order is still preserved for remaining */
    if (((task_ty*)PQDequeue(pq))->id == 10) 
    {
    	printf("  [PASS] Next out is 10\n");
    }
    if (((task_ty*)PQDequeue(pq))->id == 30) 
    {
    	printf("  [PASS] Last out is 30\n");
    }

    PQDestroy(pq);
}

int main(void)
{
    TestPQBasic();
    TestPQRemove();

    printf("\n--- Priority Queue Tests Completed ---\n");
    return 0;
}
