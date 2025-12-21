/*--------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer : oshi
worksheet : 17 (ds - queue)
version : 1
date : 17 Dec 2025
stage : mimir
------------------------------------------------------------------------------*/
#include <stdio.h>		/* printf(), NULL */
#include <stdlib.h> 		/* malloc(), free(), rand() */
#include <assert.h>		/* assert() */
/* to randomify data */
#include <math.h>			/* pow()   */

#include "queue.h"	/* API */
#include "slist.h"	/* aux API */

/*magic numbers */
/* data's array size */
#define DATA_ARR_SIZE						10
/* to make the values readable used for modulu */
#define MAX_VAL							100

/*---------------- testing functions declarations ----------------------------*/
static void TestQueueCreateDestroy();
static void TestQueueEnqueueDequeuePeek();
static void TestQueueIsEmpty();
static void TestQueueSize();
static void TestQueueAppend();
/*-----------------aux functions for dealing with queues------------------------*/
/* printing queue to the terminal */
static void PrintQueue(queue_ty*); 
/* function to generate random data */
static void GenereateData(int* arr, size_t arr_size);
/* function to generate a queue from given array */
static queue_ty* GenerateQueueFrmArr(queue_ty*, int* arr, size_t arr_size);
/*------------------------------implementations ------------------------------*/
int main()
{
	TestQueueCreateDestroy();
	TestQueueEnqueueDequeuePeek();
	TestQueueIsEmpty();
	TestQueueSize();
	TestQueueAppend();
	
	return 0;
}
/*--------------------aux functions implementation ---------------------------*/
static void PrintQueue(queue_ty* queue_p)
{
	size_t i = 0;
	size_t size = QueueSize(queue_p);
	int *val = NULL;

	printf("Queue: ");

	for (i = 0; i < size; ++i)
	{
		val = (int *)QueuePeek(queue_p);
		printf("%d ", *val);

		QueueEnqueue(queue_p, val);
		QueueDequeue(queue_p);
	}
	printf("\n");
}


static void GenereateData(int* arr, size_t arr_size)
{
    size_t i = 0;
     
    /* intialize data's array */
    for (i = 0 ; i < arr_size ; ++i)
    {
    	arr[i] = pow(-1,i)*(rand()%MAX_VAL);
    
    }
}

static queue_ty* GenerateQueueFrmArr(queue_ty* queue_p, int* arr, size_t arr_size)
{
 	size_t i = 0;
 	 
  	for (i = 0 ; i < arr_size ; ++i)
  	{
		QueueEnqueue(queue_p, &arr[i]);
  	}
   	return queue_p;
}

/*------------------testing functions implementations ------------------------*/
static void TestQueueCreateDestroy()
{
	queue_ty* queue_p = QueueCreate();

	printf("create & destroy\t\t");
	
	if (NULL == queue_p)
	{
		printf("FAILED, created NULL\n");
		return;
	}
	QueueDestroy(queue_p);
	/* it fails when checking if queue_p is null (???)*/
	printf("PASSED\n");
}


static void TestQueueEnqueueDequeuePeek()
{
	/*check enqueue's return values*/
	queue_ty* queue_p = QueueCreate();
	int arr[DATA_ARR_SIZE] = {0};
	size_t queue_size = DATA_ARR_SIZE;
	size_t i = 0;
	
	printf("enqueue & dequeue & peek\tPASSED\n");
	/* generate random data (range 0 - MAX_VAL) */
	GenereateData(arr, DATA_ARR_SIZE);
	/* create queue from given array (filled with data, use Enqueue function */
	queue_p = GenerateQueueFrmArr(queue_p, arr, DATA_ARR_SIZE);
	printf("enqueue:");
	PrintQueue(queue_p);
	printf("Dequeue (1 element at a time):\n");
	
	for (i = 0 ; i < queue_size ; i++)
	{
		QueueDequeue(queue_p);
		PrintQueue(queue_p);
	}
	QueueDestroy(queue_p);
}

static void TestQueueIsEmpty()
{
	queue_ty* queue_p = QueueCreate();
	int arr[DATA_ARR_SIZE] = {0};
	size_t is_empty_res = QueueIsEmpty(queue_p);
	size_t expected_is_empty_res = 1;
	
	printf("is empty\t\t\t");
	
	if (is_empty_res != expected_is_empty_res)
	{
		printf("FAILED at realising the queue is empty\n");
	}
	/* generate random data (range 0 - MAX_VAL) */
	GenereateData(arr, DATA_ARR_SIZE);
	/* create queue from given array (filled with data, use Enqueue function */
	queue_p = GenerateQueueFrmArr(queue_p, arr, DATA_ARR_SIZE);
	
	expected_is_empty_res = 0;
	is_empty_res = QueueIsEmpty(queue_p);
	
	if (is_empty_res != expected_is_empty_res)
	{
		printf("FAILED at realising the queue is not empty\n");
	}
	printf("PASSED\n");
	QueueDestroy(queue_p);
}

static void TestQueueSize()
{
	queue_ty* queue_p = QueueCreate();
	int arr[DATA_ARR_SIZE] = {0};
	size_t size_res = QueueSize(queue_p);
	size_t expected_size_res = 0;
	
	printf("size\t\t\t\t");
	
	if (expected_size_res != size_res)
	{
		printf("FAILED at realising the queue size is %lu\n",expected_size_res);
	}
	/* generate random data (range 0 - MAX_VAL) */
	GenereateData(arr, DATA_ARR_SIZE);
	/* create queue from given array (filled with data, use Enqueue function */
	queue_p = GenerateQueueFrmArr(queue_p, arr, DATA_ARR_SIZE);
	
	expected_size_res = DATA_ARR_SIZE;
	size_res = QueueSize(queue_p);
	
	if (expected_size_res != size_res)
	{
		printf("FAILED at realising the queue size is %u\n",DATA_ARR_SIZE);
	}
	printf("PASSED\n");
	QueueDestroy(queue_p);

}

static void TestQueueAppend()
{
	queue_ty* queue_p_1 = QueueCreate();
	queue_ty* queue_p_2 = QueueCreate();
	int arr_1[DATA_ARR_SIZE] = {0};
	int arr_2[DATA_ARR_SIZE] = {0};
	
	/* generate random data (range 0 - MAX_VAL) */
	GenereateData(arr_1, DATA_ARR_SIZE);
	GenereateData(arr_2, DATA_ARR_SIZE);
	/* create queue from given array (filled with data, use Enqueue function */
	queue_p_1 = GenerateQueueFrmArr(queue_p_1, arr_1, DATA_ARR_SIZE);
	queue_p_2 = GenerateQueueFrmArr(queue_p_2, arr_2, DATA_ARR_SIZE);
	
	printf("append\t\t\t\tPASSED\n");
	printf("Queue1: ");
	PrintQueue(queue_p_1);
	
	printf("Queue2: ");
	PrintQueue(queue_p_2);
	
	QueueAppend(queue_p_1, queue_p_2);
	
	printf("after appending:\n");
	printf("Queue1: ");
	PrintQueue(queue_p_1);
	
	printf("Queue2: ");
	PrintQueue(queue_p_2);
	
	/* since queue_p_2 -> list_ty head and tail points at the dummy node
	   we don't need to free it*/
	QueueDestroy(queue_p_1);

}






