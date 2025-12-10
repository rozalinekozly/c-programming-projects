/*--------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer  : 
worksheet : 12 (ds - stack)
version   : 1
date      : 9 Dec 2025
stage     : pre-review
----------------------------------------------------------------------------*/
#include "../include/stack.h"
#include <stdio.h>
/*
static void TestStackCreate();
static void TestStackDestroy();
static void TestStackPush();
static void TestStackPeek();
static void TestStackPop();
static void TestStackIsEmpty();
static void TestStackSize();
static void TestStackCapacity();
*/
int main()
{
	stack_ty* stack_p =  StackCreate(10, sizeof(int));
	size_t i = 0;
	int val = 5;
	int my_val = 4;
	for(i = 0 ; i < 10 ; i++)
	{
	    StackPush(stack_p, &my_val);
	    printf("stack size = %lu\n", StackSize(stack_p));
	    printf("stack is empty? %d\n",StackIsEmpty(stack_p));
	    val = *((int*) StackPeek(stack_p));
	    printf("val is %d\n", val);

	}
	

      printf("stack capacity? %lu\n",StackCapacity(stack_p));
	 1028

	for(i = 0 ; i < 10 ; i++)
	{
	    val = *((int*) StackPeek(stack_p));
	    printf("val is %d\n", val);
	    StackPop(stack_p);
	    printf("stack size = %lu\n", StackSize(stack_p));
	    printf("stack is empty? %d\n",StackIsEmpty(stack_p));
	}
	
	StackDestroy(stack_p);
	return 0;
	
}

/*
static void TestStackCreate()
{

}
static void TestStackDestroy()
{
	

}
static void TestStackPush()
{

}
static void TestStackPeek()
{

}
static void TestStackPop();
static void TestStackIsEmpty()
{

}
static void TestStackSize()
{

}
static void TestStackCapacity()
{

}*/
