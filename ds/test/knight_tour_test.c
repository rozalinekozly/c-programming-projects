#include <stdio.h>
#include <assert.h>

#include "knight_tour.h"   /* where IsKnightTour is declared */

static void TestValidStarts(void);
static void TestInvalidStarts(void);

int main(void)
{
    TestValidStarts();
    TestInvalidStarts();

    printf("All tests passed successfully.\n");
    return 0;
}

/* ----------------------------------------------------------- */

static void TestValidStarts(void)
{
    size_t row = 0;
    size_t col = 0;
    int failures = 0;

    for (row = 0; row < 5; ++row)
    {
        for (col = 0; col < 5; ++col)
        {
            printf("Testing start (%lu, %lu)... ", row, col);

            if (IsKnightTour(row, col) == SUCCESS)
            {
                printf("PASS\n");
            }
            else
            {
                printf("FAIL\n");
                ++failures;
            }
        }
    }

    if (failures == 0)
    {
        printf("\nAll tests passed successfully.\n");
    }
    else
    {
        printf("\n%d tests failed.\n", failures);
    }
}

/* ----------------------------------------------------------- */

static void TestInvalidStarts(void)
{
    /* Negative values (if function accepts int) */
    assert(IsKnightTour(-1, 0) == FAIL);
    assert(IsKnightTour(0, -1) == FAIL);

    /* Out of board */
    assert(IsKnightTour(5, 0) == FAIL);
    assert(IsKnightTour(0, 5) == FAIL);
}
