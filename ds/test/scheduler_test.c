/*-----------------------------------------------------------------------------
submitter : Rozaline Kozly
date : 11 Jan 2026
version : 2
------------------------------------------------------------------------------*/
#include <stdio.h>	/* printf() */
#include <stdlib.h>	/* malloc(), free() */
#include <unistd.h>	/* sleep() */

#include "scheduler.h"

#define SHORT_INTERVAL		2
#define UNUSED(var)		((void)(var))

/*---------------------------global for tracking execution---------------------*/
int g_counter = 0;
int g_exec_order[20] = {0};
size_t g_exec_idx = 0;

/*---------------------------task operations-----------------------------------*/
static sch_op_status_ty IncrementTask(void* param);
static sch_op_status_ty Task1(void* param);
static sch_op_status_ty Task2(void* param);
static sch_op_status_ty Task3(void* param);
static sch_op_status_ty StopTask(void* param);
static sch_op_status_ty StopAfter3(void* param);
static void SimpleCleanup(void* param);

/*-----------------------------------------------------------------------------*/
int main(void)
{
	scheduler_ty* sch = NULL;
	uid_ty uid1 = {0};
	uid_ty uid2 = {0};
	uid_ty uid3 = {0};
	size_t i = 0;
	
	printf("\n----------SCHEDULER TESTS ------------n\n");
	
	/*-----------------Test 1: Create and basic checks-----------------*/
	printf("Test 1: Create scheduler\n");
	sch = SchedulerCreate();
	if (!sch)
	{
		printf("  FAIL: Create returned NULL\n");
		return 1;
	}
	printf("  Size: %lu (expected: 0)\n", (unsigned long)SchedulerSize(sch));
	if (0 == SchedulerSize(sch))
	{
		printf("  PASS: Scheduler created\n\n");
	}
	else
	{
		printf("  FAIL: Size should be 0\n\n");
	}
	
	/*-----------------Test 2: Add tasks-----------------*/
	printf("Test 2: Add tasks\n");
	uid1 = SchedulerAddTask(sch, 5, Task1, NULL, SimpleCleanup, NULL);
	printf("  Added task 1, Size: %lu (expected: 1)\n", 
		(unsigned long)SchedulerSize(sch));
	
	uid2 = SchedulerAddTask(sch, 3, Task2, NULL, SimpleCleanup, NULL);
	printf("  Added task 2, Size: %lu (expected: 2)\n", 
		(unsigned long)SchedulerSize(sch));
	
	uid3 = SchedulerAddTask(sch, 7, Task3, NULL, SimpleCleanup, NULL);
	printf("  Added task 3, Size: %lu (expected: 3)\n", 
		(unsigned long)SchedulerSize(sch));
	
	if (3 == SchedulerSize(sch))
	{
		printf("  PASS: All tasks added correctly\n\n");
	}
	else
	{
		printf("  FAIL: Size should be 3, got %lu\n\n", 
			(unsigned long)SchedulerSize(sch));
	}
	
	/*-----------------Test 3: Remove task-----------------*/
	printf("Test 3: Remove task\n");
	printf("  Removing task 2...\n");
	if (0 == SchedulerRemoveTask(sch, uid2))
	{
		printf("  Size after remove: %lu (expected: 2)\n", 
			(unsigned long)SchedulerSize(sch));
		printf("  PASS: Remove succeeded\n");
	}
	else
	{
		printf("  FAIL: Remove failed\n");
	}
	
	printf("  Trying to remove same task again...\n");
	if (0 != SchedulerRemoveTask(sch, uid2))
	{
		printf("  PASS: Cannot remove same task twice\n\n");
	}
	else
	{
		printf("  FAIL: Should fail on second remove\n\n");
	}
	
	/*-----------------Test 4: Clear-----------------*/
	printf("Test 4: Clear scheduler\n");
	SchedulerClear(sch);
	printf("  Size after clear: %lu (expected: 0)\n", 
		(unsigned long)SchedulerSize(sch));
	if (0 == SchedulerSize(sch))
	{
		printf("  PASS: Clear worked\n\n");
	}
	else
	{
		printf("  FAIL: Should be empty\n\n");
	}
	
	/*-----------------Test 5: Run empty scheduler-----------------*/
	printf("Test 5: Run empty scheduler\n");
	if (SCH_SUCCESS == SchedulerRun(sch))
	{
		printf("  PASS: Run on empty returns SCH_SUCCESS\n\n");
	}
	else
	{
		printf("  FAIL: Should return SCH_SUCCESS\n\n");
	}
	
	/*-----------------Test 6: Basic execution-----------------*/
	printf("Test 6: Basic execution with counter\n");
	g_counter = 0;
	
	SchedulerAddTask(sch, SHORT_INTERVAL, IncrementTask, NULL, 
			 SimpleCleanup, NULL);
	SchedulerAddTask(sch, SHORT_INTERVAL, StopAfter3, sch, 
			 SimpleCleanup, NULL);
	
	printf("  Size before run: %lu (expected: 2)\n", 
		(unsigned long)SchedulerSize(sch));
	printf("  Running scheduler (will increment counter 3 times)...\n");
	
	SchedulerRun(sch);
	
	printf("  Counter value: %d (expected: 3)\n", g_counter);
	printf("  Size after run: %lu\n", (unsigned long)SchedulerSize(sch));
	
	if (3 == g_counter)
	{
		printf("  PASS: Tasks executed correctly\n\n");
	}
	else
	{
		printf("  FAIL: Counter should be 3\n\n");
	}
	
	/*-----------------Test 7: Interval zero (one-time task)-----------------*/
	printf("Test 7: Interval zero (one-time task)\n");
	SchedulerClear(sch);
	g_counter = 0;
	
	SchedulerAddTask(sch, 0, IncrementTask, NULL, SimpleCleanup, NULL);
	SchedulerAddTask(sch, SHORT_INTERVAL, StopTask, sch, 
			 SimpleCleanup, NULL);
	
	printf("  Size before run: %lu (expected: 2)\n", 
		(unsigned long)SchedulerSize(sch));
	
	SchedulerRun(sch);
	
	printf("  Counter: %d (expected: 1)\n", g_counter);
	printf("  Size after run: %lu\n", (unsigned long)SchedulerSize(sch));
	
	if (1 == g_counter)
	{
		printf("  PASS: One-time task executed once only\n\n");
	}
	else
	{
		printf("  FAIL: Task with interval=0 should execute once\n\n");
	}
	
	/*-----------------Test 8: SchedulerStop-----------------*/
	printf("Test 8: SchedulerStop during execution\n");
	SchedulerClear(sch);
	g_counter = 0;
	
	SchedulerAddTask(sch, SHORT_INTERVAL, IncrementTask, NULL, 
			 SimpleCleanup, NULL);
	SchedulerAddTask(sch, SHORT_INTERVAL, StopTask, sch, 
			 SimpleCleanup, NULL);
	
	if (SCH_STOP == SchedulerRun(sch))
	{
		printf("  Return value: SCH_STOP\n");
		printf("  Counter: %d\n", g_counter);
		printf("  Size after stop: %lu\n", (unsigned long)SchedulerSize(sch));
		printf("  PASS: SchedulerStop worked correctly\n\n");
	}
	else
	{
		printf("  FAIL: Should return SCH_STOP\n\n");
	}
	
	/*-----------------Test 9: Multiple tasks timing-----------------*/
	printf("Test 9: Execution order (intervals: 2, 4, 6 seconds)\n");
	SchedulerClear(sch);
	g_exec_idx = 0;
	
	printf("  Task1: interval=2s, writes '1'\n");
	printf("  Task2: interval=4s, writes '2'\n");
	printf("  Task3: interval=6s, writes '3'\n");
	printf("  Will run for ~13 seconds...\n");
	
	SchedulerAddTask(sch, 2, Task1, NULL, SimpleCleanup, NULL);
	SchedulerAddTask(sch, 4, Task2, NULL, SimpleCleanup, NULL);
	SchedulerAddTask(sch, 6, Task3, NULL, SimpleCleanup, NULL);
	
	printf("  Size: %lu (expected: 3)\n", (unsigned long)SchedulerSize(sch));
	printf("  Running...\n");
	
	SchedulerRun(sch);
	
	printf("  Execution order: ");
	for (i = 0; i < g_exec_idx && i < 10; ++i)
	{
		printf("%d ", g_exec_order[i]);
	}
	printf("\n");
	printf("  Total executions: %lu\n", (unsigned long)g_exec_idx);
	
	/* Expected pattern: tasks execute in order based on their next run time */
	/* At t=0: all added. Task1 next at t=2, Task2 at t=4, Task3 at t=6 */
	/* t=2: Task1 runs (1), next at t=4 */
	/* t=4: Task1 runs (1), Task2 runs (2), Task1 next at t=6, Task2 next at t=8 */
	/* t=6: Task1 runs (1), Task3 runs (3), Task1 next at t=8, Task3 next at t=12 */
	/* Expected: 1,1,2,1,3,1,2,1,1,3 */
	
	if (g_exec_idx >= 8)
	{
		printf("  PASS: Multiple tasks executed\n\n");
	}
	else
	{
		printf("  FAIL: Not enough executions\n\n");
	}
	
	/*-----------------Cleanup-----------------*/
	SchedulerDestroy(sch);
	printf("============ ALL TESTS COMPLETED ============\n\n");
	
	return 0;
}
/*-----------------------------------------------------------------------------*/
static sch_op_status_ty IncrementTask(void* param)
{
	UNUSED(param);
	g_counter++;
	return SCH_REPEAT;
}
/*-----------------------------------------------------------------------------*/
static sch_op_status_ty StopAfter3(void* param)
{
	scheduler_ty* sch = (scheduler_ty*)param;
	
	if (g_counter >= 3)
	{
		SchedulerStop(sch);
		return SCH_NOT_REPEAT;
	}
	
	return SCH_REPEAT;
}
/*-----------------------------------------------------------------------------*/
static sch_op_status_ty Task1(void* param)
{
	UNUSED(param);
	
	if (g_exec_idx < 20)
	{
		g_exec_order[g_exec_idx] = 1;
		g_exec_idx++;
	}
	
	if (g_exec_idx >= 10)
	{
		return SCH_NOT_REPEAT;
	}
	
	return SCH_REPEAT;
}
/*-----------------------------------------------------------------------------*/
static sch_op_status_ty Task2(void* param)
{
	UNUSED(param);
	
	if (g_exec_idx < 20)
	{
		g_exec_order[g_exec_idx] = 2;
		g_exec_idx++;
	}
	
	if (g_exec_idx >= 10)
	{
		return SCH_NOT_REPEAT;
	}
	
	return SCH_REPEAT;
}
/*-----------------------------------------------------------------------------*/
static sch_op_status_ty Task3(void* param)
{
	UNUSED(param);
	
	if (g_exec_idx < 20)
	{
		g_exec_order[g_exec_idx] = 3;
		g_exec_idx++;
	}
	
	if (g_exec_idx >= 10)
	{
		return SCH_NOT_REPEAT;
	}
	
	return SCH_REPEAT;
}
/*-----------------------------------------------------------------------------*/
static sch_op_status_ty StopTask(void* param)
{
	scheduler_ty* sch = (scheduler_ty*)param;
	SchedulerStop(sch);
	return SCH_NOT_REPEAT;
}
/*-----------------------------------------------------------------------------*/
static void SimpleCleanup(void* param)
{
	UNUSED(param);
}
/*-----------------------------------------------------------------------------*/
