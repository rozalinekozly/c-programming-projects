#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

/* ================= helpers ================= */

static int CmpInt(const void *a, const void *b, void *param)
{
    (void)param;
    return (*(int *)a > *(int *)b) - (*(int *)a < *(int *)b);
}

static int ActionSum(void *data, void *param)
{
    *(int *)param += *(int *)data;
    return 0;
}

/* ================= tests ================= */

static void TestCreateDestroy(void)
{
    bst_ty *bst = BstCreate(CmpInt, NULL);

    printf("TestCreateDestroy: ");
    if (bst != NULL)
    {
        printf("PASS\n");
        BstDestroy(bst);
    }
    else
    {
        printf("FAIL\n");
    }
}

static void TestInsertFind(void)
{
    bst_ty *bst = BstCreate(CmpInt, NULL);
    int a = 10, b = 5, c = 20;

    printf("TestInsertFind: ");

    BstInsert(bst, &a);
    BstInsert(bst, &b);
    BstInsert(bst, &c);

    if (BstFind(bst, &a) != BstItEnd(bst) &&
        BstFind(bst, &b) != BstItEnd(bst) &&
        BstFind(bst, &c) != BstItEnd(bst))
    {
        printf("PASS\n");
    }
    else
    {
        printf("FAIL\n");
    }

    BstDestroy(bst);
}

static void TestIteration(void)
{
    bst_ty *bst = BstCreate(CmpInt, NULL);
    int vals[] = {10, 5, 20, 3, 7};
    bst_iter_ty it;
    int last = -1000;
    int ok = 1;
    int i;

    printf("TestIteration: ");

    for (i = 0; i < 5; ++i)
    {
        BstInsert(bst, &vals[i]);
    }

    it = BstItBegin(bst);
    while (!BstItEqual(it, BstItEnd(bst)))
    {
        int curr = *(int *)BstGetData(it);
        if (curr < last)
        {
            ok = 0;
            break;
        }
        last = curr;
        it = BstItNext(it);
    }

    printf(ok ? "PASS\n" : "FAIL\n");
    BstDestroy(bst);
}

static void TestRemove(void)
{
    bst_ty *bst = BstCreate(CmpInt, NULL);
    int a = 10, b = 5, c = 20;

    printf("TestRemove: ");

    BstInsert(bst, &a);
    BstInsert(bst, &b);
    BstInsert(bst, &c);

    BstRemove(BstFind(bst, &a));

    if (BstFind(bst, &a) == BstItEnd(bst) &&
        BstSize(bst) == 2)
    {
        printf("PASS\n");
    }
    else
    {
        printf("FAIL\n");
    }

    BstDestroy(bst);
}

static void TestSize(void)
{
    bst_ty *bst = BstCreate(CmpInt, NULL);
    int vals[5];
    int i;

    printf("TestSize: ");

    for (i = 0; i < 5; ++i)
    {
        vals[i] = i;
        BstInsert(bst, &vals[i]);
    }

    if (BstSize(bst) == 5)
    {
        printf("PASS\n");
    }
    else
    {
        printf("FAIL\n");
    }

    BstDestroy(bst);
}

static void TestForEach(void)
{
    bst_ty *bst = BstCreate(CmpInt, NULL);
    int vals[] = {1, 2, 3};
    int sum = 0;
    int i;

    printf("TestForEach: ");

    for (i = 0; i < 3; ++i)
    {
        BstInsert(bst, &vals[i]);
    }

    BstForEach(BstItBegin(bst), BstItEnd(bst), ActionSum, &sum);

    if (sum == 6)
    {
        printf("PASS\n");
    }
    else
    {
        printf("FAIL\n");
    }

    BstDestroy(bst);
}

/* ================= main ================= */

int main(void)
{
    TestCreateDestroy();
    TestInsertFind();
    TestIteration();
    TestRemove();
    TestSize();
    TestForEach();

    return 0;
}

