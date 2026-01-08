/*-----------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer : ??
version : 1
date : 6 Jan 2026
------------------------------------------------------------------------------*/
#include <stdio.h>  /* printf */
#include <time.h>   /* time_t, time */
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "task.h"   

/* --- Helper Functions --- */

op_status_ty ToggleTask(void *param)
{
    int *counter = (int *)param;
    printf("  [Execute] Task counter: %d\n", *counter);
    
    if (*counter > 0)
    {
        --(*counter);
        return REPEAT;
    }
    return NOT_REPEAT;
}

void MyCleanup(void *param)
{
    int *cleanup_flag = (int *)param;
    if (NULL != cleanup_flag)
    {
        *cleanup_flag = 1;
    }
    printf("  [Cleanup] Task resources cleared.\n");
}

/* --- Test Function Declarations --- */
void TestTaskLifeCycle(void);
void TestTaskTimingAndMatch(void);

int main(void)
{
    printf("--- Starting Task Unit Tests (C89) ---\n");

    TestTaskLifeCycle();
    TestTaskTimingAndMatch();

    printf("\n--- All Task Tests Completed ---\n");
    return 0;
}

/* --- Test Implementations --- */

void TestTaskLifeCycle(void)
{
    int op_data = 1;
    int cleanup_data = 0;
    unsigned int interval = 2;
    task_ty *task = NULL;
    op_status_ty status;
    
    printf("\nTesting Life Cycle (Create, Execute, Destroy):\n");

    /* C89: Declarations are done, now start logic */
    task = TaskCreate(ToggleTask, &op_data, MyCleanup, &cleanup_data, interval);
    assert(NULL != task);
    printf("  TaskCreate: SUCCESS\n");

    status = TaskExecute(task);
    if (REPEAT == status)
    {
        printf("  TaskExecute (1st run): SUCCESS (Returned REPEAT)\n");
    }

    TaskDestroy(task);
    if (1 == cleanup_data)
    {
        printf("  TaskDestroy & Cleanup call: SUCCESS\n");
    }
    else
    {
        printf("  TaskDestroy: FAILURE (Cleanup not called)\n");
    }
}

void TestTaskTimingAndMatch(void)
{
    unsigned int interval = 10;
    time_t start_time;
    time_t t1;
    task_ty *tsk1 = NULL;
    task_ty *tsk2 = NULL;
    
    printf("\nTesting Timing, UID, and Match:\n");

    start_time = time(NULL);
    tsk1 = TaskCreate(ToggleTask, NULL, MyCleanup, NULL, interval);
    tsk2 = TaskCreate(ToggleTask, NULL, MyCleanup, NULL, interval);

    /* 1. Initial Time Check */
    t1 = TaskGetTimeToRun(tsk1);
    if (t1 >= start_time + (time_t)interval)
    {
        printf("  TaskGetTimeToRun: SUCCESS\n");
    }

    /* 2. Update Time Check */
    TaskUpdateTimeToRun(tsk1);
    if (TaskGetTimeToRun(tsk1) == t1 + (time_t)interval)
    {
        printf("  TaskUpdateTimeToRun: SUCCESS\n");
    }

    /* 3. Match Check */
    if (TRUE == TaskIsMatch(tsk1, tsk1) && FALSE == TaskIsMatch(tsk1, tsk2))
    {
        printf("  TaskIsMatch: SUCCESS\n");
    }
    else
    {
        printf("  TaskIsMatch: FAILURE\n");
    }

    TaskDestroy(tsk1);
    TaskDestroy(tsk2);
}
