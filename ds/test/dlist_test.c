/*--------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer : oshrat
worksheet : (ds - dlist)
version : 1
date : 23 Dec 2025
stage :  writing code
----------------------------------------------------------------------------*/
#include <stdio.h>				         /* printf(), NULL */
#include <stdlib.h> 				     /* malloc(), free(), rand() */
#include <assert.h>				         /* assert() */
/* to randomify data */
#include <math.h>					     /* pow()   */

#include "dlist.h" 

#define TRUE   						      1
#define FALSE  						      0
/*magic numbers */
/* data's array size */
#define DATA_ARR_SIZE					  10
/* to make the values readable used for modulu */
#define MAX_VAL							100
/*------------------- macros for printing test results -----------------------*/
#define PASS(msg) printf("[PASS] %s\n", msg)
#define FAIL(msg) printf("[FAIL] %s\n", msg)
/*--------------------testing functions----------------------------------------*/
static void TestCreateDestroy();
static void TestPushPopFront();
static void TestPushPopBack();
static void TestInsertBeforeRemove();

/*-----------------aux functions for dealing with list------------------------*/
static void PrintDlist(dlist_ty* list);
/*-------------------- implementations ----------------------------------------*/
int main() 
{
	TestCreateDestroy();
	TestPushPopFront();
	TestPushPopBack();
	printf("\n\n\n\n");
	TestInsertBeforeRemove();
	
    return 0;
}
/*----------------------------------tests------------------------------------*/
static void TestCreateDestroy()
{
	dlist_ty* list = DListCreate();
	if(NULL == list)
	{
		FAIL("create failed and created a NULL\n");
		return;
	}
	PASS("create successed in creating a dlist\n");
	DListDestroy(list);
}

static void TestPushPopFront()
{
		dlist_ty* list = DListCreate();
		int a = 1;
		int b = 2;
		int c = 3;
		DListPushFront(list, &a);
		printf("count is %lu\n", DListCount(list));
		DListPushFront(list, &b);
		printf("count is %lu\n", DListCount(list));
		DListPushFront(list, &c);
		printf("count is %lu\n", DListCount(list));
		PrintDlist(list);
		
		DListPopFront(list);
		PrintDlist(list);
		printf("count is %lu\n", DListCount(list));
		DListPopFront(list);
		PrintDlist(list);
		printf("count is %lu\n", DListCount(list));
		DListPopFront(list);
		PrintDlist(list);
		printf("count is %lu\n", DListCount(list));
		DListDestroy(list);
}
static void TestPushPopBack()
{
		dlist_ty* list = DListCreate();
		int a = 1;
		int b = 2;
		int c = 3;
		DListPushBack(list, &a);
		DListPushBack(list, &b);
		DListPushBack(list, &c);
		
		PrintDlist(list);
		
		DListPopBack(list);
		PrintDlist(list);
		
		DListPopBack(list);
		PrintDlist(list);
		
		DListPopBack(list);
		PrintDlist(list);
		
		DListDestroy(list);	
}
static void TestInsertBeforeRemove()
{
	dlist_ty* list = DListCreate();
	dlist_iter_ty rmv;
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	
	DListPushBack(list, &a);
	DListPushBack(list, &b);
	DListPushBack(list, &c);
	DListPushBack(list, &d);
	
	PrintDlist(list);
	rmv = DListIterNext(DListIterNext(DListBeginIter(list)));
	DListRemove(rmv);
	PrintDlist(list);

	DListDestroy(list);	
}

static void PrintDlist(dlist_ty* list)
{
	/* this function assumes the type is int of the data */
	dlist_iter_ty list_iter = DListBeginIter(list);
	dlist_iter_ty list_tail = DListEndIter(list);
	
	printf("\tDlist: ");
	while(list_iter != list_tail)
	{
		printf(" %d <->", *(int*)DListIterGetData(list_iter));
		list_iter = DListIterNext(list_iter);
	}
	printf("\n");
}


