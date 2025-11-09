#include "ws1.h"
#include <stdio.h>
void PrintHelloHex(void)
{
    const char str[] = "\"Hello World!\"";
    int i = 0;

    while (str[i] != '\0')
    {
        printf("%02X ", str[i]); 
        i++;
    }

    printf("\n");
}

