/*-----------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer : Itay
version : 1
date : 6 Jan 2026
------------------------------------------------------------------------------*/
#include <assert.h>	/*assert()*/
#include <stdlib.h>	/*malloc(), free()*/
#include <time.h> 	/*time()*/

#include "uid.h"
#include "task.h"
/*-----------------------------------------------------------------------------*/
struct task
{
    uid_ty uid;
    task_op_ty op;
    void* op_param;
    task_cleanup_ty cl;
    void* cl_param;
    unsigned int interval;
    time_t time_to_run;
};

/*-----------------------------------------------------------------------------*/
task_ty* TaskCreate(task_op_ty op, void* op_param, task_cleanup_ty cl, void*
		    cl_param, unsigned int interval)
{
	task_ty* new_tsk = {0};
	time_t curr_time = 0;
	
	assert(NULL != op);
	assert(NULL != cl);
	
	curr_time = time(NULL);
	if((time_t)-1 == curr_time)
	{
		return NULL;
	}
	
	new_tsk = (task_ty*)malloc(sizeof(task_ty)*sizeof(char));
	if(NULL == new_tsk)
	{
		return NULL;
	}
	
	new_tsk->uid = UidCreate();
	if(IsMatchId(invalid_uid_g,new_tsk->uid))
	{
		free(new_tsk);
		new_tsk = NULL;
		return NULL;
	}
	new_tsk->op = op;
	new_tsk->op_param = op_param;
	new_tsk->cl = cl;
	new_tsk->cl_param = cl_param;
	new_tsk->interval = interval;
	/* check if there is a add function in time header, so it be defined units */
	new_tsk->time_to_run = curr_time + (time_t)interval;
	
	return (new_tsk);
}
/*-----------------------------------------------------------------------------*/
task_op_status_ty TaskExecute(task_ty* tsk)
{
	assert(NULL != tsk);
	
	return(tsk->op(tsk->op_param));
}
/*-----------------------------------------------------------------------------*/
void TaskUpdateTimeToRun(task_ty* tsk)
{
    assert(NULL != tsk);
    tsk->time_to_run += (time_t)tsk->interval;
}
/*-----------------------------------------------------------------------------*/
void TaskDestroy(task_ty* tsk)
{
	if(NULL == tsk)
	{
		return;
	}
	tsk->cl(tsk->cl_param);
	free(tsk);
	tsk = NULL;
}
/*-----------------------------------------------------------------------------*/
/* turn this into inline function */

uid_ty TaskGetUID(const task_ty* tsk)
{
	assert(NULL != tsk);
	
	return(tsk->uid);
}
/* turn this into inline function */
time_t TaskGetTimeToRun(const task_ty* tsk)
{
	assert(NULL != tsk);
	
	return(tsk->time_to_run);
}

task_bool_ty TaskIsMatch(const task_ty* tsk1, const task_ty* tsk2)
{
    assert(NULL != tsk1);
    assert(NULL != tsk2);

    return IsMatchId(tsk1->uid, tsk2->uid);
}
