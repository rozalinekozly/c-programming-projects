/*
submitter: rozaline kozly
reviewer: Tomer
------------------------------------------------------------------------------*/
#ifndef RECURSION_H
#define RECURSION_H

#include <stddef.h>
#include "stack.h"

typedef struct node node_ty;

struct node
{
    void* data;
    node_ty* next;
};
/*
	purpose: calculates Fibonacci element placed at index X
*/
int Fibonacci(int x);
/*-----------------------------------------------------------------------------*/
/*
	purpose: flips a ssl
*/
node_ty* FlipList(node_ty* node);
/*-----------------------------------------------------------------------------*/
/*
	purpose: sorts a stack recursivly
*/
void SortStack(stack_ty* s);
/*-----------------------------------------------------------------------------*/
/*
	putpose: calcultes a string length
*/
size_t Strlen(const char* str);
/*-----------------------------------------------------------------------------*/
/*
	purpose: compares between two strings
*/
int Strcmp(const char* str1, const char* str2);
/*-----------------------------------------------------------------------------*/
/*
	purpose: copies src string to dest string
*/
char* Strcpy(char* dest, const char* src);
/*-----------------------------------------------------------------------------*/
/*
	purpose: concatenate dest and src
*/
char* Strcat(char* cat_to, const char* cat_frm);
/*-----------------------------------------------------------------------------*/
/*
	purpose: returns a poiner to first apperance of sub_str substring 
	in search_Str
*/
char* Strstr(char* search_str, const char* sub_str);
/*-----------------------------------------------------------------------------*/
#endif
