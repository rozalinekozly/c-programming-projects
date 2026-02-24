#include <stdio.h>   /* printf */
#include <string.h>  /* strcmp */
#include <math.h>    /* fabs */

#include "test_utils.h"

/*---------------------------------------------------------------------------*/
static int g_total  = 0;
static int g_passed = 0;
static int g_failed = 0;
static int g_color  = 1;
/*---------------------------------------------------------------------------*/
#define MINT    "\033[38;5;115m"
#define RED     "\033[38;5;160m"
#define WHITE   "\033[97m"
#define RESET   "\033[0m"
#define BOLD    "\033[1m"

#define LINE "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
/*---------------------------------------------------------------------------*/
static void PrintPass(void)
{
    if (g_color) printf(MINT "  ✓ " RESET);
    else         printf("  + ");
}

static void PrintFail(const char* msg)
{
    if (g_color) printf(RED "  ✗ " RESET "%s\n", msg);
    else         printf("  x %s\n", msg);
}
/*---------------------------------------------------------------------------*/
void TestSuiteBegin(const char* suite_name)
{
    g_total = g_passed = g_failed = 0;
    if (g_color)
        printf(WHITE "\n" LINE "\n  %s\n" LINE "\n" RESET, suite_name);
    else
        printf("\n%s\n%s\n%s\n", LINE, suite_name, LINE);
}

int TestSuiteEnd(void)
{
    if (g_color)
        printf(WHITE "\n" LINE "\n" RESET);
    else
        printf("\n%s\n", LINE);

    if (g_failed == 0)
    {
        if (g_color)
            printf(MINT BOLD "  %d/%d passed ✓ good job rozaline.\n" RESET, g_passed, g_total);
        else
            printf("  %d/%d passed - good job rozaline.\n", g_passed, g_total);
    }
    else
    {
        if (g_color)
            printf(RED BOLD "  %d/%d passed — %d failed. fix it rozaline.\n" RESET, g_passed, g_total, g_failed);
        else
            printf("  %d/%d passed - %d failed. fix it rozaline.\n", g_passed, g_total, g_failed);
    }

    if (g_color)
        printf(WHITE LINE "\n" RESET);
    else
        printf("%s\n", LINE);

    return g_failed == 0 ? 0 : 1;
}
/*---------------------------------------------------------------------------*/
void TestPrintSection(const char* section_name)
{
    if (g_color)
        printf(WHITE "\n" LINE "\n  %s\n" LINE "\n" RESET, section_name);
    else
        printf("\n%s\n  %s\n%s\n", LINE, section_name, LINE);
}

void TestPrintSubSection(const char* subsection_name)
{
    printf("  — %s\n", subsection_name);
}

void TestUtilsSetColorOutput(int enable)
{
    g_color = enable;
}
/*---------------------------------------------------------------------------*/
static void Record(int ok, const char* label, const char* msg)
{
    ++g_total;
    if (ok)
    {
        ++g_passed;
        PrintPass();
        printf("%s\n", label);
    }
    else
    {
        ++g_failed;
        PrintFail(msg);
    }
}
/*---------------------------------------------------------------------------*/
int AssertInt(int expected, int actual, const char* file, int line)
{
    char label[128];
    char msg[256];
    sprintf(label, "ASSERT_INT(%d, %d)", expected, actual);
    sprintf(msg, "ASSERT_INT — expected %d, got %d  (%s:%d)", expected, actual, file, line);
    Record(expected == actual, label, msg);
    return expected == actual;
}

int AssertDouble(double expected, double actual, const char* file, int line)
{
    char label[128];
    char msg[256];
    int ok = fabs(expected - actual) < 1e-9;
    sprintf(label, "ASSERT_DOUBLE(%.4f, %.4f)", expected, actual);
    sprintf(msg, "ASSERT_DOUBLE — expected %.4f, got %.4f  (%s:%d)", expected, actual, file, line);
    Record(ok, label, msg);
    return ok;
}

int AssertSize(size_t expected, size_t actual, const char* file, int line)
{
    char label[128];
    char msg[256];
    sprintf(label, "ASSERT_SIZE(%lu, %lu)", (unsigned long)expected, (unsigned long)actual);
    sprintf(msg, "ASSERT_SIZE — expected %lu, got %lu  (%s:%d)", (unsigned long)expected, (unsigned long)actual, file, line);
    Record(expected == actual, label, msg);
    return expected == actual;
}

