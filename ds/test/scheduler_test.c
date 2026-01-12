/*-----------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer : ??
version : 1
date : 7 Jan 2026
------------------------------------------------------------------------------*/
/******************************************************************************
* Scheduler tests
* C89 compliant
******************************************************************************/

#include <stdio.h>      /* printf */
#include <unistd.h>    /* sleep */
#include <assert.h>

#include "scheduler.h"

/******************************************************************************/
/* test helpers */

static sch_op_status_ty PrintTask(void *param)
{
    const char *msg = (const char *)param;
    printf("Task running: %s\n", msg);
    return SCH_REPEAT;
}

static sch_op_status_ty OneShotTask(void *param)
{
    const char *msg = (const char *)param;
    printf("One shot task: %s\n", msg);
    return SCH_NOT_REPEAT;
}

static sch_op_status_ty StopSchedulerTask(void *param)
{
    scheduler_ty *sch = (scheduler_ty *)param;
    printf("Stopping scheduler from task\n");
    SchedulerStop(sch);
    return SCH_NOT_REPEAT;
}

static void Cleanup(void *param)
{
    (void)param;
    printf("Cleanup called\n");
}

/******************************************************************************/
/* basic tests */

static void TestCreateDestroy(void)
{
    scheduler_ty *sch = SchedulerCreate();
    assert(NULL != sch);
    SchedulerDestroy(sch);
    printf("TestCreateDestroy passed\n");
}

static void TestAddAndSize(void)
{
    scheduler_ty *sch = SchedulerCreate();
    uid_ty uid;

    uid = SchedulerAddTask(sch, 1, PrintTask, "A", Cleanup, NULL);
    assert(!IsMatchId(uid, invalid_uid_g));
    assert(1 == SchedulerSize(sch));

    SchedulerDestroy(sch);
    printf("TestAddAndSize passed\n");
}

static void TestRemoveTask(void)
{
    scheduler_ty *sch = SchedulerCreate();
    uid_ty uid;

    uid = SchedulerAddTask(sch, 1, PrintTask, "ToRemove", Cleanup, NULL);
    assert(1 == SchedulerSize(sch));

    SchedulerRemoveTask(sch, uid);
    assert(0 == SchedulerSize(sch));

    SchedulerDestroy(sch);
    printf("TestRemoveTask passed\n");
}

/******************************************************************************/
/* demo usage */

static void DemoSchedulerUsage(void)
{
    scheduler_ty *sch = SchedulerCreate();

    printf("\n--- Scheduler demo start ---\n");

    SchedulerAddTask(sch, 1, PrintTask, "Repeating every 1 sec", Cleanup, NULL);
    SchedulerAddTask(sch, 2, PrintTask, "Repeating every 2 sec", Cleanup, NULL);
    SchedulerAddTask(sch, 3, OneShotTask, "Runs once", Cleanup, NULL);
    SchedulerAddTask(sch, 5, StopSchedulerTask, sch, Cleanup, NULL);

    SchedulerRun(sch);

    printf("--- Scheduler demo end ---\n\n");

    SchedulerDestroy(sch);
}

/******************************************************************************/

int main(void)
{
    printf("Running scheduler tests...\n\n");

    TestCreateDestroy();
    TestAddAndSize();
    TestRemoveTask();

    DemoSchedulerUsage();

    printf("All tests finished successfully\n");
    return 0;
}

