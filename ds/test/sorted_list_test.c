#include <stdio.h>
#include <stdlib.h>

#include "sorted_list.h"

/* Macros for clear output without using assert */
#define TEST(msg) printf("\n[TEST] %s\n", msg)
#define PASS(msg) printf("  [PASS] %s\n", msg)
#define FAIL(msg) printf("  [FAIL] %s\n", msg)

static int CmpInt(const void* a, const void* b, void* param);
static int IsEven(const void* data, void* param);

static void TestCreateDestroy(void);
static void TestInsertAndOrder(void);
static void TestCountIsEmpty(void);
static void TestFind(void);
static void TestMerge(void);

int main(void)
{
    TestCreateDestroy();
    TestInsertAndOrder();
    TestCountIsEmpty();
    TestFind();
    TestMerge();

    printf("\n--- All tests finished ---\n");
    return 0;
}

static void TestCreateDestroy(void)
{
    sorted_list_ty* list = SortedListCreate(CmpInt, NULL);
    TEST("Create & Destroy");
    if (NULL != list)
    {
        PASS("List created successfully");
        SortedListDestroy(list);
    }
    else
    {
        FAIL("List creation failed");
    }
}

static void TestInsertAndOrder(void)
{
    sorted_list_ty* list = SortedListCreate(CmpInt, NULL);
    int a[] = {5, 1, 4, 2, 3};
    int i = 0;
    sorted_list_iter_ty it;
    int expected = 1;
    int success = 1;

    TEST("Insert & Order Validation");
    for (i = 0; i < 5; ++i)
    {
        SortedListInsert(list, &a[i]);
    }

    it = SortedListBeginIter(list);
    while (!SortedListIterIsEqual(it, SortedListEndIter(list)))
    {
        if (*(int*)SortedListIterGetData(it) != expected)
        {
            success = 0;
            break;
        }
        ++expected;
        it = SortedListIterNext(it);
    }

    if (success && expected == 6)
    {
        PASS("Elements are in perfect order (1-5)");
    }
    else
    {
        FAIL("Elements are out of order or missing");
    }

    SortedListDestroy(list);
}

static void TestCountIsEmpty(void)
{
    sorted_list_ty* list = SortedListCreate(CmpInt, NULL);
    int x = 10;

    TEST("Count & IsEmpty");
    if (SortedListIsEmpty(list) && SortedListCount(list) == 0)
    {
        PASS("New list is empty");
    }

    SortedListInsert(list, &x);

    if (!SortedListIsEmpty(list) && SortedListCount(list) == 1)
    {
        PASS("List count is 1 after insertion");
    }
    else
    {
        FAIL("Count or IsEmpty failed after insertion");
    }

    SortedListDestroy(list);
}

static void TestFind(void)
{
    sorted_list_ty* list = SortedListCreate(CmpInt, NULL);
    int a[] = {10, 20, 30};
    int key = 20;
    int missing_key = 50;
    sorted_list_iter_ty it;

    TEST("Find");
    SortedListInsert(list, &a[0]);
    SortedListInsert(list, &a[1]);
    SortedListInsert(list, &a[2]);

    it = SortedListFind(list, &key);
    if (!SortedListIterIsEqual(it, SortedListEndIter(list)) && *(int*)SortedListIterGetData(it) == 20)
    {
        PASS("Found existing element 20");
    }
    else
    {
        FAIL("Failed to find 20");
    }

    it = SortedListFind(list, &missing_key);
    if (SortedListIterIsEqual(it, SortedListEndIter(list)))
    {
        PASS("Correctly returned EndIter for non-existent element");
    }
    else
    {
        FAIL("Found an element that shouldn't exist");
    }

    SortedListDestroy(list);
}

static void TestMerge(void)
{
    sorted_list_ty* dest = SortedListCreate(CmpInt, NULL);
    sorted_list_ty* src = SortedListCreate(CmpInt, NULL);
    int a[] = {1, 3, 5};
    int b[] = {2, 4, 6};
    int expected = 1;
    int success = 1;
    sorted_list_iter_ty it;

    TEST("Merge");
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
        if (*(int*)SortedListIterGetData(it) != expected)
        {
            success = 0;
        }
        ++expected;
        it = SortedListIterNext(it);
    }

    if (success && SortedListIsEmpty(src) && SortedListCount(dest) == 6)
    {
        PASS("Merge successful: dest has 1-6, src is empty");
    }
    else
    {
        FAIL("Merge failed: order or counts are wrong");
    }

    SortedListDestroy(dest);
    SortedListDestroy(src);
}

/* Helper Functions */
static int CmpInt(const void* a, const void* b, void* param)
{
    (void)param;
    return *(int*)a - *(int*)b;
}

static int IsEven(const void* data, void* param)
{
    (void)param;
    return (*(int*)data % 2 == 0);
}
