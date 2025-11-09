#include "ws1.h"
#include <stdio.h>
#include <math.h>

void TestPower(void)
{
    int n;
    float my_result, lib_result;

    printf("Testing power function\n");
    printf("Enter n value: ");
    scanf("%d", &n);

    my_result = power(n);
    lib_result = pow(10, n);

    printf("power(%d) = %f\n", n, my_result);
    printf("pow(10, %d) = %f\n", n, lib_result);

    if (fabs(my_result - lib_result) < 0.0001)
    {
        printf("TEST PASSED\n\n");
    }
    else
    {
        printf("TEST FAILED\n\n");
    }
}

