#include <stdio.h>
#include "avl.h"

int IntCmp(const void* data1, const void* data2, void* param)
{
    (void)param;
    return (*(int*)data1 - *(int*)data2);
}

int PrintInt(void* data, void* param)
{
    (void)param;
    printf("%d ", *(int*)data);
    return 0;
}

void TestCreateDestroy()
{
    avl_ty* avl = NULL;
    
    printf("TESTING AvlCreate and AvlDestroy\n");
    
    avl = AvlCreate(IntCmp, NULL);
    if (NULL == avl)
    {
        printf("FAIL: AvlCreate returned NULL\n");
        return;
    }
    printf("PASS: AvlCreate succeeded\n");
    
    AvlDestroy(avl);
    printf("PASS: AvlDestroy succeeded\n");
    
    AvlDestroy(NULL);
    printf("PASS: AvlDestroy(NULL) succeeded\n\n");
}

void TestIsEmpty()
{
    avl_ty* avl = NULL;
    int data = 10;
    
    printf("TESTING AvlIsEmpty\n");
    
    avl = AvlCreate(IntCmp, NULL);
    if (1 != AvlIsEmpty(avl))
    {
        printf("FAIL: Empty tree should return 1\n");
        AvlDestroy(avl);
        return;
    }
    printf("PASS: Empty tree returns 1\n");
    
    AvlInsert(avl, &data);
    if (0 != AvlIsEmpty(avl))
    {
        printf("FAIL: Non-empty tree should return 0\n");
        AvlDestroy(avl);
        return;
    }
    printf("PASS: Non-empty tree returns 0\n\n");
    
    AvlDestroy(avl);
}

void TestHeight()
{
    avl_ty* avl = NULL;
    int data1 = 10, data2 = 5, data3 = 15;
    
    printf("TESTING AvlHeight\n");
    
    avl = AvlCreate(IntCmp, NULL);
    if (0 != AvlHeight(avl))
    {
        printf("FAIL: Empty tree should have height 0\n");
        AvlDestroy(avl);
        return;
    }
    printf("PASS: Empty tree has height 0\n");
    
    printf("Empty tree height: %lu\n", (unsigned long)AvlHeight(avl));
    
    AvlInsert(avl, &data1);
    printf("After inserting 10, height: %lu\n", (unsigned long)AvlHeight(avl));
    
    AvlInsert(avl, &data2);
    printf("After inserting 5, height: %lu\n", (unsigned long)AvlHeight(avl));
    
    AvlInsert(avl, &data3);
    printf("After inserting 15, height: %lu\n\n", (unsigned long)AvlHeight(avl));
    
    AvlDestroy(avl);
}

void TestInsert()
{
    avl_ty* avl = NULL;
    int data1 = 10, data2 = 5, data3 = 15, data4 = 3, data5 = 7;
    
    printf("TESTING AvlInsert\n");
    
    avl = AvlCreate(IntCmp, NULL);
    
    if (0 != AvlInsert(avl, &data1))
    {
        printf("FAIL: Insert 10 failed\n");
        AvlDestroy(avl);
        return;
    }
    printf("PASS: Inserted 10\n");
    
    if (0 != AvlInsert(avl, &data2))
    {
        printf("FAIL: Insert 5 failed\n");
        AvlDestroy(avl);
        return;
    }
    printf("PASS: Inserted 5\n");
    
    if (0 != AvlInsert(avl, &data3))
    {
        printf("FAIL: Insert 15 failed\n");
        AvlDestroy(avl);
        return;
    }
    printf("PASS: Inserted 15\n");
    
    if (0 == AvlInsert(avl, &data1))
    {
        printf("FAIL: Duplicate insert should fail\n");
        AvlDestroy(avl);
        return;
    }
    printf("PASS: Duplicate insert rejected\n");
    
    AvlInsert(avl, &data4);
    AvlInsert(avl, &data5);
    
    printf("Tree contents (in-order): ");
    AvlForEach(avl, IN_ORDER, PrintInt, NULL);
    printf("\n\n");
    
    AvlDestroy(avl);
}

void TestFind()
{
    avl_ty* avl = NULL;
    int data1 = 10, data2 = 5, data3 = 15, data4 = 3, data5 = 7;
    int search1 = 7, search2 = 100;
    int* found = NULL;
    
    printf("TESTING AvlFind\n");
    
    avl = AvlCreate(IntCmp, NULL);
    
    AvlInsert(avl, &data1);
    AvlInsert(avl, &data2);
    AvlInsert(avl, &data3);
    AvlInsert(avl, &data4);
    AvlInsert(avl, &data5);
    
    found = (int*)AvlFind(avl, &search1);
    if (NULL == found || *found != 7)
    {
        printf("FAIL: Should find 7\n");
        AvlDestroy(avl);
        return;
    }
    printf("PASS: Found 7\n");
    
    found = (int*)AvlFind(avl, &search2);
    if (NULL != found)
    {
        printf("FAIL: Should not find 100\n");
        AvlDestroy(avl);
        return;
    }
    printf("PASS: Did not find 100 (correct)\n\n");
    
    AvlDestroy(avl);
}

