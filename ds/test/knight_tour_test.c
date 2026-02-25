#include <stdio.h>
#include "knight_tour.h"

#define BOARD_SIZE 5
#define PATH_LEN (BOARD_SIZE * BOARD_SIZE)

/* ------------------------------------------------------------ */
static void PrintPath(point_ty* path);
static void PrintBoard(point_ty* path);
static void RunAllTests(void);
/* ------------------------------------------------------------ */

int main(void)
{
    RunAllTests();
    return 0;
}

/* ------------------------------------------------------------ */

static void RunAllTests(void)
{
    size_t row = 0;
    size_t col = 0;
    int failures = 0;
    point_ty path[PATH_LEN];

    for (row = 0; row < BOARD_SIZE; ++row)
    {
        for (col = 0; col < BOARD_SIZE; ++col)
        {
            printf("Testing start (%lu, %lu)... ", row, col);

            if (IsKnightTour(row, col, path) == SUCCESS)
            {
                printf("PASS\n");

                printf("\nPath:\n");
                PrintPath(path);

                printf("\nBoard:\n");
                PrintBoard(path);

                printf("\n--------------------------------------\n\n");
            }
            else
            {
                printf("FAIL\n");
                ++failures;
            }
        }
    }

    printf("\n======================================\n");

    if (failures == 0)
    {
        printf("All tests passed.\n");
    }
    else
    {
        printf("%d tests failed.\n", failures);
    }
}

/* ------------------------------------------------------------ */

static void PrintPath(point_ty* path)
{
    size_t i = 0;

    for (i = 0; i < PATH_LEN; ++i)
    {
        printf("%2lu: (%d, %d)\n",
               i,
               path[i].row,
               path[i].col);
    }
}

/* ------------------------------------------------------------ */

static void PrintBoard(point_ty* path)
{
    int board[BOARD_SIZE][BOARD_SIZE] = {0};
    size_t i = 0;
    size_t r = 0;
    size_t c = 0;

    for (i = 0; i < PATH_LEN; ++i)
    {
        board[path[i].row][path[i].col] = i;
    }

    for (r = 0; r < BOARD_SIZE; ++r)
    {
        for (c = 0; c < BOARD_SIZE; ++c)
        {
            printf("%2d ", board[r][c]);
        }
        printf("\n");
    }
}
