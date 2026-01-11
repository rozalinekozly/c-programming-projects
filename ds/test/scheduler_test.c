/*-----------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer: Itay
date : 11 Jan 2026
version : 1
------------------------------------------------------------------------------*/
#include <stdio.h>	/* printf() */
#include <stdlib.h>	/* malloc(), free() */

#include "scheduler.h"
#include "uid.h"

#define TEST_INTERVAL		5
#define SHORT_INTERVAL		1
#define NUM_BASE_TASKS		3
#define EXEC_ORDER_LEN		15
#define UNUSED(var)		((void)(var))

/*---------------------------test functions------------------------------------*/
static void TestCreate(void);
static void TestAddTask(void);
static void TestRemoveTask(void);
static void TestSchedulerRun(void);
static void TestRunEmpty(void);
static void TestIntervalZero(void);
static void TestExecOrder(void);
static void TestOperations(void);
/*---------------------------task operations-----------------------------------*/
static sch_op_status_ty IncrementOp(void* param);
static void IncrementCleanup(void* param);
static void NoCleanup(void* param);
static sch_op_status_ty StopOp(void* param);
static sch_op_status_ty ExecOrderOp(void* param);
static sch_op_status_ty AddTaskOp(void* param);
static sch_op_status_ty RemoveTaskOp(void* param);
static sch_op_status_ty IsEmptyOp(void* param);
static sch_op_status_ty SizeOp(void* param);
static sch_op_status_ty ClearOp(void* param);
/*---------------------------helper structs------------------------------------*/
typedef struct exec_order_param
{
	int* actual;
	size_t* idx;
	int value;
	scheduler_ty* sch;
}exec_order_param_ty;

typedef struct add_task_param
{
	scheduler_ty* sch;
	unsigned int interval;
	scheduler_op_ty op_func;
	void* op_param;
	scheduler_cleanup_ty clean_func;
	void* clean_param;
	uid_ty* result_uid;	
}add_task_param_ty;

typedef struct remove_task_param
{
	scheduler_ty* sch;
	int* removed;
	uid_ty* uid_to_remove;	
}remove_task_param_ty;

typedef struct is_empty_param
{
	scheduler_ty* sch;
	int* result;	
}is_empty_param_ty;

typedef struct size_param
{
	scheduler_ty* sch;
	size_t* result;	
}size_param_ty;