void TestRemove()
{
    avl_ty* avl = NULL;
    int data1 = 10, data2 = 5, data3 = 15, data4 = 3, data5 = 7, data6 = 12, data7 = 20;
    int remove1 = 5, remove2 = 15, remove3 = 10, remove4 = 100;
    
    printf("TESTING AvlRemove\n");
    
    avl = AvlCreate(IntCmp, NULL);
    
    AvlInsert(avl, &data1);
    AvlInsert(avl, &data2);
    AvlInsert(avl, &data3);
    AvlInsert(avl, &data4);
    AvlInsert(avl, &data5);
    AvlInsert(avl, &data6);
    AvlInsert(avl, &data7);
    
    printf("Initial tree (in-order): ");
    AvlForEach(avl, IN_ORDER, PrintInt, NULL);
    printf("\n");
    
    if (0 != AvlRemove(avl, &remove1))
    {
        printf("FAIL: Remove 5 failed\n");
        AvlDestroy(avl);
        return;
    }
    printf("After removing 5: ");
    AvlForEach(avl, IN_ORDER, PrintInt, NULL);
    printf("\n");
    
    if (0 != AvlRemove(avl, &remove2))
    {
        printf("FAIL: Remove 15 failed\n");
        AvlDestroy(avl);
        return;
    }
    printf("After removing 15: ");
    AvlForEach(avl, IN_ORDER, PrintInt, NULL);
    printf("\n");
    
    if (0 != AvlRemove(avl, &remove3))
    {
        printf("FAIL: Remove 10 failed\n");
        AvlDestroy(avl);
        return;
    }
    printf("After removing 10: ");
    AvlForEach(avl, IN_ORDER, PrintInt, NULL);
    printf("\n");
    
    if (0 == AvlRemove(avl, &remove4))
    {
        printf("FAIL: Remove non-existing should fail\n");
        AvlDestroy(avl);
        return;
    }
    printf("PASS: Remove non-existing correctly failed\n\n");
    
    AvlDestroy(avl);
}

void TestSize()
{
    avl_ty* avl = NULL;
    int data1 = 10, data2 = 5, data3 = 15;
    
    printf("TESTING AvlSize\n");
    
    avl = AvlCreate(IntCmp, NULL);
    
    printf("Empty tree size: %lu\n", (unsigned long)AvlSize(avl));
    
    AvlInsert(avl, &data1);
    printf("After insert 10, size: %lu\n", (unsigned long)AvlSize(avl));
    
    AvlInsert(avl, &data2);
    printf("After insert 5, size: %lu\n", (unsigned long)AvlSize(avl));
    
    AvlInsert(avl, &data3);
    printf("After insert 15, size: %lu\n", (unsigned long)AvlSize(avl));
    
    AvlRemove(avl, &data2);
    printf("After remove 5, size: %lu\n\n", (unsigned long)AvlSize(avl));
    
    AvlDestroy(avl);
}

void TestTraversals()
{
    avl_ty* avl = NULL;
    int data1 = 10, data2 = 5, data3 = 15, data4 = 3, data5 = 7;
    
    printf("TESTING Traversals\n");
    
    avl = AvlCreate(IntCmp, NULL);
    
    AvlInsert(avl, &data1);
    AvlInsert(avl, &data2);
    AvlInsert(avl, &data3);
    AvlInsert(avl, &data4);
    AvlInsert(avl, &data5);
    
    printf("In-order:   ");
    AvlForEach(avl, IN_ORDER, PrintInt, NULL);
    printf("\n");
    
    printf("Pre-order:  ");
    AvlForEach(avl, PRE_ORDER, PrintInt, NULL);
    printf("\n");
    
    printf("Post-order: ");
    AvlForEach(avl, POST_ORDER, PrintInt, NULL);
    printf("\n\n");
    
    AvlDestroy(avl);
}

int main()
{
    TestCreateDestroy();
    TestIsEmpty();
    TestHeight();
    TestInsert();
    TestFind();
    TestRemove();
    TestSize();
    TestTraversals();
    
    printf("All BST tests completed!\n");
    
    return 0;
}
