#define BOARD_SIZE 8
#define TOTAL_SQUARES (BOARD_SIZE * BOARD_SIZE)

typedef struct point
{
	int row;
	int col;
} point_ty;

typedef struct board
{
	bit_array_ty visited;
} board_ty;

typedef struct offset
{
	int drow;
	int dcol;
} offset_ty;

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

int IsKnightTour(size_t row_, size_t col_)
{
	/* assert valid input using assert(row_ < 8 && col_ < 8) */
	/* create empty bit board using BitArrayResetAll(0) */

	/* create start point: 
	   point_ty start = {row_, col_} */

	/* call recursive function:
	   CanVisitAllIMP(start, board) */

	/* return result of recursive call */
}

static int CanVisitAllIMP(point_ty p_, bit_array_ty board_)
{
	/* if position is invalid:
	   if (!IsValidPosIMP(p_)) return FALSE */

	/* if position already visited:
	   if (IsVisitedIMP(p_, board_)) return FALSE */

	/* mark position as visited:
	   board_ = SetVisitedIMP(p_, board_) */

	/* if all board visited:
	   if (IsAllBoardVisitedIMP(board_)) return TRUE */

	/* for each direction i from 0 to 7 */
	{
		/* compute next position:
		   next = GetNextStepIMP(p_, i) */

		/* recursively call:
		   if (CanVisitAllIMP(next, board_) == TRUE)
		       return TRUE */
	}

	/* if none succeeded:
	   return FALSE */
}
static int IsValidPosIMP(point_ty p_)
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

