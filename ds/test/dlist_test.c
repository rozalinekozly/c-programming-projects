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
#define TEST(msg) printf("[TEST] %s\n", msg)
#define PASS(msg) printf("[PASS] %s\n", msg)
#define FAIL(msg) printf("[FAIL] %s\n", msg)
/*--------------------testing functions----------------------------------------*/
static void TestCreateDestroy();
static void TestPushPopFront();
static void TestPushPopBack();
static void TestInsertBeforeRemove();
/*static void TestFind();*/
static void TestSplice();

/*-----------------aux functions for dealing with list------------------------*/
static void PushArrFront(int* arr, size_t arr_size, dlist_ty* list);
static void PrintDlist(dlist_ty* list);
static void GenereateData(int* arr, size_t arr_size);
/*-------------------- implementations ----------------------------------------*/
int main() 
{
	TestCreateDestroy();
	TestPushPopFront();
	TestPushPopBack();
	TestInsertBeforeRemove();
	/*TestFind();*/
	TestSplice();
    return 0;
}
/*----------------------------------tests------------------------------------*/
static void TestCreateDestroy()
{
	dlist_ty* list = DListCreate();
	
	TEST("create & destroy");
	if(NULL == list)
	{
		FAIL("create failed and created a NULL");
		return;
	}
	PASS("create successed in creating a dlist");
	DListDestroy(list);
	PASS("destroy successed in destroying a dlist");
}

static void TestPushPopFront()
{
		dlist_ty* list = DListCreate();
		int a = 1;
		int b = 2;
		int c = 3;
		
		TEST("push & pop front");
		printf("expected 3-2-1\n");	
		DListPushFront(list, &a);
		DListPushFront(list, &b);
		DListPushFront(list, &c);
		PrintDlist(list);
		
		printf("popping front\n");	
		DListPopFront(list);
		PrintDlist(list);
		DListPopFront(list);
		PrintDlist(list);
		DListPopFront(list);
		PrintDlist(list);

		DListDestroy(list);
}
static void TestPushPopBack()
{
		dlist_ty* list = DListCreate();
		int a = 1;
		int b = 2;
		int c = 3;
		
		TEST("push & pop back");
		printf("expected 1-2-3\n");	
		DListPushBack(list, &a);
		DListPushBack(list, &b);
		DListPushBack(list, &c);
		PrintDlist(list);
		
		printf("popping back\n");	
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
/* make it better! */
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

static void TestSplice()
{
	dlist_ty* list1 = DListCreate();
	dlist_ty* list2 = DListCreate();
	dlist_iter_ty from = NULL;
	dlist_iter_ty to = NULL;
	dlist_iter_ty where = NULL;
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	
	int e = 10;
	int f = 20;
	int g = 30;
	int h = 40;
	
	TEST("splice");
	/* create a multi push function aux that it takes an array and pushes all it's elements */
	DListPushFront(list1, &a);
	DListPushFront(list1, &b);
	DListPushFront(list1, &c);
	DListPushFront(list1, &d);
	
	DListPushFront(list2, &e);
	DListPushFront(list2, &f);
	DListPushFront(list2, &g);
	DListPushFront(list2, &h);
	
	printf("list1:");
	PrintDlist(list1);
	
	printf("list2:");
	PrintDlist(list2);
	
	from = DListBeginIter(list1);
	to = DListIterNext(DListIterNext(from));
	
	where = DListIterNext(DListIterNext(DListBeginIter(list2)));

    DListSplice(from, to, where);
    
    printf("list1:");
	PrintDlist(list1);
	
	printf("list2:");
	PrintDlist(list2);
	
	DListDestroy(list1);
	DListDestroy(list2);		   
}
/*
static void TestFind()
{
	int arr[DATA_ARR_SIZE] = {0};
	dlist_ty* list = DListCreate();
	
	GenereateData(arr, DATA_ARR_SIZE);
	PushArrFront(arr, DATA_ARR_SIZE, list);
	
	


}

*/
static void PushArrFront(int* arr, size_t arr_size, dlist_ty* list)
{
	size_t i = 0;
	
	for(i = 0 ; i < arr_size ; i++)
	{
		DListPushFront(list1, &arr[i]);
	}
}

static void PrintDlist(dlist_ty* list)
{
	/* this function assumes the type is int of the data */
	/* later change it to struct of person or smth */
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

/* function to generate random data */
static void GenereateData(int* arr, size_t arr_size)
{
	 size_t i = 0;
     
    /* intialize data's array */
    for(i = 0 ; i < arr_size ; ++i)
    {
    	arr[i] = pow(-1,i)*(rand()%MAX_VAL);
    
    }



}
