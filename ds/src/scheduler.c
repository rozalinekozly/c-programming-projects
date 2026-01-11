/******************************************************************************
* Scheduler implementation
* C89 compliant
******************************************************************************/

#include <stdlib.h>     /* malloc, free */
#include <assert.h>     /* assert */
#include <time.h>       /* time */
#include <unistd.h>     /* sleep */

#include "scheduler.h"
#include "pqueue.h"
#include "task.h"
#include "uid.h"

/* deferred operations flags */
typedef enum op_flag
{
    OP_NONE = 0,
    OP_REMOVE = 1,
    OP_CLEAR = 2
} op_flag_ty;

/* scheduler running state */
typedef enum sch_running_bool
{
    SCH_FALSE = 0,
    SCH_TRUE = 1
} sch_running_bool_ty;

struct scheduler
{
    pq_ty *pq;
    sch_running_bool_ty is_running;
    uid_ty cur_task;
    op_flag_ty op_flag;
};

/* helpers */
static int TaskCmpTime(const void *data1, const void *data2, void *param);
static int TaskMatchUid(const void *data, void *param);

/******************************************************************************/

scheduler_ty *SchedulerCreate(void)
{
    scheduler_ty *sch = (scheduler_ty *)malloc(sizeof(scheduler_ty));
    if (NULL == sch)
    {
        return NULL;
    }

    sch->pq = PQCreate(TaskCmpTime, NULL);
    if (NULL == sch->pq)
    {
        free(sch);
        return NULL;
    }

    sch->is_running = SCH_FALSE;
    sch->cur_task = invalid_uid_g;
    sch->op_flag = OP_NONE;

    return sch;
}

/******************************************************************************/

void SchedulerDestroy(scheduler_ty *sch)
{
    if (NULL == sch)
    {
        return;
    }

    SchedulerClear(sch);
    PQDestroy(sch->pq);
    free(sch);
}

/******************************************************************************/

uid_ty SchedulerAddTask(scheduler_ty *sch,
                        unsigned int interval,
                        scheduler_op_ty op_func,
                        void *op_param,
                        scheduler_cleanup_ty clean_func,
                        void *clean_param)
{
    task_ty *task = NULL;

    assert(NULL != sch);
    assert(NULL != op_func);
    assert(NULL != clean_func);

    task = TaskCreate((task_op_ty)op_func,
                      op_param,
                      (task_cleanup_ty)clean_func,
                      clean_param,
                      interval);
    if (NULL == task)
    {
        return invalid_uid_g;
    }

    if (PQ_FAIL == PQEnqueue(sch->pq, task))
    {
        TaskDestroy(task);
        return invalid_uid_g;
    }

    return TaskGetUID(task);
}

/******************************************************************************/

int SchedulerRemoveTask(scheduler_ty *sch, uid_ty task_id)
{
    task_ty *task = NULL;

    assert(NULL != sch);
    assert(!IsMatchId(invalid_uid_g, task_id));

    if (IsMatchId(task_id, sch->cur_task) && OP_CLEAR != sch->op_flag)
    {
        sch->op_flag = OP_REMOVE;
        return SCH_SUCCESS;
    }

    task = (task_ty *)PQRemove(sch->pq, TaskMatchUid, &task_id);
    if (NULL == task)
    {
        return SCH_FAIL;
    }

    TaskDestroy(task);
    return SCH_SUCCESS;
}

/******************************************************************************/

size_t SchedulerSize(const scheduler_ty *sch)
{
    size_t size = 0;

    assert(NULL != sch);

    size = PQCount(sch->pq);
    if (SCH_TRUE == sch->is_running)
    {
        ++size;
    }

    return size;
}

/******************************************************************************/

sch_run_status_ty SchedulerRun(scheduler_ty *sch)
{
    task_ty *task = NULL;
    task_op_status_ty task_status = TSK_REPEAT;
    time_t now = 0;
    time_t wait_time = 0;

    assert(NULL != sch);

    sch->is_running = SCH_TRUE;

    while (sch->is_running && PQ_FALSE == PQIsEmpty(sch->pq))
    {
        now = time(NULL);
        if ((time_t)-1 == now)
        {
            sch->is_running = SCH_FALSE;
            return SCH_FAIL;
        }

        task = (task_ty *)PQDequeue(sch->pq);
        sch->cur_task = TaskGetUID(task);

        wait_time = TaskGetTimeToRun(task) - now;
        while (wait_time > 0)
        {
            wait_time = sleep(wait_time);
        }

        task_status = TaskExecute(task);

        if (SCH_FALSE == sch->is_running && OP_CLEAR != sch->op_flag)
        {
            TaskDestroy(task);
            return SCH_STOP;
        }
        else if (OP_CLEAR == sch->op_flag)
        {
            TaskDestroy(task);
            break;
        }
        else if (TSK_NOT_REPEAT == task_status || OP_REMOVE == sch->op_flag)
        {
            sch->op_flag = OP_NONE;
            TaskDestroy(task);
        }
        else
        {
            TaskUpdateTimeToRun(task);
            if (PQ_FAIL == PQEnqueue(sch->pq, task))
            {
                TaskDestroy(task);
                sch->is_running = SCH_FALSE;
                return SCH_FAIL;
            }
        }
    }

    if (OP_CLEAR == sch->op_flag)
    {
        sch->op_flag = OP_NONE;
        sch->is_running = SCH_FALSE;
        SchedulerClear(sch);
        return SCH_SUCCESS;
    }

    sch->is_running = SCH_FALSE;

    if (PQ_FALSE == PQIsEmpty(sch->pq))
    {
        return SCH_STOP;
    }

    return SCH_SUCCESS;
}

/******************************************************************************/

void SchedulerStop(scheduler_ty *sch)
{
    assert(NULL != sch);
    sch->is_running = SCH_FALSE;
}

/******************************************************************************/

void SchedulerClear(scheduler_ty *sch)
{
    assert(NULL != sch);

    if (SCH_TRUE == sch->is_running)
    {
        sch->is_running = SCH_FALSE;
        sch->op_flag = OP_CLEAR;
        return;
    }

    while (PQ_FALSE == PQIsEmpty(sch->pq))
    {
        TaskDestroy((task_ty *)PQDequeue(sch->pq));
    }
}

/******************************************************************************/

static int TaskCmpTime(const void *data1, const void *data2, void *param)
{
    task_ty *t1 = (task_ty *)data1;
    task_ty *t2 = (task_ty *)data2;
    (void)param;

    return (int)difftime(TaskGetTimeToRun(t1), TaskGetTimeToRun(t2));
}

static int TaskMatchUid(const void *data, void *param)
{
    return IsMatchId(TaskGetUID((task_ty *)data), *(uid_ty *)param);
}

