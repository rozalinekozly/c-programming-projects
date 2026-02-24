#include <stdio.h>   /* printf */
#include <string.h>  /* strcmp */
#include <math.h>    /* fabs */

#include "test_utils.h"

/*---------------------------------------------------------------------------*/
static int g_total = 0;
static int g_passed = 0;
static int g_failed = 0;
static int g_color  = 1;
/*---------------------------------------------------------------------------*/
#define GREEN  "\033[32m"
#define RED    "\033[31m"
#define YELLOW "\033[33m"
#define CYAN   "\033[36m"
#define RESET  "\033[0m"

static void PrintPass(void)
{
    if (g_color) printf(GREEN "[PASS]" RESET "\n");
    else         printf("[PASS]\n");
}

static void PrintFail(const char* msg, const char* file, int line)
{
    if (g_color)
        printf(RED "[FAIL]" RESET " %s (file: %s, line: %d)\n", msg, file, line);
    else
        printf("[FAIL] %s (file: %s, line: %d)\n", msg, file, line);
}
/*---------------------------------------------------------------------------*/
void TestSuiteBegin(const char* suite_name)
{
    g_total = g_passed = g_failed = 0;
    if (g_color)
        printf(CYAN "\n=== %s ===\n" RESET, suite_name);
    else
        printf("\n=== %s ===\n", suite_name);
}

int TestSuiteEnd(void)
{
    printf("\nResults: %d/%d passed", g_passed, g_total);
    if (g_failed == 0)
    {
        if (g_color) printf(GREEN " (all passed)\n" RESET);
        else         printf(" (all passed)\n");
        return 0;
    }
    if (g_color) printf(RED " (%d failed)\n" RESET, g_failed);
    else         printf(" (%d failed)\n", g_failed);
    return 1;
}
/*---------------------------------------------------------------------------*/
void TestPrintSection(const char* section_name)
{
    if (g_color)
        printf(YELLOW "\n--- %s ---\n" RESET, section_name);
    else
        printf("\n--- %s ---\n", section_name);
}

void TestPrintSubSection(const char* subsection_name)
{
    printf("  > %s\n", subsection_name);
}

void TestUtilsSetColorOutput(int enable)
{
    g_color = enable;
}
/*---------------------------------------------------------------------------*/
static void Record(int ok, const char* msg, const char* file, int line)
{
    ++g_total;
    if (ok) { ++g_passed; PrintPass(); }
    else    { ++g_failed; PrintFail(msg, file, line); }
}
/*---------------------------------------------------------------------------*/
int AssertInt(int expected, int actual, const char* file, int line)
{
    char msg[128];
    printf("  ASSERT_INT(%d, %d) ... ", expected, actual);
    sprintf(msg, "expected %d, got %d", expected, actual);
    Record(expected == actual, msg, file, line);
    return expected == actual;
}

int AssertDouble(double expected, double actual, const char* file, int line)
{
    char msg[128];
    int ok = fabs(expected - actual) < 1e-9;
    printf("  ASSERT_DOUBLE(%.6f, %.6f) ... ", expected, actual);
    sprintf(msg, "expected %.6f, got %.6f", expected, actual);
    Record(ok, msg, file, line);
    return ok;
}

int AssertSize(size_t expected, size_t actual, const char* file, int line)
{
    char msg[128];
   printf("  ASSERT_SIZE(%lu, %lu) ... ", (unsigned long)expected, (unsigned long)actual);
sprintf(msg, "expected %lu, got %lu", (unsigned long)expected, (unsigned long)actual);
    Record(expected == actual, msg, file, line);
    return expected == actual;
}

int AssertPtr(const void* expected, const void* actual, const char* file, int line)
{
    char msg[128];
    printf("  ASSERT_PTR(%p, %p) ... ", expected, actual);
    sprintf(msg, "expected %p, got %p", expected, actual);
    Record(expected == actual, msg, file, line);
    return expected == actual;
}

int AssertTrue(int condition, const char* condition_str, const char* file, int line)
{
    char msg[256];
    printf("  ASSERT_TRUE(%s) ... ", condition_str);
    sprintf(msg, "expected true, got false: %s", condition_str);
    Record(condition != 0, msg, file, line);
    return condition != 0;
}

int AssertFalse(int condition, const char* condition_str, const char* file, int line)
{
    char msg[256];
    printf("  ASSERT_FALSE(%s) ... ", condition_str);
    sprintf(msg, "expected false, got true: %s", condition_str);
    Record(condition == 0, msg, file, line);
    return condition == 0;
}

int AssertSuccess(int condition, const char* condition_str, const char* file, int line)
{
    char msg[256];
    printf("  ASSERT_SUCCESS(%s) ... ", condition_str);
    sprintf(msg, "expected SUCCESS(0), got %d: %s", condition, condition_str);
    Record(condition == 0, msg, file, line);
    return condition == 0;
}

int AssertFail(int condition, const char* condition_str, const char* file, int line)
{
    char msg[256];
    printf("  ASSERT_FAIL(%s) ... ", condition_str);
    sprintf(msg, "expected FAIL(non-zero), got 0: %s", condition_str);
    Record(condition != 0, msg, file, line);
    return condition != 0;
}

int AssertNotNull(const void* ptr, const char* ptr_str, const char* file, int line)
{
    char msg[256];
    printf("  ASSERT_NOT_NULL(%s) ... ", ptr_str);
    sprintf(msg, "expected non-NULL, got NULL: %s", ptr_str);
    Record(ptr != NULL, msg, file, line);
    return ptr != NULL;
}

int AssertNull(const void* ptr, const char* ptr_str, const char* file, int line)
{
    char msg[256];
    printf("  ASSERT_NULL(%s) ... ", ptr_str);
    sprintf(msg, "expected NULL, got non-NULL: %s", ptr_str);
    Record(ptr == NULL, msg, file, line);
    return ptr == NULL;
}

int AssertStrEqual(const char* expected, const char* actual, const char* file, int line)
{
    char msg[256];
    int ok = (expected && actual && 0 == strcmp(expected, actual));
    printf("  ASSERT_STR_EQUAL(\"%s\", \"%s\") ... ",
           expected ? expected : "(null)",
           actual   ? actual   : "(null)");
    sprintf(msg, "expected \"%s\", got \"%s\"",
            expected ? expected : "(null)",
            actual   ? actual   : "(null)");
    Record(ok, msg, file, line);
    return ok;
}

int AssertIntArray(const int* expected, const int* actual, size_t length,
                   const char* file, int line)
{
    size_t i = 0;
    int ok = 1;
    char msg[256];
    printf("  ASSERT_INT_ARRAY(len=%lu) ... ", (unsigned long)length);
    for (i = 0; i < length; ++i)
    {
        if (expected[i] != actual[i])
        {
            ok = 0;
            sprintf(msg, "mismatch at index %lu: expected %d, got %d", (unsigned long)i, expected[i], actual[i]);
            break;
        }
    }
    Record(ok, ok ? "" : msg, file, line);
    return ok;
}
/*---------------------------------------------------------------------------*/
void TestPass(const char* test_name)
{
    ++g_total;
    ++g_passed;
    printf("  %s ... ", test_name);
    PrintPass();
}

void TestFail(const char* test_name, const char* message, const char* file, int line)
{
    ++g_total;
    ++g_failed;
    printf("  %s ... ", test_name);
    PrintFail(message, file, line);
}
