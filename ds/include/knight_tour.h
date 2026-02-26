#ifndef __ILRD_KNIGHT_TOUR_H__
#define __ILRD_KNIGHT_TOUR_H__

enum
{
	BOARD_SIZE = 8,
	PATH_LEN = BOARD_SIZE * BOARD_SIZE
};
typedef enum
{
	FAIL = 0,
	SUCCESS = 1
}status_ty;

typedef struct point
{
	int row;
	int col;
} point_ty;

status_ty IsKnightTour(int row_, int col_, point_ty* path);

#endif
