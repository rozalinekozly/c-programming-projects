/*
submitter: rozaline kozly
reviewer: Tomer
-------------------------------------------------------------------------------*/
#include <string.h>		/*strncmp() in Strstr*/
#include <assert.h>		/*assert()*/

#include "recursion.h"		/*API*/

/*-----------------------aux functions-----------------------------------------*/
static void InsertSorted(stack_ty* s, int x);
static void StrcpyWrapped(char* dest, const char* src);
static void StrcatWrapped(char* cat_to, const char* cat_frm);
/*-----------------------------------------------------------------------------*/
int Fibonacci(int x)
{
    if(0 > x)
    {
        return (-1);
    }
    if(1 == x || 0 == x)
    {
        return x;
    }
    
    return (Fibonacci(x-1) + Fibonacci(x-2));
}
/*-----------------------------------------------------------------------------*/
node_ty* FlipList(node_ty* node)
{
    node_ty* new_head = NULL;
    
    if(NULL == node || NULL == node->next)
    {
        return (node);
    }
    new_head = FlipList(node->next);
    node->next->next = node;
    node->next = NULL;
    
    return (new_head);
}
/*-----------------------------------------------------------------------------*/
void SortStack(stack_ty *s)
{
    int x = 0;
    
    if(StackIsEmpty(s))
    {
		return;
    }
    x = *(int*)StackPeek(s);
    StackPop(s);
    SortStack(s);
    InsertSorted(s,x);
}
/*-----------------------------------------------------------------------------*/
static void InsertSorted(stack_ty* s, int x)
{
    int tmp = 0;
    
    if (StackIsEmpty(s) || *(int*)StackPeek(s) <= x)
    {
        StackPush(s, &x);
        return;
    }

    tmp = *(int*)StackPeek(s);
    StackPop(s);
    InsertSorted(s, x);
    StackPush(s, &tmp);
}
/*-----------------------------------------------------------------------------*/
size_t Strlen(const char* str)
{
    if(NULL == str || '\0'== *str)
    {
        return (0);
    }
    return (1 + Strlen(++str)); 
}
/*-----------------------------------------------------------------------------*/
int Strcmp(const char* str1, const char* str2)
{
    assert(NULL != str1);
    assert(NULL != str2);

    if ('\0' == *str1 || *str1 != *str2)
    {
        return (unsigned char)*str1 - (unsigned char)*str2;
    }

    return Strcmp(str1 + 1, str2 + 1);
}
/*-----------------------------------------------------------------------------*/
char* Strcpy(char* dest, const char* src)
{
    char* dest_iter = dest;
    
    assert(NULL != dest);
    assert(NULL != src);
    
    StrcpyWrapped(dest_iter, src);
    
    return dest;
}
/*-----------------------------------------------------------------------------*/
static void StrcpyWrapped(char* dest, const char* src)
{
    if('\0' == *src)
    {
        *dest = '\0';
        return;
    }
    *dest = *src;
    ++dest;
    ++src;
    StrcpyWrapped(dest, src);
}
/*-----------------------------------------------------------------------------*/
char* Strcat(char* cat_to, const char* cat_frm)
{
	char* cat_to_iter = cat_to;
	
	assert(cat_to != NULL);
	assert(cat_frm != NULL);
	
	StrcatWrapped(cat_to_iter, cat_frm);
	
	return cat_to;
}
/*-----------------------------------------------------------------------------*/
static void StrcatWrapped(char* cat_to, const char* cat_frm)
{
    if ('\0' != *cat_to)
    {
        StrcatWrapped(cat_to + 1, cat_frm);
        return;
    }
    if ('\0' == *cat_frm)
    {
        *cat_to = '\0';  
        return;
    }
    *cat_to = *cat_frm;
    StrcatWrapped(cat_to + 1, cat_frm + 1);
}
/*-----------------------------------------------------------------------------*/
char* Strstr(char* search_str, const char* sub_str)
{
    assert(search_str != NULL);
    assert(sub_str != NULL);
    
    if ('\0' == *sub_str)  
    {
        return (search_str);
    }
    
    if ('\0' == *search_str)  
    {
        return (NULL);
    }
    
    if (strncmp(search_str, sub_str, Strlen(sub_str)) == 0)  
    {
        return (search_str);
    }
    
    return Strstr(search_str + 1, sub_str);  
}
