#include "ws1.h"
#include <stdio.h>

void TestSwap(void)
{
    int a, b;

    printf("Testing swap function\n");
    printf("Enter first number: ");
    scanf("%d", &a);
    printf("Enter second number: ");
    scanf("%d", &b);

    printf("Before swap: a = %d, b = %d\n", a, b);
    swap(&a, &b);
    printf("After swap:  a = %d, b = %d\n", a, b);

    if (a != b)
    {
        printf("TEST PASSED\n\n");
    }
    else
    {
        printf("TEST FAILED\n\n");
    }
}

