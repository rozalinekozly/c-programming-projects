#include <stdio.h>      /* printf */
#include <stdlib.h>     /* malloc, free */

#include "fsa.h"

#define BLOCK_SIZE 32
#define NUM_BLOCKS 5

static int TestSuggestedSize(void);
static int TestInitAndAvailable(void);
static int TestAlloc(void);
static int TestFree(void);

static void PrintResult(const char *test_name, int result);

int main(void)
{
    int failures = 0;

    printf("===== FSA TEST START =====\n");

    failures += TestSuggestedSize();
    failures += TestInitAndAvailable();
    failures += TestAlloc();
    failures += TestFree();

    printf("===== FSA TEST END =====\n");

    if (0 == failures)
    {
        printf("ALL TESTS PASSED\n");
    }
    else
    {
        printf("FAILED TESTS: %d \n", failures);
    }

    return 0;
}

/*--------------------------------Tests --------------------------------*/

static int TestSuggestedSize(void)
{
    size_t size = FsaSuggestedSize(NUM_BLOCKS, BLOCK_SIZE);

    PrintResult("TestSuggestedSize", size > 0);

    return (size > 0) ? 0 : 1;
}

static int TestInitAndAvailable(void)
{
    size_t pool_size = FsaSuggestedSize(NUM_BLOCKS, BLOCK_SIZE);
    void *pool = malloc(pool_size);
    fsa_ty *fsa = NULL;
    size_t available = 0;
    int result = 1;

    if (NULL == pool)
    {
        PrintResult("TestInitAndAvailable", 0);
        return 1;
    }

    fsa = FsaInit(pool, pool_size, BLOCK_SIZE);
    available = FsaAvailableBlocks(fsa);

    result = (available == NUM_BLOCKS);

    PrintResult("TestInitAndAvailable", result);

    free(pool);

    return result ? 0 : 1;
}

static int TestAlloc(void)
{
    size_t pool_size = FsaSuggestedSize(NUM_BLOCKS, BLOCK_SIZE);
    void *pool = malloc(pool_size);
    fsa_ty *fsa = NULL;
    void *block = NULL;
    size_t i = 0;
    int success = 1;

    if (NULL == pool)
    {
        PrintResult("TestAlloc", 0);
        return 1;
    }

    fsa = FsaInit(pool, pool_size, BLOCK_SIZE);

    for (i = 0; i < NUM_BLOCKS; ++i)
    {
        block = FsaAlloc(fsa);
        if (NULL == block)
        {
            success = 0;
            break;
        }
    }

    if (FsaAlloc(fsa) != NULL)
    {
        success = 0;
    }

    PrintResult("TestAlloc", success);

    free(pool);

    return success ? 0 : 1;
}

static int TestFree(void)
{
    size_t pool_size = FsaSuggestedSize(NUM_BLOCKS, BLOCK_SIZE);
    void *pool = malloc(pool_size);
    fsa_ty *fsa = NULL;
    void *block1 = NULL;
    void *block2 = NULL;
    size_t available = 0;
    int result = 1;

    if (NULL == pool)
    {
        PrintResult("TestFree", 0);
        return 1;
    }

    fsa = FsaInit(pool, pool_size, BLOCK_SIZE);

    block1 = FsaAlloc(fsa);
    block2 = FsaAlloc(fsa);

    FsaFree(fsa, block1);
    FsaFree(fsa, block2);

    available = FsaAvailableBlocks(fsa);
    result = (available == NUM_BLOCKS);

    PrintResult("TestFree", result);

    free(pool);

    return result ? 0 : 1;
}



static void PrintResult(const char *test_name, int result)
{
    printf("%s: %s\n", test_name, result ? "PASS" : "FAIL");
}

