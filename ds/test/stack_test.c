/*--------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer  : steve
worksheet : 12 (ds - stack)
version   : 1
date      : 10 Dec 2025
stage     : post-testing (intial-testing-peerReview-mimir)
----------------------------------------------------------------------------*/
#include "../include/stack.h"
#include <stdio.h>	/* printf() */
#include <math.h>		/* pow()   */
#include <stdlib.h>	/* rand() */
#include  <limits.h>		/*INT_MAX*/

#define SIZEOF_ARR(ARR)  		(sizeof(ARR)/sizeof(*ARR))
#define ASCII_SIZE				256

static void Test();

static void TestInt(size_t capacity, size_t element_size, int* elements, size_t number_of_elements);
static void TestFloat(size_t capacity, size_t element_size, float* elements, size_t number_of_elements);
static void TestChar(size_t capacity, size_t element_size, char* elements, size_t number_of_elements);

static size_t test_number = 1;

int main()
{	
	Test();
	return 0;	
}


static void Test()
{
	size_t capacity = 100;
	int elements_int[100] = {0};
	float elements_float[100] = {0};
	char elements_char[100] = {0};
	size_t i = 0;
	
	
	/* creating random values of each type */
	for(i = 0 ; i < capacity ; i++)
	{
		elements_int[i] = pow(-1,i)*(rand()%INT_MAX );
		elements_float[i] = pow(-1,i)*((float)(rand()% INT_MAX)/(rand() + 1));
		elements_char[i] = (rand() % ASCII_SIZE);
	
	}
	/* call test int */
	TestInt(capacity, sizeof(int), elements_int, 100);
	TestFloat(capacity, sizeof(float), elements_float, 100);
      TestChar(capacity, sizeof(char), elements_char, 100);
      
}


static void TestInt(size_t capacity, size_t element_size, int* elements, size_t number_of_elements)
{	
	stack_ty* stack_p = StackCreate(capacity, element_size);	
	size_t i = 0;
	int val = 0;

	printf("--------- TEST %lu ---------\n",test_number);
	printf("create\t\t");
	if(NULL == stack_p)
	{
		printf("failed at creating the stack with the following attributes:\n");
		printf("capacity = %lu, element size = %lu\n", capacity, element_size);
		return;
	}
	printf("PASSED\n");
	printf("capacity\t");
	if(capacity != StackCapacity(stack_p))
	{
		printf("failed: StackCreate function, in creating stack of %lu capacity\n", capacity);
		printf("it created %lu capacity\n",StackCapacity(stack_p));
		StackDestroy(stack_p);
		return;
	}
	printf("PASSED\n");
	
		printf("push\t\t");
		for(i = 0 ; i < number_of_elements ; i++)
		{
			StackPush(stack_p, &elements[i]);
		}
		if(StackSize(stack_p) != number_of_elements)
		{
			printf("size\t\t");
			printf("failed\n");
			return;
		}
		printf("PASSED\n");
		printf("peek\t\t");
		for(i = 0 ; i < number_of_elements ; i++)
		{
			val = *(int*)StackPeek(stack_p);
			StackPop(stack_p);
			if(val != elements[number_of_elements -1 - i])
			{
				printf("failed: it got %d, where it supposed to get %d\n", val, elements[number_of_elements -1 - i]);
				return;
			}
		}

            printf("PASSED\n");
            printf("pop\t\t");
            printf("PASSED\n");
            printf("size\t\t");
            printf("PASSED\n");
		StackDestroy(stack_p);
		printf("destroy\t\t");
            printf("PASSED\n");
	
	++test_number;
   
}

static void TestFloat(size_t capacity, size_t element_size, float* elements, size_t number_of_elements)
{	
	stack_ty* stack_p =  StackCreate(capacity, element_size);	
	size_t i = 0;
	float val = 0;


	
	printf("--------- TEST %lu ---------\n",test_number);
	++test_number;
	printf("create\t\t");
	if(NULL == stack_p)
	{
		printf("failed at creating the stack with the following attributes:\n");
		printf("capacity = %lu, element size = %lu\n", capacity, element_size);
		return;
	
	}
	printf("PASSED\n");
	printf("capacity\t");
	if(capacity != StackCapacity(stack_p))
	{
		printf("failed: StackCreate function, in creating stack of %lu capacity\n", capacity);
		printf("it created %lu capacity\n",StackCapacity(stack_p));
		StackDestroy(stack_p);
		return;
	}
	printf("PASSED\n");
	
		printf("push\t\t");
		for(i = 0 ; i < number_of_elements ; i++)
		{
			StackPush(stack_p, &elements[i]);
		}
		if(StackSize(stack_p) != number_of_elements)
		{
			printf("size\t\t");
			printf("failed\n");
			return;
		}
		printf("PASSED\n");
		printf("peek\t\t");
		for(i = 0 ; i < number_of_elements ; i++)
		{
			val = *(float*)StackPeek(stack_p);
			StackPop(stack_p);
			if(val != elements[number_of_elements -1 - i])
			{
				printf("failed: it got %f, where it supposed to get %f\n", val, elements[number_of_elements -1 - i]);
				return;
			}
		}

            printf("PASSED\n");
            printf("pop\t\t");
            printf("PASSED\n");
            printf("size\t\t");
            printf("PASSED\n");
		StackDestroy(stack_p);
		printf("destroy\t\t");
            printf("PASSED\n");
	

    

}

static void TestChar(size_t capacity, size_t element_size, char* elements, size_t number_of_elements)
{	
	stack_ty* stack_p =  StackCreate(capacity, element_size);	
	size_t i = 0;
	char val = 0;


	
	printf("--------- TEST %lu ---------\n",test_number);
	printf("create\t\t");
	if(NULL == stack_p)
	{
		printf("failed at creating the stack with the following attributes:\n");
		printf("capacity = %lu, element size = %lu\n", capacity, element_size);
		return;
	
	}
	printf("PASSED\n");
	printf("capacity\t");
	if(capacity != StackCapacity(stack_p))
	{
		printf("failed: StackCreate function, in creating stack of %lu capacity\n", capacity);
		printf("it created %lu capacity\n",StackCapacity(stack_p));
		StackDestroy(stack_p);
		return;
	}
	printf("PASSED\n");
	
		printf("push\t\t");
		for(i = 0 ; i < number_of_elements ; i++)
		{
			StackPush(stack_p, &elements[i]);
		}
		if(StackSize(stack_p) != number_of_elements)
		{
			printf("size\t\t");
			printf("failed\n");
			return;
		}
		printf("PASSED\n");
		printf("peek\t\t");
		for(i = 0 ; i < number_of_elements ; i++)
		{
			val = *(char*)StackPeek(stack_p);
			StackPop(stack_p);
			if(val != elements[number_of_elements -1 - i])
			{
				printf("failed: it got %c, where it supposed to get %c\n", val, elements[number_of_elements -1 - i]);
				return;
			}
		}

            printf("PASSED\n");
            printf("pop\t\t");
            printf("PASSED\n");
            printf("size\t\t");
            printf("PASSED\n");
		StackDestroy(stack_p);
		printf("destroy\t\t");
            printf("PASSED\n");
	
	++test_number;
    

}