int AssertPtr(const void* expected, const void* actual, const char* file, int line)
{
    char label[128];
    char msg[256];
    sprintf(label, "ASSERT_PTR(%p, %p)", expected, actual);
    sprintf(msg, "ASSERT_PTR — expected %p, got %p  (%s:%d)", expected, actual, file, line);
    Record(expected == actual, label, msg);
    return expected == actual;
}

int AssertTrue(int condition, const char* condition_str, const char* file, int line)
{
    char label[256];
    char msg[256];
    sprintf(label, "ASSERT_TRUE(%s)", condition_str);
    sprintf(msg, "ASSERT_TRUE — got false: %s  (%s:%d)", condition_str, file, line);
    Record(condition != 0, label, msg);
    return condition != 0;
}

int AssertFalse(int condition, const char* condition_str, const char* file, int line)
{
    char label[256];
    char msg[256];
    sprintf(label, "ASSERT_FALSE(%s)", condition_str);
    sprintf(msg, "ASSERT_FALSE — got true: %s  (%s:%d)", condition_str, file, line);
    Record(condition == 0, label, msg);
    return condition == 0;
}

int AssertSuccess(int condition, const char* condition_str, const char* file, int line)
{
    char label[256];
    char msg[256];
    sprintf(label, "ASSERT_SUCCESS(%s)", condition_str);
    sprintf(msg, "ASSERT_SUCCESS — expected 0, got %d: %s  (%s:%d)", condition, condition_str, file, line);
    Record(condition == 0, label, msg);
    return condition == 0;
}

int AssertFail(int condition, const char* condition_str, const char* file, int line)
{
    char label[256];
    char msg[256];
    sprintf(label, "ASSERT_FAIL(%s)", condition_str);
    sprintf(msg, "ASSERT_FAIL — expected non-zero, got 0: %s  (%s:%d)", condition_str, file, line);
    Record(condition != 0, label, msg);
    return condition != 0;
}

int AssertNotNull(const void* ptr, const char* ptr_str, const char* file, int line)
{
    char label[256];
    char msg[256];
    sprintf(label, "ASSERT_NOT_NULL(%s)", ptr_str);
    sprintf(msg, "ASSERT_NOT_NULL — got NULL: %s  (%s:%d)", ptr_str, file, line);
    Record(ptr != NULL, label, msg);
    return ptr != NULL;
}

int AssertNull(const void* ptr, const char* ptr_str, const char* file, int line)
{
    char label[256];
    char msg[256];
    sprintf(label, "ASSERT_NULL(%s)", ptr_str);
    sprintf(msg, "ASSERT_NULL — expected NULL, got non-NULL: %s  (%s:%d)", ptr_str, file, line);
    Record(ptr == NULL, label, msg);
    return ptr == NULL;
}

int AssertStrEqual(const char* expected, const char* actual, const char* file, int line)
{
    char label[256];
    char msg[256];
    int ok = (expected && actual && 0 == strcmp(expected, actual));
    sprintf(label, "ASSERT_STR_EQUAL(\"%s\", \"%s\")",
            expected ? expected : "(null)",
            actual   ? actual   : "(null)");
    sprintf(msg, "ASSERT_STR_EQUAL — expected \"%s\", got \"%s\"  (%s:%d)",
            expected ? expected : "(null)",
            actual   ? actual   : "(null)",
            file, line);
    Record(ok, label, msg);
    return ok;
}

int AssertIntArray(const int* expected, const int* actual, size_t length,
                   const char* file, int line)
{
    size_t i = 0;
    int ok = 1;
    char label[64];
    char msg[256];
    sprintf(label, "ASSERT_INT_ARRAY(len=%lu)", (unsigned long)length);
    for (i = 0; i < length; ++i)
    {
        if (expected[i] != actual[i])
        {
            ok = 0;
            sprintf(msg, "ASSERT_INT_ARRAY — mismatch at [%lu]: expected %d, got %d  (%s:%d)",
                    (unsigned long)i, expected[i], actual[i], file, line);
            break;
        }
    }
    Record(ok, label, msg);
    return ok;
}
/*---------------------------------------------------------------------------*/
void TestPass(const char* test_name)
{
    ++g_total;
    ++g_passed;
    PrintPass();
    printf("%s\n", test_name);
}

void TestFail(const char* test_name, const char* message, const char* file, int line)
{
    char msg[256];
    ++g_total;
    ++g_failed;
    sprintf(msg, "%s — %s  (%s:%d)", test_name, message, file, line);
    PrintFail(msg);
}
