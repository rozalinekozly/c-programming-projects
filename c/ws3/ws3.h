#ifndef __WS3_H__
#define __WS3_H__
#include <stddef.h>
#define COLS 3


/*
Description: Calculates the sum of all elements in same row in a 2D integer array.
Undefined: Passing NULL or using a column size that does not match COLS.
*/
void RowSum2D(int arr[][COLS], size_t rows, int res[]);

/*
Description: Solves the Josephus problem for a group of size n.
Returns: The index of the last surviving soldier.
Undefined: memory allocation failure.
*/
size_t JosephusCircularArray(size_t n);

/*
Description: Prints the size (in bytes) of all built-in C data types.
Returns: Nothing.
Undefined: None.
*/
void PrintDataTypeSizes(void);

/*
Description: Prints all environment variables in lowercase.
Returns: Nothing.
Undefined: Passing NULL instead of a valid envp array.
*/
void PrintEnvVarInLowerCase(char *envp[]);



#endif /* __WS3_H__ */

