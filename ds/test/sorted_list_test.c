#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "sorted_list.h"

static int CmpInt(const void* data1, const void* data2, void* param);
static int PrintInt(void* data, void* param);
static int IsMatchInt(const void* data, void* param);

int main(void)
{
	sorted_list_ty* list = NULL;
	sorted_list_iter_ty iter;
	int i = 0;
	int values[] = {7, 3, 9, 1, 5, 8, 2, 6, 4};
	int key = 5;

	list = SortedListCreate(CmpInt, NULL);
	assert(NULL != list);

	for (i = 0; i < 9; ++i)
	{
		SortedListInsert(list, &values[i]);
	}

	printf("After insert:\n");
	SortedListForEach(SortedListBeginIter(list),
	SortedListEndIter(list),
	PrintInt,
	NULL);
	printf("\n");

	iter = SortedListFind(list, &key);
	assert(!SortedListIterIsEqual(iter, SortedListEndIter(list)));
	printf("Found %d\n", *(int*)SortedListIterGetData(iter));

	SortedListRemove(iter);

	printf("After remove 5:\n");
	SortedListForEach(SortedListBeginIter(list),
	SortedListEndIter(list),
	PrintInt,
	NULL);
	printf("\n");

	iter = SortedListFindIf(SortedListBeginIter(list),
	SortedListEndIter(list),
	IsMatchInt,
	&key);
	assert(SortedListIterIsEqual(iter, SortedListEndIter(list)));

	SortedListDestroy(list);

	printf("Test passed\n");
	return 0;
}

static int CmpInt(const void* data1, const void* data2, void* param)
{
	(void)param;
	return *(int*)data1 - *(int*)data2;
}

static int PrintInt(void* data, void* param)
{
	(void)param;
	printf("%d ", *(int*)data);
	return 0;
}

static int IsMatchInt(const void* data, void* param)
{
	return (*(int*)data == *(int*)param);
}
	

