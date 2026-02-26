#include "btrie.h"
#include "test_utils.h"
/*---------------------------------------------------------------------------*/
#define BITS_3  3
#define BITS_4  4
/*---------------------------------------------------------------------------*/
static void TestCreateDestroy(void);
static void TestGetBasic(void);
static void TestGetNextAvailable(void);
static void TestGetFullTrie(void);
static void TestRelease(void);
static void TestReleaseAndReuse(void);
static void TestCountAvailable(void);
static void TestCountAfterGetAndRelease(void);
/*---------------------------------------------------------------------------*/
int main(void)
{
    TestSuiteBegin("BTrié Tests");

    TestPrintSection("Create Destroy Tests");
    TestCreateDestroy();

    TestPrintSection("Get Basic Tests");
    TestGetBasic();

    TestPrintSection("Get Next Available Tests");
    TestGetNextAvailable();

    TestPrintSection("Get Full Trie Tests");
    TestGetFullTrie();

    TestPrintSection("Release Tests");
    TestRelease();

    TestPrintSection("Release And Reuse Tests");
    TestReleaseAndReuse();

    TestPrintSection("Count Available Tests");
    TestCountAvailable();

    TestPrintSection("Count After Get And Release Tests");
    TestCountAfterGetAndRelease();

    return TestSuiteEnd();
}
/*---------------------------------------------------------------------------*/
static void TestCreateDestroy(void)
{
    btrie_ty* trie = BTrieCreate(BITS_4);

    ASSERT_NOT_NULL(trie);

    BTrieDestroy(trie);
    ASSERT_TRUE(1); /* destroy did not crash */

    BTrieDestroy(NULL);
    ASSERT_TRUE(1); /* destroy NULL did not crash */
}
/*---------------------------------------------------------------------------*/
static void TestGetBasic(void)
{
    btrie_ty* trie = BTrieCreate(BITS_4);
    num_ty result = 0;

    /* address 0 reserved at create, first available should be 1 */
    result = BTrieGet(trie, 1);
    ASSERT_SIZE(1, result);

    /* same address again should return different one */
    result = BTrieGet(trie, 1);
    ASSERT_TRUE(1 != result);

    BTrieDestroy(trie);
}
/*---------------------------------------------------------------------------*/
static void TestGetNextAvailable(void)
{
    btrie_ty* trie = BTrieCreate(BITS_4);
    num_ty result = 0;

    BTrieGet(trie, 1);
    BTrieGet(trie, 2);

    /* 1 and 2 taken, should get 3 */
    result = BTrieGet(trie, 1);
    ASSERT_SIZE(3, result);

    BTrieDestroy(trie);
}
/*---------------------------------------------------------------------------*/
static void TestGetFullTrie(void)
{
    btrie_ty* trie = BTrieCreate(BITS_3);
    num_ty result = 0;
    num_ty i = 0;

    /* 3 bits = 8 addresses, 0 reserved, fill 1..7 */
    for (i = 1; i <= 7; ++i)
    {
        BTrieGet(trie, i);
    }

    /* trie full, should return 0 */
    result = BTrieGet(trie, 1);
    ASSERT_SIZE(0, result);

    BTrieDestroy(trie);
}
/*---------------------------------------------------------------------------*/
static void TestRelease(void)
{
    btrie_ty* trie = BTrieCreate(BITS_4);
    size_t before = 0;
    size_t after = 0;

    BTrieGet(trie, 1);
    BTrieGet(trie, 2);
    BTrieGet(trie, 3);

    before = BTrieCountAvailable(trie);
    BTrieRelease(trie, 2);
    after = BTrieCountAvailable(trie);

    ASSERT_SIZE(before + 1, after);

    BTrieDestroy(trie);
}
/*---------------------------------------------------------------------------*/
static void TestReleaseAndReuse(void)
{
    btrie_ty* trie = BTrieCreate(BITS_4);
    num_ty result = 0;

    BTrieGet(trie, 5);
    BTrieRelease(trie, 5);

    result = BTrieGet(trie, 5);
    ASSERT_SIZE(5, result);

    BTrieDestroy(trie);
}
/*---------------------------------------------------------------------------*/
static void TestCountAvailable(void)
{
    btrie_ty* trie = BTrieCreate(BITS_3);

    /* 3 bits = 8 total, 1 reserved = 7 available */
    ASSERT_SIZE(7, BTrieCountAvailable(trie));

    BTrieDestroy(trie);
}
/*---------------------------------------------------------------------------*/
static void TestCountAfterGetAndRelease(void)
{
    btrie_ty* trie = BTrieCreate(BITS_3);

    BTrieGet(trie, 1);
    BTrieGet(trie, 2);
    BTrieGet(trie, 3);

    ASSERT_SIZE(4, BTrieCountAvailable(trie));

    BTrieRelease(trie, 1);
    BTrieRelease(trie, 2);

    ASSERT_SIZE(6, BTrieCountAvailable(trie));

    BTrieDestroy(trie);
}
