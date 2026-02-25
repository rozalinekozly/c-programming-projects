#include <assert.h>		/*assert()*/
/*----------------------------------------------------------------------------*/
#define BOARD_SIZE 8
#define TOTAL_SQUARES (BOARD_SIZE * BOARD_SIZE)
/*----------------------------------------------------------------------------*/
typedef struct point
{
	size_t row;
	size_t col;
} point_ty;
/*--------------------------forward declarations-------------------------------*/
static int CanVisitAllIMP(point_ty point_, bit_array_ty board_);

static point_ty GetNextpointIMP(point_ty p_, size_t dir_);
static int IsVisitedIMP(point_ty p_, bit_array_ty board_);
static bit_array_ty SetVisitedIMP(point_ty p_, bit_array_ty board_);
static size_t PointToIndexIMP(point_ty p_);

static int IsValidPointIMP(point_ty p_);
static IsValidCordinate(int cord_);
/*---------------------------LUT of valid moves--------------------------------*/
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
/*----------------------------------------------------------------------------*/
int IsKnightTour(size_t row_, size_t col_)
{
	/* assert row_ and col_ are within the board's range'*/
	
	/*create a point_ty instance set fields to row_ and col_*/
	
	/* create empty bit board using BitArrayResetAll(0) for tracking visited*/

	/* call recursive function:
	   CanVisitAllIMP(start_point_, board) */

	/* return result of recursive call */
}
/*----------------------------------------------------------------------------*/
static int CanVisitAllIMP(point_ty point_, bit_array_ty board_)
{
	/* if all board visited:
	   if (IsAllBoardVisitedIMP(board_)) return TRUE */
	   
	/* if point_ is out of range:
	(!IsValidPosIMP(point_)) return FALSE */

	/* if position already visited:
	   if (IsVisitedIMP(point_, board_)) return FALSE */

	/* mark position as visited:
	   board_ = SetVisitedIMP(p_, board_) */


	/* for each direction i from 0 to 7 (valid direction from point_)*/
	{
		/* compute next position:
		   next = GetNextpointIMP(p_, i) */

		/* recursively call:
		   if (CanVisitAllIMP(next, board_) == TRUE)
		       return TRUE */
	}

	/* if none succeeded:
	   return FALSE */
}

static point_ty GetNextpointIMP(point_ty p_, size_t dir_)
{
	/*assert*/
	/*cast to int before adding offsets, then check range before casting back*/
	
}
static IsValidCordinate(int cord_)
{
	/*if cord_ < 0 OR cord_ > 8*/
		/*return FALSE*/
	/*return TRUE*/
}
static int IsValidPointIMP(point_ty p_)
{
	/* return TRUE if row and col are between 0 and 7 */
}

static int IsVisitedIMP(point_ty p_, bit_array_ty board_)
{
	/* return value of bit at index mapped from point */
}

static size_t PointToIndexIMP(point_ty p_)
{
	/* map (row, col) to single index: 8 * row + col */
}

static bit_array_ty SetVisitedIMP(point_ty p_, bit_array_ty board_)
{
	/* turn ON the bit corresponding to the point */
}

