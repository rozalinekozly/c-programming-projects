/*******************************************
* ROZALINE KOZLY
* REVIWER : GIL
* DATE 16-11-2025
********************************************/
#include <stddef.h> /* using size_t data type */
#include <stdlib.h> /* strdup uses malloc and free */
#include "String.h" /* my declarations*/
#include <assert.h> /* for asserts (debugging mode) */
#define SEVEN 7

size_t StrLen(const char* str)
{
  size_t len = 0;
  
  assert(NULL != str);
  
  while('\0' != *str)
  {
    ++len;
    ++str;
  }
  
  return len;
}


int StrCmp(const char *s1, const char *s2)
{
  while(*s1 != '\0' && *s2 != '\0')
  {	
	if(*s1 == *s2)
	{
		++s1;
		++s2;
			
	}
	else
	{
		break;
	}
  } 
	
  return ((unsigned char)(*s1) - (unsigned char)(*s2));
}

char* StrCpy(char* dst, const char* src)
{
   char* head = dst; /*placement to hold head of the string*/
   
   assert(NULL != dst);
   assert(NULL != src);
   while(*src != '\0')
   {
   	*dst = *src;
   	++src;
   	++dst;
   }
   
   *dst = '\0'; /* strcpy copies the \0 char too*/
   return head;

}


char* StrnCpy(char* dst, const char* src, size_t n)
{
    char* head = dst;
    
    assert(dst != NULL && src != NULL);

    while(n > 0 && *src != '\0')
    {
        *dst++ = *src++;
        --n;
    }

    while(n > 0) /* padding with null terminator in case |src| < n */
    {
        *dst++ = '\0';
        --n;
    }

    return head;
}


int StrnCmp(const char *str1, const char *str2, size_t n)
{
    assert(str1 != NULL);
    assert(str2 != NULL);

    while(n > 0 && *str1 == *str2 && *str1 != '\0')
    {
        ++str1;
        ++str2;
        --n;
    }

    if(n == 0)
    {
        return 0;
    }

    return (unsigned char)*str1 - (unsigned char)*str2;
}


int StrCaseCmp(const char* s1, const char* s2)
{
    unsigned char c1, c2;

    while(*s1 && *s2)
    {
        c1 = (*s1 >= 'A' && *s1 <= 'Z') ? *s1 - 'A' + 'a' : *s1;
        c2 = (*s2 >= 'A' && *s2 <= 'Z') ? *s2 - 'A' + 'a' : *s2;

        if(c1 != c2)
        {
            return c1 - c2;
        }

        ++s1;
        ++s2;
    }

    c1 = (*s1 >= 'A' && *s1 <= 'Z') ? *s1 - 'A' + 'a' : *s1;
    c2 = (*s2 >= 'A' && *s2 <= 'Z') ? *s2 - 'A' + 'a' : *s2;

    return c1 - c2;
}

char* StrChr(const char *str, int ch)
{
    char* iterator = (char*)str;

    while(*iterator != '\0')
    {
        if(*iterator == ch)
        {
            return iterator;
        }
        ++iterator;
    }

    if(ch == '\0')
    {
        return iterator;
    }

    return NULL;
}

char* StrDup(const char* string)
{
    char* duplicate_string = NULL;
    size_t len = StrLen(string);

    duplicate_string = (char*)malloc(len + 1);
    if(NULL == duplicate_string)
    {
        return NULL;
    }

    StrCpy(duplicate_string, string);

    return duplicate_string;
}


char* StrCat(char *dest, const char *src)
{
	char* dest_traverser = (char*)dest;
	
	assert(NULL != dest);
        assert(NULL != src);
        
	while('\0' != (*dest_traverser))
	{	++dest_traverser;
	
	}
	
	StrCpy(dest_traverser, src);
	
	return dest;

}

char* StrnCat(char *dest, const char *src, size_t n)
{
    char* dest_traverser = dest;
    char* src_traverser = (char*)src;
    
    assert(NULL != dest);
    assert(NULL != src);
    
    while (*dest_traverser != '\0')
    {
        ++dest_traverser;
    }
	
    while (n > 0 && *src_traverser != '\0')
    {
        *dest_traverser = *src_traverser;
        ++dest_traverser;
        ++src_traverser;
        --n;
    }
	
    *dest_traverser = '\0';
	
    return dest;
}


char* StrStr(const char *s1, const char *s2)
{
    char* traverse_s1 = (char*)s1;
    char first_letter_of_s2 = *s2;
    size_t str2_len = StrLen(s2);
    int strcmp_res = -1;

    if ('\0' == *s2)
    {
        return (char*)s1;
    }

    while ('\0' != *traverse_s1 )
    {
        traverse_s1 = StrChr(traverse_s1, first_letter_of_s2);
        if (NULL == traverse_s1 )
        {
            return NULL;
        }

        strcmp_res = StrnCmp(traverse_s1, s2, str2_len);
        if (0 == strcmp_res)
        {
            return traverse_s1;
        }

        ++traverse_s1;
    }

    return NULL;
}

size_t StrSpn(const char* str1, const char* str2)
{
    char* traverse_s1 = (char*)str1;
    char* traverse_s2 = (char*)str2;
    size_t seq_len = 0;
    
    while ('\0' != *traverse_s1)
    {
        traverse_s2 = (char*)str2;

        while (*traverse_s2 != '\0')
        {
            if (*traverse_s1 == *traverse_s2)
            {
                ++seq_len;
                break;
            }
            ++traverse_s2;
        }
        
        if (*traverse_s2 == '\0')
        {
            return seq_len;
        }

        ++traverse_s1;
    }

    return seq_len;
}






