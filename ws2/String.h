#include <stddef.h>
#ifndef STRING_H
#define STRING_H

#define RESET         "\033[0m"
#define RED           "\033[1;91m"
#define WHITE         "\033[1;97m"
#define CYAN          "\033[1;96m"
#define GREEN         "\033[1;92m"
#define YELLOW        "\033[1;93m"
#define PINK          "\033[1;95m"



/* Undefined behaviour if:
 * 1 - dst buffer is too small
 * 2 - src or dst are NULL
 * 3 - src and dst overlap
 * 4 - dst points to read-only memory (in other words ;string literal)
 * if used correctly then this function makes sure to return a valid 
 * string (ends with \0).
 */
char* StrCpy(char* dst, const char* src);

/* strncpy copies up to n chars from src to dst.
   - legal : |dst| >= n, src & dst valid (non-NULL)
   - risky :
       1- |dst| < n may cause overflow
       2- src = NULL or dst = NULL then segmentation fault
       3- |src| >= n → no '\0' added may cause undefined       
       behaviour later  
*/

char* StrnCpy(char* dst, const char* src, size_t n);

/* Undefined behaviour if:
 * 1 - dst buffer contains fewer than n empty slots
 * 2 - src / dst are NULL
 * 3 - src and dst overlap
 * 4 - dst points to read-only memory (string literal)
 *
 * Behaviour summary according to the man page:
 * - Copies at most n characters from src into dst.
 * - If src is shorter than n, pads the remaining bytes with '\0'
 *   until exactly n bytes have been written.
 * - If src is at least n slots long, copies exactly n bytes and does NOT
 *   append a terminating '\0'. In this case dst is NOT guaranteed to be
 *   a valid C-string.
 */
int StrnCmp(const char *str1, const char *str2, size_t n);

/* StrCaseCmp compares two strings case-insensitively.
 * Returns 0 if equal, <0 if s1<s2, >0 if s1>s2 ignoring case.
 *
 * Undefined behaviour if:
 * 1. s1 or s2 are NULL.
 * 2. The memory regions overlap.
 */
int StrCaseCmp(const char *s1, const char *s2);

/*  StrChr function takes as an arguments a pointer to a string and a character  
    and returns a pointer to the first occurrence of the specified character  
    within the string if it did not found it it returns NULL */
char* StrChr(const char* str, int ch);


/*  StrDup function dynamically allocates a space to put a string content in it 
    and it copies the content.. */
char* StrDup(const char *string);

/* StrCat function concatinate the two strings it's given .
   The behavior of strcat() is undefined if:
   - the destination array is not large enough for the contents of both src and 
     dest and the terminating null character
   - if the string overlaps.
   - if either dest or src is not a pointer to a null-terminated byte string.*/

char* StrCat(char *dest, const char *src);
/* StrnCat function, catenate the first n letters from src to dest
*/
char* StrnCat (char *dest, const char *src, size_t n);

/* StrStr takes 2 arguments a string and a subsequnce string 
    we should return the part of the the string starting from the first  
    occurance of the substring(as a whole)
    if not found return NULL */
char* StrStr (const char *s1, const char *s2);



/* StrSpn takes as an argument two strings where the second argument (str2) 
   acts as the "bank of letters" and str1 is the data, it's return value is 
   the length of the sequence (starting from first letter of str1) that 
   contains letters from str2 (the bank) only */
size_t StrSpn(const char *str1, const char *str2);



char* StrTok(char *str, const char *delim);

/*practice questions in the worksheet*/
/* return values 0 = is not a palindrom, 1 = a palindrome */
size_t IsPalindrome(char* str);

void SevenBoom (int start, int end);

char* WhiteSpaceReview(char* str);


#endif
