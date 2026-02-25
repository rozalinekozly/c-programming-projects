#include <assert.h>		/*assert()*/

#include "bit_array.h"		/**/
/*----------------------------------------------------------------------------*/
typedef enum
{
	BOARD_SIZE = 5;
}BOARD_SIZE;

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
static status_ty CanVisitAllIMP(point_ty point_, bit_array_ty board_);

static point_ty GetNextPointIMP(point_ty p_, size_t dir_);
static status_ty IsVisitedIMP(point_ty p_, bit_array_ty board_);
static bit_array_ty SetVisitedIMP(point_ty p_, bit_array_ty board_);
static size_t PointToIndexIMP(point_ty p_);

static status_ty IsValidPointIMP(point_ty p_);
static status_ty IsValidCordinate(int cord_);

status_ty IsAllBoardVisitedIMP(bit_array_ty board_);
/*----------------------------------------------------------------------------*/
status_ty IsKnightTour(int row_, int col_)
{
	/* assert row_ and col_ are within the board's range*/
	/*create a point_ty instance set fields to row_ and col_*/
	/* create empty bit board for tracking visited by defining a bit_array instance*/
	/* return recursive function:
	   CanVisitAllIMP(start_point_, board) *//
}
/*----------------------------------------------------------------------------*/
static status_ty CanVisitAllIMP(point_ty point_, bit_array_ty board_)
{
	/* if point_ is out of range:
		(!IsValidPointIMP(point_)) return FAIL */
	 if(!IsValidPointIMP(point_))
	 {
	 		return FAIL;
	 }
	/* if all board visited:
	   if (IsAllBoardVisitedIMP(board_)) return SUCCESS */
	  if(IsAllBoardVisitedIMP(board_))
	  {
	  	return SUCCESS;
	  }
	/* if position already visited:
	   if (IsVisitedIMP(point_, board_)) return FAIL */
		if(IsVisitedIMP(point_, board))
		{
			return FAIL;
		}
	/* mark position as visited:
	   board_ = SetVisitedIMP(p_, board_) */

	/* for each direction i from 0 to 7 (valid direction from point_)*/
	
		/* compute next position:
		   next = GetNextpointIMP(p_, i) */

		   /*if (CanVisitAllIMP(next, board_) == TRUE)*/
		      /* return SUCCESS */
	

	/* return FAIL */
}
/*----------------------------------------------------------------------------*/
static point_ty GetNextPointIMP(point_ty p_, size_t dir_)
{
	point_ty ret = {0, 0};
	static const offset_ty knight_moves[8] =
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
	assert(dir_ < BOARD_SIZE);
	/*assert point is valid*/
	assert(IsValidPointIMP(p_));

	/*add offset from knight_moves[dir]*/
	ret = {p_.row + knight_moves[dir_].d_row,
           p_.col + knight_moves[dir_].d_col};
    return next;
	/*check range */
	/*cast back and set return point*/
}
/*----------------------------------------------------------------------------*/
static status_ty IsValidPointIMP(point_ty p_)
{
	return (IsValidCordinate(p_->row) && IsValidCordinate(P_->col));
}
/*----------------------------------------------------------------------------*/
static IsValidCordinate(int cord_)
{
	return (cord_ > 0 && cord_ < 8);
}
/*----------------------------------------------------------------------------*/
static status_ty IsVisitedIMP(point_ty p_, bit_array_ty board_)
{
	size_t index = 0;
	/* assert*/
	assert(IsValidPointIMP(p_));
	/*index = PointToIndex(p_) to get mapped number*/
	index = PointToIndex(p_);
	/* return BitArrayGetBitVal(mapped_num) */
	return (BitArrayGetBitVal(index));
}
/*----------------------------------------------------------------------------*/
static size_t PointToIndexIMP(point_ty p_)
{
	/*assert*/
	assert(IsValidPointIMP(p_));
	/* return (8 * row + col) */
	return (BOARD_SIZE * p_->row + p_->col);
}
/*----------------------------------------------------------------------------*/
static bit_array_ty SetVisitedIMP(point_ty p_, bit_array_ty board_)
{
	size_t index = 0;
	/* assert*/
	assert(IsValidPointIMP(p_));
	/*index = PointToIndex(p_)*/
	index = PointToIndex(p_);
	/*return BitArraySetOn(board_, index_)*/
	return (BitArraySetOn(board_, index));
}
/*----------------------------------------------------------------------------*/
status_ty IsAllBoardVisitedIMP(bit_array_ty board_) 
{
	return (0 == board_);
}

