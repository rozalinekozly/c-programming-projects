#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "sorted_list.h"

static int CmpInt(const void* a, const void* b, void* param);
static int PrintInt(void* data, void* param);
static int IsEven(const void* data, void* param);

static void TestCreateDestroy(void);
static void TestInsertAndOrder(void);
static void TestCountIsEmpty(void);
static void TestIterNavigation(void);
static void TestGetSetData(void);
static void TestRemove(void);
static void TestFind(void);
static void TestFindIf(void);
static void TestForEach(void);
static void TestMerge(void);

int main(void)
{
	TestCreateDestroy();
	TestInsertAndOrder();
	TestCountIsEmpty();
	TestIterNavigation();
	TestGetSetData();
	TestRemove();
	TestFind();
	TestFindIf();
	TestForEach();
	TestMerge();

	printf("ALL TESTS PASSED\n");
	return 0;
}

static void TestCreateDestroy(void)
{
	sorted_list_ty* list = SortedListCreate(CmpInt, NULL);
	assert(NULL != list);
	SortedListDestroy(list);
}

static void TestInsertAndOrder(void)
{
	sorted_list_ty* list = SortedListCreate(CmpInt, NULL);
	int a[] = {5, 1, 4, 2, 3};
	int i = 0;
	sorted_list_iter_ty it;
	int expected = 1;

	for (i = 0; i < 5; ++i)
	{
		SortedListInsert(list, &a[i]);
	}

	it = SortedListBeginIter(list);
	
	while (!SortedListIterIsEqual(it, SortedListEndIter(list)))
	{
		assert(*(int*)SortedListIterGetData(it) == expected);
		++expected;
		it = SortedListIterNext(it);
	}

	SortedListDestroy(list);
}

static void TestCountIsEmpty(void)
{
	sorted_list_ty* list = SortedListCreate(CmpInt, NULL);
	int x = 10;

	assert(1 == SortedListIsEmpty(list));
	assert(0 == SortedListCount(list));

	SortedListInsert(list, &x);

	assert(0 == SortedListIsEmpty(list));
	assert(1 == SortedListCount(list));

	SortedListDestroy(list);
}

static void TestIterNavigation(void)
{
	sorted_list_ty* list = SortedListCreate(CmpInt, NULL);
	int a[] = {1, 2, 3};
	sorted_list_iter_ty it;

	SortedListInsert(list, &a[0]);
	SortedListInsert(list, &a[1]);
	SortedListInsert(list, &a[2]);

	it = SortedListBeginIter(list);
	assert(*(int*)SortedListIterGetData(it) == 1);

	it = SortedListIterNext(it);
	assert(*(int*)SortedListIterGetData(it) == 2);

	it = SortedListIterPrev(it);
	assert(*(int*)SortedListIterGetData(it) == 1);

	SortedListDestroy(list);
}

static void TestGetSetData(void)
{
	sorted_list_ty* list = SortedListCreate(CmpInt, NULL);
	int a = 1, b = 3, c = 2;
	sorted_list_iter_ty it;

	SortedListInsert(list, &a);
	SortedListInsert(list, &b);

	it = SortedListBeginIter(list);
	SortedListIterSetData(list, it, &c);

	it = SortedListBeginIter(list);
	assert(*(int*)SortedListIterGetData(it) == 2);

	SortedListDestroy(list);
}

static void TestRemove(void)
{
	sorted_list_ty* list = SortedListCreate(CmpInt, NULL);
	int a[] = {1, 2, 3};
	sorted_list_iter_ty it;

	SortedListInsert(list, &a[0]);
	SortedListInsert(list, &a[1]);
	SortedListInsert(list, &a[2]);

	it = SortedListBeginIter(list);
	it = SortedListIterNext(it);

	SortedListRemove(it);

	assert(SortedListCount(list) == 2);

	SortedListDestroy(list);
}

static void TestFind(void)
{
	sorted_list_ty* list = SortedListCreate(CmpInt, NULL);
	int a[] = {1, 2, 3};
	int key = 2;
	sorted_list_iter_ty it;

	SortedListInsert(list, &a[0]);
	SortedListInsert(list, &a[1]);
	SortedListInsert(list, &a[2]);

	it = SortedListFind(list, &key);
	assert(*(int*)SortedListIterGetData(it) == 2);

	SortedListDestroy(list);
}

static void TestFindIf(void)
{
	sorted_list_ty* list = SortedListCreate(CmpInt, NULL);
	int a[] = {1, 2, 3, 4};
	sorted_list_iter_ty it;

	SortedListInsert(list, &a[0]);
	SortedListInsert(list, &a[1]);
	SortedListInsert(list, &a[2]);
	SortedListInsert(list, &a[3]);

	it = SortedListFindIf(SortedListBeginIter(list), SortedListEndIter(list),
	IsEven, NULL);

	assert(*(int*)SortedListIterGetData(it) == 2);

	SortedListDestroy(list);
}

static void TestForEach(void)
{
	sorted_list_ty* list = SortedListCreate(CmpInt, NULL);
	int a[] = {3, 1, 2};

	SortedListInsert(list, &a[0]);
	SortedListInsert(list, &a[1]);
	SortedListInsert(list, &a[2]);

	SortedListForEach(SortedListBeginIter(list),
	SortedListEndIter(list),
	PrintInt,
	NULL);
	printf("\n");

	SortedListDestroy(list);
}

static void TestMerge(void)
{
	sorted_list_ty* dest = SortedListCreate(CmpInt, NULL);
	sorted_list_ty* src = SortedListCreate(CmpInt, NULL);
	int a[] = {1, 3, 5};
	int b[] = {2, 4, 6};
	sorted_list_iter_ty it;
	int expected = 1;

	SortedListInsert(dest, &a[0]);
	SortedListInsert(dest, &a[1]);
	SortedListInsert(dest, &a[2]);

	SortedListInsert(src, &b[0]);
	SortedListInsert(src, &b[1]);
	SortedListInsert(src, &b[2]);

	SortedListMerge(dest, src);

	it = SortedListBeginIter(dest);
	while (!SortedListIterIsEqual(it, SortedListEndIter(dest)))
	{
		assert(*(int*)SortedListIterGetData(it) == expected);
		++expected;
		it = SortedListIterNext(it);
	}

	assert(SortedListIsEmpty(src));

	SortedListDestroy(dest);
	SortedListDestroy(src);
}

static int CmpInt(const void* a, const void* b, void* param)
{
	(void)param;
	return *(int*)a - *(int*)b;
}

static int PrintInt(void* data, void* param)
{
	(void)param;
	printf("%d ", *(int*)data);
	return 0;
}

static int IsEven(const void* data, void* param)
{
	(void)param;
	return (*(int*)data % 2 == 0);
}

