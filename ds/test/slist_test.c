/*--------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer : nimrod
worksheet : 14 (ds - slist)
version : 1
date : 14 Dec 2025
stage : testing
----------------------------------------------------------------------------*/
#include <assert.h>				      /* assert() */
#include <stdio.h> 					/* printf() */
#include "../include/slist.h"

#define TRUE 1
#define FALSE 0

static void TestSomething(void);

static void TestCreateDestroy(void);
static void TestCount(void);
static void TestInsertBefore(void);
static void TestRemove(void);
static void TestFind(void);
static void TestForEach(void);

static int MatchInt(const void* data, void* param);
static int ActionAdd(void* data, void* param);

int main(void)
{
	TestSomething();
	printf("All tests passed\n");
	return 0;
}

/*---------------------------------driver------------------------------------*/

static void TestSomething(void)
{
	TestCreateDestroy();
	TestCount();
	TestInsertBefore();
	TestRemove();
	TestFind();
	TestForEach();
}

/*----------------------------------tests------------------------------------*/

static void TestCreateDestroy(void)
{
	slist_ty* list = SListCreate();
	if(NULL == list)
	{
		printf("failed at creation, null\n");
	}
	SListDestroy(list);
}

static void TestCount(void)
{
	slist_ty* list = SListCreate();
	slist_iter_ty iter = SListBeginIter(list);
	int a = 1;
	int b = 2;
	int c = 3;
	size_t count = 0;

	iter = SlistInsertBefore(list, iter, &a);
	iter = SlistInsertBefore(list, iter, &b);
	iter = SlistInsertBefore(list, iter, &c);

	count = SListCount(list);
	
	if(3 != count)
	{
		printf("failed in count, your count is %lu\n", count );
	}
	SListDestroy(list);
}

static void TestInsertBefore(void)
{
	slist_ty* list = SListCreate();
	slist_iter_ty iter = SListBeginIter(list);
	int a = 10;
	int b = 20;

	iter = SlistInsertBefore(list, iter, &a);
	iter = SlistInsertBefore(list, iter, &b);

	iter = SListBeginIter(list);
	if(20 != *(int*)IterGetData(iter))
	{
		printf("failed at get data1\n");
	
	}
	iter = IterNext(iter);
	if(10 != *(int*)IterGetData(iter))
	{
		printf("failed at get data2\n");
	}

	SListDestroy(list);
}

static void TestRemove(void)
{
	slist_ty* list = SListCreate();
	slist_iter_ty iter = SListBeginIter(list);
	int a = 1;
	int b = 2;
	int c = 3;

	iter = SlistInsertBefore(list, iter, &a);
	iter = SlistInsertBefore(list, iter, &b);
	iter = SlistInsertBefore(list, iter, &c);

	iter = SListBeginIter(list);
	iter = SListRemove(iter);

	if(2 != SListCount(list))
	{
		printf("failed at remove-count\n");
	}
	if(2 != *(int*)IterGetData(iter))
	{
		printf("failed at remove2\n");
	}

	SListDestroy(list);
}

static void TestFind(void)
{
	slist_ty* list = SListCreate();
	slist_iter_ty iter = SListBeginIter(list);
	slist_iter_ty found = NULL;
	int a = 5;
	int b = 7;
	int c = 9;
	int key = 7;

	iter = SlistInsertBefore(list, iter, &a);
	iter = SlistInsertBefore(list, iter, &b);
	iter = SlistInsertBefore(list, iter, &c);

	found = SListFind(SListBeginIter(list), SListEndIter(list), (match_func_ty )MatchInt, &key);

	if(FALSE != IterIsEqual(found, SListEndIter(list)))
	{
		printf("failed at itr is equal1\n");
	}
	if(7 != *(int*)IterGetData(found))
	{
		printf("failed at itr is equal2\n");
	}

	SListDestroy(list);
}

static void TestForEach(void)
{
	slist_ty* list = SListCreate();
	slist_iter_ty iter = SListBeginIter(list);
	int a = 1;
	int b = 2;
	int add = 10;

	iter = SlistInsertBefore(list, iter, &a);
	iter = SlistInsertBefore(list, iter, &b);

	SListForEach(SListBeginIter(list),
	SListEndIter(list),
	ActionAdd,
	&add);

	iter = SListBeginIter(list);
	if(12 != *(int*)IterGetData(iter))
	{
		printf("failed at for-each\n");
	}
	iter = IterNext(iter);
	if(11 != *(int*)IterGetData(iter))
	{
		printf("failed at for-each\n");
	}

	SListDestroy(list);
}

/*--------------------------------helpers------------------------------------*/

static int MatchInt(const void* data, void* param)
{
	return (*(int*)data == *(int*)param);
}

static int ActionAdd(void* data, void* param)
{
	*(int*)data += *(int*)param;
	return TRUE;
}
