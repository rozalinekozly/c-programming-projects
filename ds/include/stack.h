/* Stack - create, modify and explore stack objects of dynamic size */
#ifndef __STACK_H__
#define __STACK_H__

#include <stddef.h>		/* size_t */

typedef struct stack_s stack_ty;

/***************************************************************************************  
* Create a stack of "capacity" number of elements, each element of "element_size" size.
* Return Value: a pointer to created stack on success, NULL otherwise
****************************************************************************************/
stack_ty* StackCreate(size_t capacity, size_t element_size);

/***************************************************************************************  
* Remove all stack elements.
* If "stack_p" is NULL, no operations will be performed 
****************************************************************************************/
void StackDestroy(stack_ty* stack_p);

/***************************************************************************************  
* Add an element to the top of the stack.
* Undefined behaviour if "stack_p" or "new_element" is NULL.
* Undefined behaviour if pushing element causes capacity overflow.
****************************************************************************************/
void StackPush(stack_ty* stack_p, void* new_element);

/***************************************************************************************  
* Peek at the last element of the stack.
* Undefined behaviour if "stack_p" is NULL.
****************************************************************************************/
void* StackPeek(const stack_ty* stack_p);

/***************************************************************************************  
* Remove last element from stack.
* Undefined behaviour if "stack_p" is NULL.
****************************************************************************************/
void StackPop(stack_ty* stack_p);

/***************************************************************************************
* Returns the amount of elements occupied in the stack.
* Undefined behaviour if "stack_p" is NULL.
****************************************************************************************/
size_t StackSize(const stack_ty* stack_p);

/***************************************************************************************
* Is stack empty? Returns 1 if empty and 0 if not.
* Undefined behaviour if "stack_p" is NULL.
****************************************************************************************/
int StackIsEmpty(const stack_ty* stack_p);

/***************************************************************************************
* Returns maximum number of elements in the stack.
* Undefined behaviour if "stack_p" is NULL.
****************************************************************************************/
size_t StackCapacity(const stack_ty* stack_p);

#endif /* __STACK_H__ */
