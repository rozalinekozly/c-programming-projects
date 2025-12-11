/*--------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer  : steve
worksheet : 12 (ds - stack)
version   : 3
date      : 10 Dec 2025
stage     : pre-mimir
----------------------------------------------------------------------------*/

#include <stdio.h>          /* printf()     */
#include <stdlib.h>         /* rand()       */
#include <limits.h>         /* INT_MAX      */
#include <math.h>           /* pow()        */

#include "../include/stack.h"   /* header file (API) */

#define ASCII_SIZE   256
#define CAPACITY     100

static void TestInt(size_t capacity, int* elements, size_t count);
static void TestFloat(size_t capacity, float* elements, size_t count);
static void TestChar(size_t capacity, char* elements, size_t count);

static size_t test_num = 1;

int main()
{
    size_t capacity = CAPACITY;
    size_t i = 0;

    int   elements_int[CAPACITY];
    float elements_float[CAPACITY];
    char  elements_char[CAPACITY];

    /* generating random values */
    for (i = 0; i < capacity; i++)
    {
        elements_int[i]   = pow(-1, i) * (rand() % INT_MAX);
        elements_float[i] = pow(-1, i) * ((float)(rand() % INT_MAX) / (rand() + 1));
        elements_char[i]  = rand() % ASCII_SIZE;
    }

    TestInt(capacity, elements_int, capacity);
    TestFloat(capacity, elements_float, capacity);
    TestChar(capacity, elements_char, capacity);

    return 0;
}

/**----------------------------- INT TEST -----------------------------**/

static void TestInt(size_t capacity, int *elements, size_t count)
{
    stack_ty* stack_p = NULL;
    size_t i = 0;
    size_t before = 0;
    int val = 0;

    printf("\n--------- TEST %lu: INT ---------\n", test_num++);

    stack_p = StackCreate(capacity, sizeof(int));
    if (NULL == stack_p)
    {
        printf("create\t\tFAILED (NULL returned)\n");
        return;
    }
    printf("create\t\tPASSED\n");

    if (capacity != StackCapacity(stack_p))
    {
        printf("capacity\tFAILED\nexpected: %lu\nactual:   %lu\n",
            capacity, StackCapacity(stack_p));
        return;
    }
    printf("capacity\tPASSED\n");

    if (0 != StackSize(stack_p))
    {
        printf("size\t\tFAILED\nexpected: 0\nactual:   %lu\n",
            StackSize(stack_p));
        return;
    }
    printf("size\t\tPASSED\n");

    for (i = 0 ; i < count ; i++)
    {
        StackPush(stack_p, &elements[i]);

        if ((i + 1) != StackSize(stack_p))
        {
            printf("push\t\tFAILED at index %lu\nexpected size: %lu\nactual size: %lu\n",
                i, (unsigned long)(i + 1), (unsigned long)StackSize(stack_p));
            return;
        }
    }
    printf("push\t\tPASSED\n");

    for (i = 0 ; i < count ; i++)
    {
        before = StackSize(stack_p);
        val = *(int*)StackPeek(stack_p);

        if (before != StackSize(stack_p))
        {
            printf("peek\t\tFAILED (size changed)\nbefore: %lu\nafter:%lu\n",
                before, StackSize(stack_p));
            return;
        }

        StackPop(stack_p);

        if (elements[count - 1 - i] != val)
        {
            printf("pop-peek\tFAILED at index %lu\nexpected: %d\ngot:%d\n",
                i, elements[count - 1 - i], val);
            return;
        }
    }
    printf("peek/pop\tPASSED\n");

    if (0 != StackIsEmpty(stack_p))
    {
        /* StackIsEmpty returns 1 when empty, so failure means not empty */
        if (1 != StackIsEmpty(stack_p))
        {
            printf("empty\t\tFAILED (stack not empty)\ncurrent size: %lu\n",
                StackSize(stack_p));
            return;
        }
    }
    printf("empty\t\tPASSED\n");

    StackDestroy(stack_p);
    printf("destroy\t\tPASSED\n");
}

/**----------------------------- FLOAT TEST -----------------------------**/

