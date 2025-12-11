/*--------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer  : steve
worksheet : 12 (ds - stack)
version   : 1
date      : 10 Dec 2025
stage     : post-testing
----------------------------------------------------------------------------*/
#include <stdlib.h>			/* malloc(), free() */
#include <string.h>			/* memcpy() */
#include <assert.h>			/* assert() */
#include "../include/stack.h"

/* shortcuts, used for created stacks pointers of name "stack_p" */
#define CURRENT_EMPTY_PLACEMENT_IN_STK		      ((stack_p -> stack) + (stack_p -> stack_size * stack_p -> element_size))
#define NUMBER_OF_ELEMENTS_IN_STK			      (stack_p -> stack_size )
#define FULL_CAPACITY_STK					(stack_p -> stack_size == stack_p -> capacity)
#define CURRENT_ELEMENT_IN_STK				(stack_p -> stack + (stack_p-> stack_size - 1) * stack_p -> element_size)

struct stack_s
{
	/*holds maximum number of elements the stack can hold*/
	size_t capacity;	
	/*holds size per element, all elements share same size*/
	size_t element_size;
	/*holds number of elements within the stack at each point in time*/
	size_t stack_size;
      /*flexible array c89, this is the stack! */
	char stack[1];		
};

typedef enum
{
	FALSE = 0,
	TRUE = 1
}bool_ty;


stack_ty* StackCreate(size_t capacity, size_t element_size)
{
	stack_ty* stack_p = NULL;
	
	/* already have 1 block in stack, so just malloc extra (capacity - 1) */
	stack_p = malloc(sizeof(stack_ty) + (capacity - 1) * element_size);

	if (NULL == stack_p)
	{
		return NULL;
	}
	stack_p -> capacity = capacity;
	stack_p -> element_size = element_size;
	NUMBER_OF_ELEMENTS_IN_STK = 0;
	
	return stack_p;
}

void StackDestroy(stack_ty* stack_p)
{
	
      if (NULL != stack_p)
	{   
     		free(stack_p);
     		stack_p = NULL;
	}
}

void StackPush(stack_ty* stack_p, void* new_element)
{
	assert(NULL != stack_p);
	assert(!FULL_CAPACITY_STK);
	memcpy(CURRENT_EMPTY_PLACEMENT_IN_STK, new_element, stack_p -> element_size);
	++NUMBER_OF_ELEMENTS_IN_STK;
}

void* StackPeek(const stack_ty* stack_p)
{
	assert(NULL != stack_p);
	assert(0 != NUMBER_OF_ELEMENTS_IN_STK);
      return (void*)(CURRENT_ELEMENT_IN_STK);
}

void StackPop(stack_ty* stack_p)
{
	assert(NULL != stack_p);
	assert(0 != NUMBER_OF_ELEMENTS_IN_STK);
	--(NUMBER_OF_ELEMENTS_IN_STK);
}

size_t StackSize(const stack_ty* stack_p)
{
	return (NUMBER_OF_ELEMENTS_IN_STK);
}

int StackIsEmpty(const stack_ty* stack_p)
{
	if (0 == StackSize(stack_p))
	{
		return TRUE;
	}
	return FALSE;
}

size_t StackCapacity(const stack_ty* stack_p)
{
	return (stack_p -> capacity);
}

