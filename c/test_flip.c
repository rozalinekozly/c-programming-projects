#include "ws1.h"
#include <stdio.h>

void TestFlip(void)
{
    int input = 12340;
    int expected = 4321;
    int result = flip(input);

    printf("Testing flip function\n");
    printf("Input: %d\n", input);
    printf("flip(%d) = %d\n", input, result);
    printf("Expected: %d\n", expected);

    if (result == expected)
    {
        printf("TEST PASSED\n\n");
    }
    else
    {
        printf("TEST FAILED\n\n");
    }
}

