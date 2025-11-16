/*******************************************
*
*
********************************************/
#include <stddef.h> /* using size_t data type */
#include <string.h> /* used strlen() */
#include <stdlib.h> /* strdup uses malloc */
#include <stdio.h> /* seven boom uses printf */
#include "String.h" /* my declarations*/
#include <assert.h> /* for asserts */
#define SEVEN 7

size_t StrLen(const char* str)
{
  size_t len = 0;
  assert(NULL != str);
  while('\0' != *str)
  {
    ++len;
  }
  
  return len;

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
    size_t counter = 0;
    char* head = dst;

    assert(NULL != dst);
    assert(NULL != src);
    assert(StrLen(dest) <= n);
    
    /* copy up to n chars or until \0 */
    while ((*src != '\0') && (counter < n))
    {
        *dst = *src;
        ++src;
        ++dst;
        ++counter;
    }

    /* if src shorter than n then pad with \0 */
    while (counter < n)
    {
        *dst = '\0';
        ++dst;
        ++counter;
    }

    return head;
}


int StrCmp(const char *str1, const char *str2)
{
	int diff = 0;
	size_t i = 0;
	
	assert(NULL !=str1);
	assert(NULL !=str2);
	
	while('\0' != *str1 && '\0' != *str2)
	{
		diff = str1[i] - str2[i];
		if(diff != 0) 
		{
			return diff;
		}
		
		++i;
		
	}
	
	if('\0' == *str1)
	{
	  return (*str1);
	}
	else
	{
	  return (0 - *str2);
	}
	
	return 0;
}

int StrnCmp(const char *str1, const char *str2, size_t n)
{
	int diff = 0;
	size_t i = 0;
	
	assert(NULL !=str1);
	assert(NULL !=str2);
	
	while(n>0)
	{
		diff = str1[i] - str2[i];
		if(diff != 0) 
		{
			return diff;
		}
		
		++i;
		--n;
	}
	
	return 0;

}

int StrCaseCmp(const char* s1, const char* s2)
{
	int i = 0;
	int diff = 0;
	
	char c1 = ' ';
	char c2 = ' ';
	  
 	while('\0' != s1[i] && '\0' != s2[i])
 	{
 		c1 = s1[i];
 		c2 = s2[i];
 		if(c1 >= 'A' && c1 <= 'Z')
 		{
 			c1 = c1 - 'A' + 'a';
 		}
 		if(c2 >= 'A' && c2 <= 'Z')
 		{
 			c2 = c2 - 'A' + 'a';
 		}
 		
 		diff = c1 - c2;
 		if(0 != diff)
 		{
 			return diff;
 		}
 		++i;
 	}
 	
 	if('\0' != s1[i])
 	{
 		return ((int)s1[i]);
 	}
 	else if ('\0' != s2[i])
 	{
 		return ((int)s2[i]*(-1));
 	}
 	
 	return diff;
}


char* StrChr(const char *str, int ch)
{

	char* iterator = (char*) str; 

	while('\0' != (*iterator))
	{
		if(ch == *iterator)
		{
			return iterator;		
		}
		iterator++;;		
	
	}
	
	if('\0' == ch)
	{
		return iterator; /* the last char \0 in the given string*/
	}
	
	return NULL; 

}


char* StrDup(const char* string)
{
	char* duplicate_string = NULL;
	size_t i  = 0;
	duplicate_string = (char*)malloc(strlen(string)+1);
	if(NULL == duplicate_string) 
	{
		return NULL;
	}
	
	while('\0' != string[i])
	{
		duplicate_string[i] = string[i];
		i++;	
	}
	
	StrCpy(duplicate_string,string);
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
    size_t str2_len = strlen(s2);
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


/* questions in the worksheet*/
size_t IsPalindrome(char* str)
{
    size_t len = strlen(str);
    size_t i = 0;
    size_t j = len - 1;

    if (len <= 1)
    {
        return 1;
    }



    while (j > i)
    {
        if (str[i] != str[j])
        {
            return 0;
        }
        ++i;
        --j;
    }

    return 1;
}




void SevenBoom (int start, int end)
{
	int iterator = start;
	int remainder = 0;
	int num = 0;
	size_t flag = 0;
	size_t counter_to_new_line = 10;
	
	/* invalid range input */
	if(start > end)
	{
		printf(RED "INVALID INPUT!\n");
	}
	
	
	for( iterator = start ; iterator <= end ; iterator++)
	{
		flag = 0;
		if(counter_to_new_line == 0)
		{
			printf("\n");
			counter_to_new_line = 10;
		
		}

		
		/* check if it is dividable by 7 */
		if(iterator % SEVEN == 0)
		{
			printf("BOOM ");
			counter_to_new_line--;
			flag = 1;
		
		}
		/*check if 7 is one of it's digits */
		else 
		{
			num = iterator;
			while(num != 0)
			{
				remainder = num % 10;
				if(remainder == SEVEN)
				{
					printf("BOOM ");
					counter_to_new_line--;
					flag = 1;
					break;
				}
				num = num / 10;
			}
		
		}
		if(flag == 0)
		{
			printf("%d ", iterator);
			counter_to_new_line--;
		}
		
		
	}
	
	printf("\n");


}

char* WhiteSpaceReview(char* str)
{
    char* read = str; /* ptr that reads */
    char* write = str; /* ptr that writes*/
    int in_ws = 0; /* flag to signal if we are in a whitespace sequence or not */
    char first_ws = 0; /* holds first whitespace in the current sequence (space \ tab)*/

   
    /* skip spaces and tabs from the begining of the string */
    while (*read == ' ' || *read == '\t')  
    {
        ++read;
    }
 
 
    /* middle & last part of the string */
    while (*read != '\0')
    {
        if (*read == ' ' || *read == '\t') /* a whitespace found */
        {
        	   /* found first whitespace in the sequence */
            if (!in_ws) 
            {
                in_ws = 1;
                first_ws = *read; /* save first whitespace in the sequence */
            }
            ++read; 
        }
        else /* a sequence of whitespaces stopped (found a different char)*/
        {
            if (in_ws && write != str) /* we skip writing in the beginning 
                                        (prevents insertions of ws at the start*/
            {
                *write = first_ws;
                ++write;
            }
            in_ws = 0;
            *write = *read;
            ++write;
            ++read;
        }
    }
    *write = '\0';

    return str;
}
