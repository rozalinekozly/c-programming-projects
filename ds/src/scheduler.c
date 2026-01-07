/*-----------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer : ??
version : 1
date : 7 Jan 2026
------------------------------------------------------------------------------*/
#include <pqueue.h>
#include <uid.h>
#include <task.h>

typedef enum
{
	NONE = 0,
	RMV = 1,
	CLR = 2
}special_op_ty;

struct scheduler
{
	pq_ty* pq;
	uid_ty curr_uid;
	special_op_ty sp_op;  /* none, remove, clear*/
};

