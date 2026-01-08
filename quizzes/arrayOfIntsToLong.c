#include <stdio.h> 

long* sumInPairsToLongs(int ints[], size_t numOfElements)
{
    size_t i;
    size_t j;
    long sum;
    long* longs;
    
    longs = (long*)ints;
    j = 0;
    
    for (i = 0; i < numOfElements; i += 2)
    {
        sum = (long)ints[i] + (long)ints[i+1];
        longs[j] = sum;
        j++;
    }
    
    return longs;
}

int main()
{
    long* result1;
    long* result2;
    long* result3;
    long* result4;
    long* result5;
    
    int test1[] = {10, 20, 30, 40};
    int test2[] = {1000000, 2000000, 500000, 750000};
    int test3[] = {-100, 50, -200, -300};
    int test4[] = {100, -50, -200, 300};
    int test5[] = {0, 0, 100, 0};
    
    /* Test 1: Simple positive numbers */
    printf("Test 1: Simple positive numbers\n");
    result1 = sumInPairsToLongs(test1, 4);
    printf("Pair 1: %ld (expected: 30)\n", result1[0]);
    printf("Pair 2: %ld (expected: 70)\n", result1[1]);
    printf("\n");
    
    /* Test 2: Larger numbers */
    printf("Test 2: Larger numbers\n");
    result2 = sumInPairsToLongs(test2, 4);
    printf("Pair 1: %ld (expected: 3000000)\n", result2[0]);
    printf("Pair 2: %ld (expected: 1250000)\n", result2[1]);
    printf("\n");
    
    /* Test 3: Negative numbers */
    printf("Test 3: Negative numbers\n");
    result3 = sumInPairsToLongs(test3, 4);
    printf("Pair 1: %ld (expected: -50)\n", result3[0]);
    printf("Pair 2: %ld (expected: -500)\n", result3[1]);
    printf("\n");
    
    /* Test 4: Mixed positive and negative */
    printf("Test 4: Mixed positive and negative\n");
    result4 = sumInPairsToLongs(test4, 4);
    printf("Pair 1: %ld (expected: 50)\n", result4[0]);
    printf("Pair 2: %ld (expected: 100)\n", result4[1]);
    printf("\n");
    
    /* Test 5: Zero values */
    printf("Test 5: Zero values\n");
    result5 = sumInPairsToLongs(test5, 4);
    printf("Pair 1: %ld (expected: 0)\n", result5[0]);
    printf("Pair 2: %ld (expected: 100)\n", result5[1]);
    printf("\n");
    
    return 0;
}
