/*--------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer  : 
worksheet : 12 (ds - stack)
version   : 1
date      : 9 Dec 2025
stage     : pre-review
----------------------------------------------------------------------------*/
#include "../include/stack.h"
#include <stdlib.h>			/* malloc(), free() */
#include <string.h>			/* memmove() */
struct stack_s
{
	size_t capacity;
	size_t element_size;
	size_t stk_size;
	char stk[1];		/* flexible array c89 */
};

typedef enum
{
	FALSE = 0,
	TRUE = 1
}bool_ty;

stack_ty* StackCreate(size_t capacity, size_t element_size)
{
	stack_ty* stk_p = NULL;
	
	stk_p = (stack_ty*)malloc(sizeof(stack_ty) + capacity * element_size);
	stk_p -> capacity = capacity;
	stk_p -> element_size = element_size;
	stk_p -> stk_size = 0;
	
	return stk_p;
}

void StackDestroy(stack_ty* stack_p)
{
	if(NULL != stack_p)
	{
     		free(stack_p);
     		stack_p = NULL;
	}
}

void StackPush(stack_ty* stack_p, void* new_element)
{
	 /*stack_p -> stk[stack_p -> stk_size] = new_element;
	 ++(stack_p -> stk_size);*/
	memmove(stack_p -> stk + stack_p -> stk_size, new_element, stack_p -> element_size);
	++stack_p->stk_size;
}

void* StackPeek(const stack_ty* stack_p)
{
      return (void*)(stack_p-> stk + (stack_p->stk_size - 1));
	/*return (void*)(stack_p -> stk[(stack_p -> stk_size) - 1]);*/
}

void StackPop(stack_ty* stack_p)
{
	--(stack_p -> stk_size);
}

size_t StackSize(const stack_ty* stack_p)
{
	return (stack_p -> stk_size);
}

int StackIsEmpty(const stack_ty* stack_p)
{
	if(0 == StackSize(stack_p))
	{
		return TRUE;
	}
	return FALSE;
}

size_t StackCapacity(const stack_ty* stack_p)
{
	return (stack_p -> capacity);
}

