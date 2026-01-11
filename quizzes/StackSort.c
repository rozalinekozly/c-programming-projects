#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

#define CAPACITY 5

void PrintStk(stack_ty*);
void SortStack(stack_ty*, stack_ty*);

int main()
{
	stack_ty* stk = StackCreate(CAPACITY, sizeof(int));
	stack_ty* sorted_stk = StackCreate(CAPACITY, sizeof(int));
	int arr[] = {7, 0 , 10 , 4, 1};
	size_t i = 0;
	
	if(NULL == stk || NULL == sorted_stk)
	{
		printf("failed at creatoin\n");
		return 1;
	}

	for(i = 0 ; i < CAPACITY ; i++)
	{
		StackPush(stk, &arr[i]);
	}
	
	SortStack(stk, sorted_stk);
	
	PrintStk(sorted_stk);
	return 0;
}

void SortStack(stack_ty* stk, stack_ty* sorted_stk)
{
	size_t popped_from_sorted = 0;
	int curr_to_insert = 0;
	
	while(!StackIsEmpty(stk))
	{
		curr_to_insert = *(int*)StackPeek(stk);
		StackPop(stk);
		
		while(!StackIsEmpty(sorted_stk) && *(int*)StackPeek(sorted_stk) > curr_to_insert)
		{
			StackPush(stk, StackPeek(sorted_stk));
			StackPop(sorted_stk);
			++popped_from_sorted;
		}
		StackPush(sorted_stk, &curr_to_insert);
		
		while(popped_from_sorted > 0)
		{
			StackPush(sorted_stk, StackPeek(stk));
			StackPop(stk);
			--popped_from_sorted;
		}
	}

}

void PrintStk(stack_ty* stk)
{
	while(!StackIsEmpty(stk))
	{
		printf("|\t%d\t|\n", *(int*)StackPeek(stk));
		StackPop(stk);
	}
	printf("|_______________|\n");

}
