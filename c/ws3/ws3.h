#ifndef __WS3_H__
#define __WS3_H__

#include <stddef.h>
#define COLS 3


/*
Description: Calculates the sum of all elements in a 2D integer array.
Returns: The total sum of all elements.
Undefined: Passing NULL or using a column size that does not match COLS.
*/
int Sum2D(int arr[][COLS], size_t rows);

/*
Description: Solves the Josephus problem for a group of size n.
Returns: The index of the last surviving soldier.
Undefined: memory allocation failure.
*/
int JosephusCircularArray(int n);

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


int Sum2D(int arr[][COLS], size_t rows);
void PrintEnvVarInLowerCase(char *envp[]);
size_t GetEnvSize(char *envp[]);
char **AllocateEnvCopy(size_t size);
char *ToLowerString(const char *src);
char **CloneEnvToLower(char *envp[]);
void PrintEnv(char *envp[]);
void FreeEnv(char *envp[]);
#endif /* __WS3_H__ */

