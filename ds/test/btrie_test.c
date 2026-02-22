/*
developer: rozaline
*/
/*----------------------------------------------------------------------------*/
#include <stdio.h>   /* printf */
#include <stddef.h>  /* size_t */

#include "btrie.h"   /* API */
/*----------------------------------------------------------------------------*/
#define GREEN   "\033[0;32m"
#define RED     "\033[0;31m"
#define RESET   "\033[0m"

#define TEST(name, condition)                                          \
    do {                                                               \
        if (condition)                                                 \
        {                                                              \
            printf(GREEN "[PASS]" RESET " %s\n", name);               \
        }                                                              \
        else                                                           \
        {                                                              \
            printf(RED "[FAIL]" RESET " %s (line %d)\n", name, __LINE__); \
        }                                                              \
    } while (0)
/*----------------------------------------------------------------------------*/
static void TestCreateDestroy(void);
static void TestGetBasic(void);
static void TestGetNextAvailable(void);
static void TestGetFullTrie(void);
static void TestRelease(void);
static void TestReleaseAndReuse(void);
static void TestCountAvailable(void);
static void TestCountAfterGetAndRelease(void);
static void TestNullSafety(void);
/*----------------------------------------------------------------------------*/
int main(void)
{
    printf("=== BTrieCreate / BTrieDestroy ===\n");
    TestCreateDestroy();

    printf("\n=== BTrieGet Basic ===\n");
    TestGetBasic();

    printf("\n=== BTrieGet Next Available ===\n");
    TestGetNextAvailable();

    printf("\n=== BTrieGet Full Trie ===\n");
    TestGetFullTrie();

    printf("\n=== BTrieRelease ===\n");
    TestRelease();

    printf("\n=== BTrieRelease and Reuse ===\n");
    TestReleaseAndReuse();

    printf("\n=== BTrieCountAvailable ===\n");
    TestCountAvailable();

    printf("\n=== BTrieCountAvailable After Get/Release ===\n");
    TestCountAfterGetAndRelease();

    printf("\n=== NULL Safety ===\n");
    TestNullSafety();

    printf("\n=== Done ===\n");

    return 0;
}
/*----------------------------------------------------------------------------*/
static void TestCreateDestroy(void)
{
    btrie_ty* trie = NULL;

    trie = BTrieCreate(4);
    TEST("BTrieCreate returns non-NULL", trie != NULL);

    BTrieDestroy(trie);
    TEST("BTrieDestroy does not crash", 1);

    /* destroy NULL - should not crash */
    BTrieDestroy(NULL);
    TEST("BTrieDestroy(NULL) does not crash", 1);
}
/*----------------------------------------------------------------------------*/
static void TestGetBasic(void)
{
    btrie_ty* trie = NULL;
    num_ty result = 0;

    trie = BTrieCreate(4);

    /* address 0 is reserved at create time, first available should be 1 */
    result = BTrieGet(trie, 1);
    TEST("BTrieGet returns requested address when available", result == 1);

    /* getting the same address again should return a different one */
    result = BTrieGet(trie, 1);
    TEST("BTrieGet doesn't return already-used address", result != 1);

    BTrieDestroy(trie);
}
/*----------------------------------------------------------------------------*/
static void TestGetNextAvailable(void)
{
    btrie_ty* trie = NULL;
    num_ty result = 0;

    trie = BTrieCreate(4);

    /* fill addresses 1 and 2, ask for 1 again - should get 3 */
    BTrieGet(trie, 1);
    BTrieGet(trie, 2);

    result = BTrieGet(trie, 1);
    TEST("BTrieGet finds next available when requested is taken", result == 3);

    BTrieDestroy(trie);
}
/*----------------------------------------------------------------------------*/
static void TestGetFullTrie(void)
{
    btrie_ty* trie = NULL;
    num_ty result = 0;
    num_ty i = 0;
    num_ty max = 0;

    /* 3 bits = 8 addresses (0..7), 0 is reserved */
    trie = BTrieCreate(3);
    max = 7; /* 2^3 - 1 */

    for (i = 1; i <= max; ++i)
    {
        BTrieGet(trie, i);
    }

    /* trie is now full, should return 0 */
    result = BTrieGet(trie, 1);
    TEST("BTrieGet returns 0 when trie is full", result == 0);

    BTrieDestroy(trie);
}
/*----------------------------------------------------------------------------*/
static void TestRelease(void)
{
    btrie_ty* trie = NULL;
    size_t before = 0;
    size_t after = 0;

    trie = BTrieCreate(4);

    BTrieGet(trie, 1);
    BTrieGet(trie, 2);
    BTrieGet(trie, 3);

    before = BTrieCountAvailable(trie);

    BTrieRelease(trie, 2);

    after = BTrieCountAvailable(trie);

    TEST("BTrieRelease increases available count by 1", after == before + 1);

    BTrieDestroy(trie);
}
/*----------------------------------------------------------------------------*/
static void TestReleaseAndReuse(void)
{
    btrie_ty* trie = NULL;
    num_ty result = 0;

    trie = BTrieCreate(4);

    BTrieGet(trie, 5);
    BTrieRelease(trie, 5);

    /* after release, requesting 5 should succeed and return 5 */
    result = BTrieGet(trie, 5);
    TEST("Released address can be reused", result == 5);

    BTrieDestroy(trie);
}
/*----------------------------------------------------------------------------*/
static void TestCountAvailable(void)
{
    btrie_ty* trie = NULL;
    size_t count = 0;

    /* 3 bits = 8 total, 1 reserved (address 0) = 7 available */
    trie = BTrieCreate(3);

    count = BTrieCountAvailable(trie);
    TEST("BTrieCountAvailable after create = 2^bits - 1", count == 7);

    BTrieDestroy(trie);
}
/*----------------------------------------------------------------------------*/
static void TestCountAfterGetAndRelease(void)
{
    btrie_ty* trie = NULL;
    size_t count = 0;

    /* 3 bits = 8 total, 1 reserved = 7 available */
    trie = BTrieCreate(3);

    BTrieGet(trie, 1);
    BTrieGet(trie, 2);
    BTrieGet(trie, 3);

    count = BTrieCountAvailable(trie);
    TEST("Count decreases by 3 after 3 gets", count == 4);

    BTrieRelease(trie, 1);
    BTrieRelease(trie, 2);

    count = BTrieCountAvailable(trie);
    TEST("Count increases by 2 after 2 releases", count == 6);

    BTrieDestroy(trie);
}
/*----------------------------------------------------------------------------*/
static void TestNullSafety(void)
{
    /* BTrieDestroy(NULL) - already tested in TestCreateDestroy */
    /* BTrieRelease(NULL) - should not crash */
    BTrieRelease(NULL, 1);
    TEST("BTrieRelease(NULL, ...) does not crash", 1);
}
/*----------------------------------------------------------------------------*/
