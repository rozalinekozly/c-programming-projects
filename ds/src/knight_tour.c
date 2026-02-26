#include <assert.h>		/*assert()*/
#include <stdlib.h> 	/*qsort()*/
#include "knight_tour.h"
#include "bit_array.h"		/**/
/*-------------------------magic numbers---------------------------------------*/
enum
{
	DIRS = 8
};
/*----------------------------------------------------------------------------*/
typedef enum 
{
	FALSE = 0,
	TRUE = 1
}bool_ty;
/*----------------------------------------------------------------------------*/
typedef struct 
{
    point_ty point;
    size_t degree;
}neighbours_ty;
/*----------------------------------------------------------------------------*/
typedef struct offset_pair
{
	int d_row;
	int d_col;
}offset_pair_ty;
/*--------------------------forward declarations-------------------------------*/
static status_ty CanVisitAllIMP(point_ty point_, bit_array_ty board_, point_ty* path);
static point_ty GetNextPointIMP(point_ty p_, size_t dir_);
static bool_ty IsVisitedIMP(point_ty p_, bit_array_ty board_);
static bit_array_ty SetVisitedIMP(point_ty p_, bit_array_ty board_);
static size_t PointToIndexIMP(point_ty p_);
static bool_ty IsValidPointIMP(point_ty p_);
static bool_ty IsValidCordinate(int cord_);
static bool_ty IsAllBoardVisitedIMP(bit_array_ty board_);
/*phase 3*/
static size_t FillNeighboursArray(point_ty point_, neighbours_ty* arr_,
                                  bit_array_ty board_);