/*-----------------------------------------------------------------------------*/
int main(void)
{
	printf("\n========== SCHEDULER TESTS ==========\n\n");
	
	TestCreate();
	TestAddTask();
	TestRemoveTask();
	TestSchedulerRun();
	TestRunEmpty();
	TestIntervalZero();
	TestExecOrder();
	TestOperations();
	
	printf("\n========== ALL TESTS COMPLETED ==========\n\n");
	
	return 0;
}
/*-----------------------------------------------------------------------------*/
static void TestCreate(void)
{
	scheduler_ty* sch = NULL;
	
	printf("Testing SchedulerCreate...\n");
	
	sch = SchedulerCreate();
	if (!sch)
	{
		printf("  FAIL: SchedulerCreate returned NULL\n");
		return;
	}
	
	if (0 != SchedulerSize(sch))
	{
		printf("  FAIL: Size should be 0, got %lu\n", 
			(unsigned long)SchedulerSize(sch));
	}
	else
	{
		printf("  PASS: Size is 0\n");
	}
	
	if (!SchedulerIsEmpty(sch))
	{
		printf("  FAIL: Scheduler should be empty\n");
	}
	else
	{
		printf("  PASS: Scheduler is empty\n");
	}
	
	SchedulerDestroy(sch);
	printf("  PASS: Create/Destroy successful\n\n");
}
/*-----------------------------------------------------------------------------*/
static void TestAddTask(void)
{
	scheduler_ty* sch = NULL;
	uid_ty uid = invalid_uid_g;
	int* counter = NULL;
	
	printf("Testing SchedulerAddTask...\n");
	
	counter = (int*)malloc(sizeof(*counter));
	if (!counter)
	{
		printf("  FAIL: malloc failed\n");
		return;
	}
	*counter = 0;
	
	sch = SchedulerCreate();
	if (!sch)
	{
		free(counter);
		printf("  FAIL: SchedulerCreate failed\n");
		return;
	}
	
	uid = SchedulerAddTask(sch, TEST_INTERVAL, IncrementOp, counter, 
				IncrementCleanup, counter);
	
	if (IsMatchId(invalid_uid_g, uid))
	{
		printf("  FAIL: AddTask returned invalid UID\n");
	}
	else
	{
		printf("  PASS: AddTask returned valid UID\n");
	}
	
	if (1 != SchedulerSize(sch))
	{
		printf("  FAIL: Size should be 1, got %lu\n", 
			(unsigned long)SchedulerSize(sch));
	}
	else
	{
		printf("  PASS: Size is 1\n");
	}
	
	if (SchedulerIsEmpty(sch))
	{
		printf("  FAIL: Scheduler should not be empty\n");
	}
	else
	{
		printf("  PASS: Scheduler is not empty\n");
	}
	
	SchedulerDestroy(sch);
	printf("  PASS: AddTask test complete\n\n");
}
/*-----------------------------------------------------------------------------*/
static void TestRemoveTask(void)
{
	scheduler_ty* sch = NULL;
	uid_ty uids[NUM_BASE_TASKS] = {invalid_uid_g};
	size_t i = 0;
	
	printf("Testing SchedulerRemoveTask...\n");
	
	sch = SchedulerCreate();
	if (!sch)
	{
		printf("  FAIL: SchedulerCreate failed\n");
		return;
	}
	
	/* add tasks with different intervals */
	for (i = 0; i < NUM_BASE_TASKS; ++i)
	{
		uids[i] = SchedulerAddTask(sch, TEST_INTERVAL * (i + 1), 
					   IncrementOp, NULL, NoCleanup, NULL);
	}
	
	if (NUM_BASE_TASKS != SchedulerSize(sch))
	{
		printf("  FAIL: Expected size %d, got %lu\n", NUM_BASE_TASKS,
			(unsigned long)SchedulerSize(sch));
	}
	else
	{
		printf("  PASS: Added %d tasks\n", NUM_BASE_TASKS);
	}
	
	/* remove middle task */
	if (0 != SchedulerRemoveTask(sch, uids[1]))
	{
		printf("  FAIL: Failed to remove middle task\n");
	}
	else
	{
		printf("  PASS: Removed middle task\n");
	}
	
	if (NUM_BASE_TASKS - 1 != SchedulerSize(sch))
	{
		printf("  FAIL: Size after remove should be %d, got %lu\n", 
			NUM_BASE_TASKS - 1, (unsigned long)SchedulerSize(sch));
	}
	
	/* try to remove same task again - should fail */
	if (0 == SchedulerRemoveTask(sch, uids[1]))
	{
		printf("  FAIL: Should fail removing already removed task\n");
	}
	else
	{
		printf("  PASS: Cannot remove same task twice\n");
	}
	
	/* remove remaining tasks */
	SchedulerRemoveTask(sch, uids[0]);
	SchedulerRemoveTask(sch, uids[2]);
	
	if (!SchedulerIsEmpty(sch))
	{
		printf("  FAIL: Scheduler should be empty\n");
	}
	else
	{
		printf("  PASS: All tasks removed\n");
	}
	
	SchedulerDestroy(sch);
	printf("  PASS: RemoveTask test complete\n\n");
}
/*-----------------------------------------------------------------------------*/
static void TestSchedulerRun(void)
{
	scheduler_ty* sch = NULL;
	int counter = 0;
	
	printf("Testing SchedulerRun...\n");
	
	sch = SchedulerCreate();
	if (!sch)
	{
		printf("  FAIL: SchedulerCreate failed\n");
		return;
	}
	
	/* add increment task */
	SchedulerAddTask(sch, SHORT_INTERVAL, IncrementOp, &counter, 
			 NoCleanup, NULL);
	/* add stop task */
	SchedulerAddTask(sch, SHORT_INTERVAL, StopOp, sch, NoCleanup, NULL);
	
	if (SCH_STOP != SchedulerRun(sch))
	{
		printf("  FAIL: Run should return SCH_STOP\n");
	}
	else
	{
		printf("  PASS: SchedulerRun returned SCH_STOP\n");
	}
	
	if (1 != counter)
	{
		printf("  FAIL: Counter should be 1, got %d\n", counter);
	}
	else
	{
		printf("  PASS: Task executed once\n");
	}
	
	/* increment task should still be in scheduler */
	if (SchedulerIsEmpty(sch))
	{
		printf("  FAIL: Scheduler should not be empty\n");
	}
	else
	{
		printf("  PASS: Remaining task in scheduler\n");
	}
	
	SchedulerClear(sch);
	if (!SchedulerIsEmpty(sch))
	{
		printf("  FAIL: Scheduler should be empty after clear\n");
	}
	else
	{
		printf("  PASS: SchedulerClear worked\n");
	}
	
	SchedulerDestroy(sch);
	printf("  PASS: SchedulerRun test complete\n\n");
}
/*-----------------------------------------------------------------------------*/
static void TestRunEmpty(void)
{
	scheduler_ty* sch = NULL;
	
	printf("Testing SchedulerRun on empty scheduler...\n");
	
	sch = SchedulerCreate();
	if (!sch)
	{
		printf("  FAIL: SchedulerCreate failed\n");
		return;
	}
	
	if (SCH_SUCCESS != SchedulerRun(sch))
	{
		printf("  FAIL: Empty run should return SCH_SUCCESS\n");
	}
	else
	{
		printf("  PASS: Empty run returned SCH_SUCCESS\n");
	}
	
	if (!SchedulerIsEmpty(sch))
	{
		printf("  FAIL: Scheduler should still be empty\n");
	}
	else
	{
		printf("  PASS: Scheduler still empty after run\n");
	}
	
	SchedulerDestroy(sch);
	printf("  PASS: RunEmpty test complete\n\n");
}
/*-----------------------------------------------------------------------------*/
static void TestIntervalZero(void)
{
	scheduler_ty* sch = NULL;
	int counter = 0;
	
	printf("Testing interval=0 (one-time task)...\n");
	
	sch = SchedulerCreate();
	if (!sch)
	{
		printf("  FAIL: SchedulerCreate failed\n");
		return;
	}
	
	/* add task with interval 0 */
	SchedulerAddTask(sch, 0, IncrementOp, &counter, NoCleanup, NULL);
	/* add stop task */
	SchedulerAddTask(sch, SHORT_INTERVAL, StopOp, sch, NoCleanup, NULL);
	
	if (SCH_STOP != SchedulerRun(sch))
	{
		printf("  FAIL: Run should return SCH_STOP\n");
	}
	
	if (1 != counter)
	{
		printf("  FAIL: Counter should be 1 (one-time), got %d\n", counter);
	}
	else
	{
		printf("  PASS: One-time task executed once\n");
	}
	
	if (!SchedulerIsEmpty(sch))
	{
		printf("  FAIL: Scheduler should be empty\n");
	}
	else
	{
		printf("  PASS: One-time task not rescheduled\n");
	}
	
	SchedulerDestroy(sch);
	printf("  PASS: IntervalZero test complete\n\n");
}
/*-----------------------------------------------------------------------------*/
static void TestExecOrder(void)
{
	scheduler_ty* sch = NULL;
	exec_order_param_ty* params[NUM_BASE_TASKS] = {NULL};
	int expected[EXEC_ORDER_LEN] = {1, 1, 2, 1, 1, 3, 1, 2, 1, 1, 1, 2, 1, 3, 1};
	int actual[EXEC_ORDER_LEN] = {0};
	size_t shared_idx = 0;
	size_t i = 0;
	int interval = 1;
	int all_match = 1;
	
	printf("Testing execution order...\n");
	
	sch = SchedulerCreate();
	if (!sch)
	{
		printf("  FAIL: SchedulerCreate failed\n");
		return;
	}
	
	/* initialize params */
	for (i = 0; i < NUM_BASE_TASKS; ++i)
	{
		params[i] = (exec_order_param_ty*)malloc(sizeof(*params[i]));
		if (!params[i])
		{
			printf("  FAIL: malloc failed\n");
			while (i > 0)
			{
				free(params[--i]);
			}
			SchedulerDestroy(sch);
			return;
		}
		
		params[i]->actual = actual;
		params[i]->value = i + 1;
		params[i]->idx = &shared_idx;
		params[i]->sch = sch;
		
		SchedulerAddTask(sch, interval, ExecOrderOp, params[i], 
				 NoCleanup, NULL);
		interval += 2;
	}
	
	SchedulerRun(sch);
	
	/* verify execution order */
	for (i = 0; i < EXEC_ORDER_LEN; ++i)
	{
		if (expected[i] != actual[i])
		{
			printf("  FAIL: Position %lu expected %d, got %d\n", 
				(unsigned long)i, expected[i], actual[i]);
			all_match = 0;
		}
	}
	
	if (all_match)
	{
		printf("  PASS: Execution order correct\n");
	}
	
	SchedulerDestroy(sch);
	
	for (i = 0; i < NUM_BASE_TASKS; ++i)
	{
		free(params[i]);
	}
	
	printf("  PASS: ExecOrder test complete\n\n");
}
/*-----------------------------------------------------------------------------*/
static void TestOperations(void)
{
	scheduler_ty* sch = NULL;
	int counter = 0;
	uid_ty new_uid = invalid_uid_g;
	uid_ty to_remove = invalid_uid_g;
	uid_ty remove_self = invalid_uid_g;
	int removed = 0;
	int self_removed = 0;
	int is_empty = 0;
	size_t size = 0;
	
	add_task_param_ty add_param = {0};
	remove_task_param_ty remove_param = {0};
	remove_task_param_ty self_param = {0};
	is_empty_param_ty empty_param = {0};
	size_param_ty size_param = {0};
	
	printf("Testing operations during run...\n");
	
	sch = SchedulerCreate();
	if (!sch)
	{
		printf("  FAIL: SchedulerCreate failed\n");
		return;
	}
	
	/* add counter task */
	to_remove = SchedulerAddTask(sch, SHORT_INTERVAL, IncrementOp, 
				      &counter, NoCleanup, NULL);
	
	/* setup add task operation */
	add_param.sch = sch;
	add_param.interval = SHORT_INTERVAL;
	add_param.op_func = IncrementOp;
	add_param.op_param = &counter;
	add_param.clean_func = NoCleanup;
	add_param.clean_param = NULL;
	add_param.result_uid = &new_uid;
	SchedulerAddTask(sch, SHORT_INTERVAL, AddTaskOp, &add_param, 
			 NoCleanup, NULL);
	
	/* setup remove task operation */
	remove_param.sch = sch;
	remove_param.removed = &removed;
	remove_param.uid_to_remove = &to_remove;
	SchedulerAddTask(sch, SHORT_INTERVAL, RemoveTaskOp, &remove_param, 
			 NoCleanup, NULL);
	
	/* setup remove self operation */
	self_param.sch = sch;
	self_param.removed = &self_removed;
	self_param.uid_to_remove = &remove_self;
	remove_self = SchedulerAddTask(sch, SHORT_INTERVAL, RemoveTaskOp, 
				       &self_param, NoCleanup, NULL);
	
	/* setup is empty operation */
	empty_param.sch = sch;
	empty_param.result = &is_empty;
	SchedulerAddTask(sch, SHORT_INTERVAL, IsEmptyOp, &empty_param, 
			 NoCleanup, NULL);
	
	/* setup size operation */
	size_param.sch = sch;
	size_param.result = &size;
	SchedulerAddTask(sch, SHORT_INTERVAL, SizeOp, &size_param, 
			 NoCleanup, NULL);
	
	/* add clear operation */
	SchedulerAddTask(sch, SHORT_INTERVAL, ClearOp, sch, NoCleanup, NULL);
	
	/* add stop operation (should not execute) */
	SchedulerAddTask(sch, SHORT_INTERVAL, StopOp, sch, NoCleanup, NULL);
	
	if (SCH_SUCCESS != SchedulerRun(sch))
	{
		printf("  FAIL: Should return SCH_SUCCESS after clear\n");
	}
	else
	{
		printf("  PASS: Returned SCH_SUCCESS\n");
	}
	
	if (1 != counter)
	{
		printf("  FAIL: Counter should be 1, got %d\n", counter);
	}
	else
	{
		printf("  PASS: Counter incremented once\n");
	}
	
	if (IsMatchId(new_uid, invalid_uid_g))
	{
		printf("  FAIL: AddTask should return valid UID\n");
	}
	else
	{
		printf("  PASS: AddTask worked during run\n");
	}
	
	if (0 != removed)
	{
		printf("  FAIL: RemoveTask should succeed (return 0)\n");
	}
	else
	{
		printf("  PASS: RemoveTask worked\n");
	}
	
	if (0 != self_removed)
	{
		printf("  FAIL: Remove self should succeed\n");
	}
	else
	{
		printf("  PASS: Remove self worked\n");
	}
	
	if (is_empty)
	{
		printf("  FAIL: IsEmpty should be false during run\n");
	}
	else
	{
		printf("  PASS: IsEmpty returned false\n");
	}
	
	if (7 != size)
	{
		printf("  FAIL: Size should be 7, got %lu\n", (unsigned long)size);
	}
	else
	{
		printf("  PASS: Size was 7\n");
	}
	
	if (!SchedulerIsEmpty(sch))
	{
		printf("  FAIL: Scheduler should be empty after clear\n");
	}
	else
	{
		printf("  PASS: Clear worked\n");
	}
	
	SchedulerDestroy(sch);
	printf("  PASS: Operations test complete\n\n");
}
/*-----------------------------------------------------------------------------*/
static sch_op_status_ty IncrementOp(void* param)
{
	int* counter = (int*)param;
	if (counter)
	{
		*counter += 1;
	}
	return SCH_REPEAT;
}
/*-----------------------------------------------------------------------------*/
static void IncrementCleanup(void* param)
{
	free(param);
}
/*-----------------------------------------------------------------------------*/
static void NoCleanup(void* param)
{
	UNUSED(param);
}
/*-----------------------------------------------------------------------------*/
static sch_op_status_ty StopOp(void* param)
{
	SchedulerStop((scheduler_ty*)param);
	return SCH_NOT_REPEAT;
}
/*-----------------------------------------------------------------------------*/
static sch_op_status_ty ExecOrderOp(void* param)
{
	exec_order_param_ty* p = (exec_order_param_ty*)param;
	
	*(p->actual + *p->idx) = p->value;
	*p->idx += 1;
	
	if (*p->idx >= EXEC_ORDER_LEN)
	{
		SchedulerStop(p->sch);
		return SCH_NOT_REPEAT;
	}
	
	return SCH_REPEAT;
}
/*-----------------------------------------------------------------------------*/
static sch_op_status_ty AddTaskOp(void* param)
{
	add_task_param_ty* p = (add_task_param_ty*)param;
	
	*p->result_uid = SchedulerAddTask(p->sch, p->interval, p->op_func, 
					  p->op_param, p->clean_func, 
					  p->clean_param);
	
	return SCH_REPEAT;
}
/*-----------------------------------------------------------------------------*/
static sch_op_status_ty RemoveTaskOp(void* param)
{
	remove_task_param_ty* p = (remove_task_param_ty*)param;
	
	*p->removed = SchedulerRemoveTask(p->sch, *p->uid_to_remove);
	
	return SCH_REPEAT;
}
/*-----------------------------------------------------------------------------*/
static sch_op_status_ty IsEmptyOp(void* param)
{
	is_empty_param_ty* p = (is_empty_param_ty*)param;
	
	*p->result = SchedulerIsEmpty(p->sch);
	
	return SCH_REPEAT;
}
/*-----------------------------------------------------------------------------*/
static sch_op_status_ty SizeOp(void* param)
{
	size_param_ty* p = (size_param_ty*)param;
	
	*p->result = SchedulerSize(p->sch);
	
	return SCH_REPEAT;
}
/*-----------------------------------------------------------------------------*/
static sch_op_status_ty ClearOp(void* param)
{
	SchedulerClear((scheduler_ty*)param);
	
	return SCH_REPEAT;
}
/*-----------------------------------------------------------------------------*/
