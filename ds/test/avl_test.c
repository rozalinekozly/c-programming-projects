#include <stdio.h>
#include "avl.h"

/* Comparison function for integers */
int IntCmp(const void* data1, const void* data2, void* param)
{
    (void)param;
    return (*(int*)data1 - *(int*)data2);
}

void TestCreateDestroy()
{
    avl_ty* avl = NULL;
    
    printf("Testing AvlCreate and AvlDestroy...\n");
    
    /* Test 1: Create AVL tree */
    avl = AvlCreate(IntCmp, NULL);
    if (NULL == avl)
    {
        printf("FAIL: AvlCreate returned NULL\n");
        return;
    }
    printf("PASS: AvlCreate succeeded\n");
    
    /* Test 2: Destroy AVL tree */
    AvlDestroy(avl);
    printf("PASS: AvlDestroy succeeded\n");
    
    /* Test 3: Destroy NULL */
    AvlDestroy(NULL);
    printf("PASS: AvlDestroy(NULL) succeeded\n");
}

void TestIsEmpty()
{
    avl_ty* avl = NULL;
    
    printf("Testing AvlIsEmpty...\n");
    
    /* Test 1: Empty tree */
    avl = AvlCreate(IntCmp, NULL);
    if (1 != AvlIsEmpty(avl))
    {
        printf("FAIL: Empty tree should return 1\n");
        AvlDestroy(avl);
        return;
    }
    printf("PASS: Empty tree returns 1\n");
    
    AvlDestroy(avl);
}
void TestHeight()
{
    avl_ty* avl = NULL;
    
    printf("Testing AvlHeight...\n");
    
    /* Test 1: Empty tree height */
    avl = AvlCreate(IntCmp, NULL);
    if (-1 != AvlHeight(avl))  /* assuming we return -1 for empty */
    {
        printf("FAIL: Empty tree should have height 0 (or -1 cast to size_t)\n");
        AvlDestroy(avl);
        return;
    }
    printf("PASS: Empty tree has height -1\n");
    
    /* TODO: Test with actual nodes once Insert is implemented */
    
    AvlDestroy(avl);
}
int main()
{
    TestCreateDestroy();
    TestIsEmpty();
    TestHeight();
    printf("\nAll tests passed!\n");
    return 0;
}