static void TestFloat(size_t capacity, float *elements, size_t count)
{
    stack_ty* stack_p = NULL;
    size_t i = 0;
    size_t before = 0;
    float val = 0;

    printf("\n--------- TEST %lu: FLOAT ---------\n", test_num++);

    stack_p = StackCreate(capacity, sizeof(float));
    if (NULL == stack_p)
    {
        printf("create\t\tFAILED (NULL returned)\n");
        return;
    }
    printf("create\t\tPASSED\n");

    if (capacity != StackCapacity(stack_p))
    {
        printf("capacity\tFAILED\nexpected: %lu\nactual:%lu\n",
            capacity, StackCapacity(stack_p));
        return;
    }
    printf("capacity\tPASSED\n");

    if (0 != StackSize(stack_p))
    {
        printf("size\t\tFAILED\nexpected: 0\nactual:%lu\n",
            StackSize(stack_p));
        return;
    }
    printf("size\t\tPASSED\n");

    for (i = 0 ; i < count ; i++)
    {
        StackPush(stack_p, &elements[i]);

        if ((i + 1) != StackSize(stack_p))
        {
            printf("push\t\tFAILED at index %lu\nexpected size: %lu\nactual size:%lu\n",
                i, (unsigned long)(i + 1), (unsigned long)StackSize(stack_p));
            return;
        }
    }
    printf("push\t\tPASSED\n");

    for (i = 0 ; i < count ; i++)
    {
        before = StackSize(stack_p);
        val = *(float*)StackPeek(stack_p);

        if (before != StackSize(stack_p))
        {
            printf("peek\t\tFAILED (size changed)\nbefore: %lu\nafter:%lu\n",
                before, StackSize(stack_p));
            return;
        }

        StackPop(stack_p);

        if (elements[count - 1 - i] != val)
        {
            printf("pop-peek\tFAILED at index %lu\nexpected: %f\ngot: %f\n",
                i, elements[count - 1 - i], val);
            return;
        }
    }
    printf("peek/pop\tPASSED\n");

    if (0 != StackIsEmpty(stack_p))
    {
        if (1 != StackIsEmpty(stack_p))
        {
            printf("empty\t\tFAILED (stack not empty)\ncurrent size: %lu\n",
                StackSize(stack_p));
            return;
        }
    }
    printf("empty\t\tPASSED\n");

    StackDestroy(stack_p);
    printf("destroy\t\tPASSED\n");
}

/**----------------------------- CHAR TEST -----------------------------**/

static void TestChar(size_t capacity, char *elements, size_t count)
{
    stack_ty *stack_p = NULL;
    size_t i = 0;
    size_t before = 0;
    char val = 0;

    printf("\n--------- TEST %lu: CHAR ---------\n", test_num++);

    stack_p = StackCreate(capacity, sizeof(char));
    if (NULL == stack_p)
    {
        printf("create\t\tFAILED (NULL returned)\n");
        return;
    }
    printf("create\t\tPASSED\n");

    if (capacity != StackCapacity(stack_p))
    {
        printf("capacity\tFAILED\nexpected: %lu\nactual:%lu\n",
            capacity, StackCapacity(stack_p));
        return;
    }
    printf("capacity\tPASSED\n");

    if (0 != StackSize(stack_p))
    {
        printf("size\t\tFAILED\nexpected: 0\nactual: %lu\n",
            StackSize(stack_p));
        return;
    }
    printf("size\t\tPASSED\n");

    for (i = 0 ; i < count ; i++)
    {
        StackPush(stack_p, &elements[i]);

        if ((i + 1) != StackSize(stack_p))
        {
            printf("push\t\tFAILED at index %lu\nexpected size: %lu\nactual size:%lu\n",
                i, (unsigned long)(i + 1), (unsigned long)StackSize(stack_p));
            return;
        }
    }
    printf("push\t\tPASSED\n");

    for (i = 0 ; i < count ; i++)
    {
        before = StackSize(stack_p);
        val = *(char*)StackPeek(stack_p);

        if (before != StackSize(stack_p))
        {
            printf("peek\t\tFAILED (size changed)\nbefore: %lu\nafter:%lu\n",
                before, StackSize(stack_p));
            return;
        }

        StackPop(stack_p);

        if (elements[count - 1 - i] != val)
        {
            printf("pop-peek\tFAILED at index %lu\nexpected: '%c' (ASCII %d)\ngot:'%c' (ASCII %d)\n",
                i,
                elements[count - 1 - i], elements[count - 1 - i],
                val, val);
            return;
        }
    }
    printf("peek/pop\tPASSED\n");

    if (0 != StackIsEmpty(stack_p))
    {
        if (1 != StackIsEmpty(stack_p))
        {
            printf("empty\t\tFAILED (stack not empty)\ncurrent size: %lu\n",
                StackSize(stack_p));
            return;
        }
    }
    printf("empty\t\tPASSED\n");

    StackDestroy(stack_p);
    printf("destroy\t\tPASSED\n");
}

