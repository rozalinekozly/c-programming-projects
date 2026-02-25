#include <assert.h>		/*assert()*/

#include "bit_array.h"		/**/
/*----------------------------------------------------------------------------*/
typedef enum 
{
	FALSE = 0,
	TRUE = 1
}bool_ty;
	
typedef enum
{
	FAIL = 0,
	SUCCESS = 1
}status_ty;
/*----------------------------------------------------------------------------*/
typedef struct point
{
	int row;
	int col;
} point_ty;
/*----------------------------------------------------------------------------*/
typedef struct offset_pair
{
	int d_row;
	int d_col;
}offset_pair_ty;
/*--------------------------forward declarations-------------------------------*/
static int CanVisitAllIMP(point_ty point_, bit_array_ty board_);

static point_ty GetNextPointIMP(point_ty p_, size_t dir_);
static int IsVisitedIMP(point_ty p_, bit_array_ty board_);
static bit_array_ty SetVisitedIMP(point_ty p_, bit_array_ty board_);
static size_t PointToIndexIMP(point_ty p_);

static int IsValidPointIMP(point_ty p_);
static IsValidCordinate(int cord_);

int IsAllBoardVisitedIMP(bit_array_ty board_);
/*----------------------------------------------------------------------------*/
int IsKnightTour(int row_, int col_)
{
	/* assert row_ and col_ are within the board's range*/
	assert()
	/*create a point_ty instance set fields to row_ and col_*/
	
	/* create empty bit board for tracking visited by defining a bit_array instance*/

	/* call recursive function:
	   CanVisitAllIMP(start_point_, board) */

	/* return result of recursive call */
}
/*----------------------------------------------------------------------------*/
static int CanVisitAllIMP(point_ty point_, bit_array_ty board_)
{
	/* if point_ is out of range:
		(!IsValidPointIMP(point_)) return FALSE */
	
	/* if position already visited:
	   if (IsVisitedIMP(point_, board_)) return FALSE */
	   	
	/* if all board visited:
	   if (IsAllBoardVisitedIMP(board_)) return TRUE */
	   
	/* mark position as visited:
	   board_ = SetVisitedIMP(p_, board_) */

	/* for each direction i from 0 to 7 (valid direction from point_)*/
	
		/* compute next position:
		   next = GetNextpointIMP(p_, i) */

		   /*if (CanVisitAllIMP(next, board_) == TRUE)*/
		      /* return TRUE */
	

	/* return FALSE */
}
/*----------------------------------------------------------------------------*/
static point_ty GetNextPointIMP(point_ty p_, size_t dir_)
{
	/*assert dir is valid < 8*/
	/*assert point is valid*/
	/*const offset_pair_ty knight_moves[8] =
	{
		{-2, -1},
		{-2,  1},
		{-1,  2},
		{ 1,  2},
		{ 2,  1},
		{ 2, -1},
		{ 1, -2},
		{-1, -2}
	};*/
	/*cast to int */
	/*add offset from knight_moves[dir]*/
	/*check range */
	/*cast back and set return point*/
}
/*----------------------------------------------------------------------------*/
static int IsValidPointIMP(point_ty p_)
{
	/* return TRUE if row and col are between 0 and 7 */
}
/*----------------------------------------------------------------------------*/
static IsValidCordinate(int cord_)
{
	return (cord_ > 0 && cord_ < 8);
}
/*----------------------------------------------------------------------------*/
static int IsVisitedIMP(point_ty p_, bit_array_ty board_)
{
	/* assert*/
	/*mapped_num = PointToIndex(p_) to get mapped number*/
	/* ret =  BitArrayGetBitVal(mapped_num) */
	/*return ret */
}
/*----------------------------------------------------------------------------*/
static size_t PointToIndexIMP(point_ty p_)
{
	/*assert*/
	/* return (8 * row + col) */
}
/*----------------------------------------------------------------------------*/
static bit_array_ty SetVisitedIMP(point_ty p_, bit_array_ty board_)
{
	/* assert*/
	/*index = PointToIndex(p_)*/
	/*BitArraySetOn(board_, index_)*/
}
/*----------------------------------------------------------------------------*/
int IsAllBoardVisitedIMP(bit_array_ty board_) 
{
	/*return (0 == board_)*/
}