static int CountValidMovesIMP(point_ty p_, bit_array_ty board_);
static void SortNeighboursArray(neighbours_ty* arr_, size_t size_);
static int CompareDegree(const void* a_, const void* b_);
/*----------------------------------------------------------------------------*/
status_ty IsKnightTour(int row_, int col_, point_ty* path_)
{
	/*create a point_ty instance set fields to row_ and col_*/
	point_ty start_point;
	/* create empty bit board for tracking visited by defining a bit_array instance*/
	bit_array_ty board = 0;
	
	start_point.row = row_;
	start_point.col = col_;

	/* assert row_ and col_ are within the board's range*/
	assert(IsValidCordinate(row_) && IsValidCordinate(col_));

	/* return recursive function:
	   CanVisitAllIMP(start_point_, board, path) */
	return CanVisitAllIMP(start_point, board, path_);
}
/*----------------------------------------------------------------------------*/
static status_ty CanVisitAllIMP(point_ty point_,
                                bit_array_ty board_,
                                point_ty* path)
{
    /* declare loop variable */
    size_t i = 0;

    /* declare neighbours array (candidates to check will sort later) */
    neighbours_ty neighbours[DIRS];

    /* declare neighbours count */
    size_t neighbours_count = 0;

    /* if point_ is out of range */
    /* return FAIL */
    if (!IsValidPointIMP(point_))
    {
        return FAIL;
    }

    /* if position already visited */
    /* return FAIL */
    if (IsVisitedIMP(point_, board_))
    {
        return FAIL;
    }

    /* mark position as visited */
    board_ = SetVisitedIMP(point_, board_);

    /* add point to path */
    *path = point_;

    /* if all board visited */
    /* return SUCCESS */
    if (IsAllBoardVisitedIMP(board_))
    {
        return SUCCESS;
    }

    /* FillNeighboursArray(point_, neighbours, board_) */
    neighbours_count = FillNeighboursArray(point_,
                                           neighbours,
                                           board_);

    /* SortNeighboursArray(neighbours, neighbours_count) */
    SortNeighboursArray(neighbours,
                        neighbours_count);

    /* for each neighbour in sorted order */
    for (i = 0; i < neighbours_count; ++i)
    {
        /* if recursive call on neighbour succeeds */
        if (CanVisitAllIMP(neighbours[i].point,
                           board_,
                           path + 1) == SUCCESS)
        {
            /* return SUCCESS */
            return SUCCESS;
        }
    }

    /* return FAIL */
    return FAIL;
}
/*----------------------------------------------------------------------------*/
static point_ty GetNextPointIMP(point_ty p_, size_t dir_)
{
	point_ty ret = {0, 0};
	static const offset_pair_ty knight_moves[8] =
    {
        {-2, -1},
        {-2,  1},
        {-1,  2}, 
        { 1,  2},
        { 2,  1}, 
        { 2, -1},
        { 1, -2}, 
        {-1, -2}
    };

	/*assert dir is valid < BOARD_SIZE*/
	assert(dir_ < DIRS);
	/*assert point is valid*/
	assert(IsValidPointIMP(p_));

	/*add offset from knight_moves[dir]*/
	ret.row = p_.row + knight_moves[dir_].d_row;
    ret.col = p_.col + knight_moves[dir_].d_col;
    return ret;
}
/*----------------------------------------------------------------------------*/
static bool_ty IsValidPointIMP(point_ty p_)
{
	return (IsValidCordinate(p_.row) && IsValidCordinate(p_.col));
}
/*----------------------------------------------------------------------------*/
static bool_ty IsValidCordinate(int cord_)
{
	return (cord_ >= 0 && cord_ < (int)BOARD_SIZE);
}
/*----------------------------------------------------------------------------*/
static bool_ty IsVisitedIMP(point_ty p_, bit_array_ty board_)
{
	size_t index = 0;
	/* assert*/
	assert(IsValidPointIMP(p_));
	/*index = PointToIndex(p_) to get mapped number*/
	index = PointToIndexIMP(p_);
	/* return BitArrayGetBitVal(mapped_num) */
	return (BitArrayGetBitVal(board_, index));
}
/*----------------------------------------------------------------------------*/
static size_t PointToIndexIMP(point_ty p_)
{
	/*assert*/
	assert(IsValidPointIMP(p_));
	/* return (BOARD_SIZE* row + col) */
	return (BOARD_SIZE * p_.row + p_.col);
}
/*----------------------------------------------------------------------------*/
static bit_array_ty SetVisitedIMP(point_ty p_, bit_array_ty board_)
{
	size_t index = 0;
	/* assert*/
	assert(IsValidPointIMP(p_));
	/*index = PointToIndex(p_)*/
	index = PointToIndexIMP(p_);
	/*return BitArraySetOn(board_, index_)*/
	return (BitArraySetOn(board_, index));
}
/*----------------------------------------------------------------------------*/
static bool_ty IsAllBoardVisitedIMP(bit_array_ty board_) 
{
	return (BitArrayCountOn(board_) == BOARD_SIZE * BOARD_SIZE);
}
/*----------------------------------------------------------------------------*/
static size_t FillNeighboursArray(point_ty point_, neighbours_ty* arr_,
                                  bit_array_ty board_)
{
    /* declare count and initialize to 0 */
    size_t count = 0;

    /* for each direction i from 0 to 7 */
    size_t i = 0;
    point_ty next = {0, 0};

    for (i = 0; i < DIRS; ++i)
    {
        /* compute next point using GetNextPointIMP(point_, i) */
        next = GetNextPointIMP(point_, i);

        /* if next point is valid AND not visited */
        if (IsValidPointIMP(next) && !IsVisitedIMP(next, board_))
        {
            /* store next point in arr_[count].point */
            arr_[count].point = next;

            /* compute degree using CountValidMovesIMP(next, board_) */
            arr_[count].degree = CountValidMovesIMP(next, board_);

            /* increment count */
            ++count;
        }
    }

    /* return count */
    return count;
}
/*----------------------------------------------------------------------------*/
static int CountValidMovesIMP(point_ty p_, bit_array_ty board_)
{
    /* declare count and initialize to 0 */
    int count = 0;

    /* declare loop variable i */
    size_t i = 0;

    /* declare next point holder */
    point_ty next = {0, 0};

    /* for each direction from 0 to 7 */
    for (i = 0; i < DIRS; ++i)
    {
        /* compute next possible move from current point */
        next = GetNextPointIMP(p_, i);

        /* if next move is inside board AND not visited */
        if (IsValidPointIMP(next) && !IsVisitedIMP(next, board_))
        {
            /* increment count of valid onward moves */
            ++count;
        }
    }

    /* return total number of valid onward moves */
    return count;
}
/*----------------------------------------------------------------------------*/
static void SortNeighboursArray(neighbours_ty* arr_, size_t size_)
{
    /* call qsort on arr_ */
    /* number of elements is size_ */
    /* size of each element is sizeof(neighbours_ty) */
    /* comparison function compares degree fields */
    qsort(arr_, size_, sizeof(neighbours_ty), CompareDegree);
}
/*----------------------------------------------------------------------------*/
static int CompareDegree(const void* a_, const void* b_)
{
    /* cast a_ and b_ to neighbours_ty pointers */
    const neighbours_ty* first = (const neighbours_ty*)a_;
    const neighbours_ty* second = (const neighbours_ty*)b_;

    /* if first degree < second degree */
    if (first->degree < second->degree)
    {
        /* return negative value */
        return -1;
    }

    /* if first degree > second degree */
    if (first->degree > second->degree)
    {
        /* return positive value */
        return 1;
    }

    /* otherwise */
    /* return 0 */
    return 0;
}
