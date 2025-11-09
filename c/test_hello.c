#include "ws1.h"
#include <stdio.h>
#include <string.h>

void TestHello(void)
{
    const char expected[] = "22 48 65 6C 6C 6F 20 57 6F 72 6C 64 21 22";
    char actual[256];
    const char str[] = "\"Hello World!\"";
    int i = 0;
    char *p = actual;

    printf("Testing Hello function\n");

 
    while (str[i] != '\0')
    {
        sprintf(p, "%02X", str[i]);
        p += 2;
        if (str[i + 1] != '\0')
        {
            sprintf(p, " ");
            p++;
        }
        i++;
    }
    *p = '\0';

    if (strcmp(actual, expected) == 0)
    {
        printf("TEST PASSED\n\n");
    }
    else
    {
        printf("TEST FAILED\nExpected: %s\nGot:      %s\n\n", expected, actual);
    }
}

