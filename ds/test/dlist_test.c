/*--------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer : oshrat
version : 1
date : 23 Dec 2025
----------------------------------------------------------------------------*/
#include <stdio.h>      /* printf(), NULL */
#include <stdlib.h>     /* malloc(), free(), rand() */
#include <assert.h>     /* assert() */
#include <math.h>       /* pow() */

#include "dlist.h" 

#define TRUE 1
#define FALSE 0
#define MAX_VAL 100

/*------------------- macros for printing test results -----------------------*/
#define TEST(msg) printf("\n[TEST] %s\n", msg)
#define PASS(msg) printf("  [PASS] %s\n", msg)
#define FAIL(msg) printf("  [FAIL] %s\n", msg)

/*--------------------testing functions----------------------------------------*/
static void TestCreateDestroy();
static void TestPushPop();
static void TestInsertRemove();
static void TestFind();
static void TestSplice();

/*-----------------aux functions for dealing with list------------------------*/
static int MatchInt(const void *data, void *param);
/*static void PrintDlist(dlist_ty* list);*/

/*-------------------- implementations ----------------------------------------*/
int main() 
{
    TestCreateDestroy();
    TestPushPop();
    TestInsertRemove();
    TestFind();
    TestSplice();
    
    printf("\n--- All tests finished ---\n");
    return 0;
}

/*----------------------------------tests------------------------------------*/

static void TestCreateDestroy()
{
    dlist_ty* list = DListCreate();
    TEST("DListCreate & DListDestroy");
    
    if(NULL != list && DListIsEmpty(list))
    {
        PASS("List created and is empty");
    }
    else
    {
        FAIL("Create failed or list not empty");
    }
    DListDestroy(list);
}

static void TestPushPop()
{
    dlist_ty* list = DListCreate();
    int a = 10, b = 20, c = 30;
    
    TEST("Push/Pop Front & Back");
    
    DListPushFront(list, &a); /* [10] */
    DListPushBack(list, &b);  /* [10, 20] */
    DListPushFront(list, &c); /* [30, 10, 20] */
    
    if(DListCount(list) == 3) PASS("Count is 3 after pushes");
    else FAIL("Count is incorrect after pushes");

    if(*(int*)DListIterGetData(DListBeginIter(list)) == 30) PASS("Front is 30");
    
    DListPopFront(list); /* [10, 20] */
    DListPopBack(list);  /* [10] */
    
    if(DListCount(list) == 1 && *(int*)DListIterGetData(DListBeginIter(list)) == 10)
    {
        PASS("Pop successful, remaining element is 10");
    }
    
    DListDestroy(list);
}

static void TestInsertRemove()
{
    dlist_ty* list = DListCreate();
    int data[] = {1, 2, 3};
    dlist_iter_ty iter;
    
    TEST("InsertBefore & Remove");
    
    iter = DListBeginIter(list);
    iter = DListInsertBefore(list, iter, &data[0]); /* [1] */
    iter = DListInsertBefore(list, iter, &data[1]); /* [2, 1] */
    
    if(*(int*)DListIterGetData(DListBeginIter(list)) == 2) PASS("InsertBefore worked");

    DListRemove(DListBeginIter(list)); /* Removes 2, leaves [1] */
    
    if(DListCount(list) == 1) PASS("Remove worked");

    DListDestroy(list);    
}

static void TestFind()
{
    dlist_ty* list = DListCreate();
    int a = 1, b = 2, c = 3;
    dlist_iter_ty found;
    
    TEST("DListFind");
    DListPushBack(list, &a);
    DListPushBack(list, &b);
    DListPushBack(list, &c);
    
    found = DListFind(DListBeginIter(list), DListEndIter(list), MatchInt, &b);
    
    if(!DListIterIsEqual(found, DListEndIter(list)) && *(int*)DListIterGetData(found) == 2)
    {
        PASS("Found element 2");
    }
    else
    {
        FAIL("Could not find element 2");
    }
    
    DListDestroy(list);
}

static void TestSplice()
{
    dlist_ty* l1 = DListCreate();
    dlist_ty* l2 = DListCreate();
    int a=1, b=2, c=3, d=4;
    
    TEST("DListSplice");
    DListPushBack(l1, &a);
    DListPushBack(l1, &b); /* l1: [1, 2] */
    DListPushBack(l2, &c);
    DListPushBack(l2, &d); /* l2: [3, 4] */
    
    /* Move [1, 2] from l1 to the middle of l2 */
    DListSplice(DListBeginIter(l1), DListEndIter(l1), DListIterNext(DListBeginIter(l2)));
    
    /* Expected: l1 empty, l2 [3, 1, 2, 4] */
    if(DListIsEmpty(l1) && DListCount(l2) == 4)
    {
        PASS("Splice successful: Nodes moved from l1 to l2");
    }
    else
    {
        FAIL("Splice failed: Counts are incorrect");
    }
    
    DListDestroy(l1);
    DListDestroy(l2);           
}

/*----------------- Helpers ------------------------*/

static int MatchInt(const void *data, void *param)
{
    return (*(int*)data == *(int*)param);
}
/*
static void PrintDlist(dlist_ty* list)
{
    dlist_iter_ty iter = DListBeginIter(list);
    printf("\tList: ");
    while(!DListIterIsEqual(iter, DListEndIter(list)))
    {
        printf("%d <-> ", *(int*)DListIterGetData(iter));
        iter = DListIterNext(iter);
    }
    printf("NULL\n");
}*/
