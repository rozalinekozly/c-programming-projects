/*******************************************
* ROZALINE KOZLY
* REVIWER : GIL
* DATE 16-11-2025
********************************************/
#ifndef STRING_H
#define STRING_H


/*------------------------------------------------------
 * StrLen
 * 
 * Description:
 *   Returns the length of a null-terminated C-string.
 *
 * Return Values:
 *   Success: number of characters before the '\0'.
 *   Failure: no failure return value (never returns error).
 *
 * Undefined Behaviour:
 *   Passing a NULL pointer or a non-null-terminated string
 *   results in undefined behaviour, same as the standard strlen().
 *-----------------------------------------------------*/
size_t StrLen(const char* str);


/*------------------------------------------------------
 * StrCmp
 *
 * Description:
 *   Compares two null-terminated strings lexicographically.
 *
 * Return Values:
 *   Success: negative/zero/positive according to strcmp().
 *   Failure: no failure return value.
 *
 * Undefined Behaviour:
 *   Passing NULL or non-null-terminated strings is undefined,
 *   same as the standard strcmp().
 *-----------------------------------------------------*/
int StrCmp(const char *s1, const char *s2);


/*------------------------------------------------------
 * StrCpy
 *
 * Description:
 *   Copies src (including '\0') into dst.
 *
 * Return Values:
 *   Success: pointer to dst.
 *   Failure: no failure return value.
 *
 * Undefined Behaviour:
 *   Passing NULL pointers or overlapping buffers is undefined,
 *   same as the standard strcpy().
 *-----------------------------------------------------*/
char* StrCpy(char* dst, const char* src);


/*------------------------------------------------------
 * StrnCpy
 *
 * Description:
 *   Copies up to n characters from src to dst.
 *   Pads with '\0' if src is shorter than n.
 *
 * Return Values:
 *   Success: pointer to dst.
 *   Failure: no failure return value.
 *
 * Undefined Behaviour:
 *   Passing NULL or overlapping buffers is undefined.
 *   If src is longer than n, the resulting dst is not
 *   null-terminated, matching the behaviour of strncpy().
 *-----------------------------------------------------*/
char* StrnCpy(char* dst, const char* src, size_t n);


/*------------------------------------------------------
 * StrnCmp
 *
 * Description:
 *   Compares up to n characters of two strings.
 *
 * Return Values:
 *   Success: negative/zero/positive according to strncmp().
 *   Failure: no failure return value.
 *
 * Undefined Behaviour:
 *   Passing NULL or non-null-terminated strings results
 *   in undefined behaviour (same as strncmp()).
 *-----------------------------------------------------*/
int StrnCmp(const char *str1, const char *str2, size_t n);


/*------------------------------------------------------
 * StrCaseCmp
 *
 * Description:
 *   Case-insensitive lexicographic comparison.
 *
 * Return Values:
 *   Success: negative/zero/positive according to strcasecmp().
 *   Failure: no failure return value.
 *
 * Undefined Behaviour:
 *   Passing NULL pointers or non-null-terminated strings
 *   results in undefined behaviour.
 *-----------------------------------------------------*/
int StrCaseCmp(const char *s1, const char *s2);


/*------------------------------------------------------
 * StrChr
 *
 * Description:
 *   Returns a pointer to the first occurrence of character ch in str.
 *
 * Return Values:
 *   Success: pointer to the found character (including '\0').
 *   Failure: NULL if ch does not appear in str.
 *
 * Undefined Behaviour:
 *   Passing NULL or non-null-terminated strings is undefined,
 *   same as the standard strchr().
 *-----------------------------------------------------*/
char* StrChr(const char* str, int ch);


/*------------------------------------------------------
 * StrDup
 *
 * Description:
 *   Allocates memory and duplicates the given string.
 *
 * Return Values:
 *   Success: pointer to newly allocated copy.
 *   Failure: NULL if malloc fails.
 *
 * Undefined Behaviour:
 *   Passing NULL or a non-null-terminated string is undefined,
 *   same as strdup().
 *-----------------------------------------------------*/
char* StrDup(const char *string);


/*------------------------------------------------------
 * StrCat
 *
 * Description:
 *   Appends src to the end of dest.
 *
 * Return Values:
 *   Success: pointer to dest.
 *   Failure: no failure return value.
 *
 * Undefined Behaviour:
 *   Passing NULL or overlapping buffers is undefined.
 *   dest must have enough space, exactly like strcat().
 *-----------------------------------------------------*/
char* StrCat(char *dest, const char *src);


/*------------------------------------------------------
 * StrnCat
 *
 * Description:
 *   Appends up to n characters from src to dest.
 *
 * Return Values:
 *   Success: pointer to dest.
 *   Failure: no failure return value.
 *
 * Undefined Behaviour:
 *   Passing NULL or overlapping buffers is undefined.
 *   dest must have enough space, same as strncat().
 *-----------------------------------------------------*/
char* StrnCat (char *dest, const char *src, size_t n);


/*------------------------------------------------------
 * StrStr
 *
 * Description:
 *   Finds the first occurrence of substring s2 in s1.
 *
 * Return Values:
 *   Success: pointer to the first match.
 *   Failure: NULL if s2 does not appear in s1.
 *
 * Undefined Behaviour:
 *   Passing NULL or non-null-terminated strings is undefined,
 *   same as strstr().
 *-----------------------------------------------------*/
char* StrStr (const char *s1, const char *s2);


/*------------------------------------------------------
 * StrSpn
 *
 * Description:
 *   Returns the length of the initial segment of str1
 *   consisting only of characters from str2.
 *
 * Return Values:
 *   Success: the length of the matching prefix.
 *   Failure: no failure return value.
 *
 * Undefined Behaviour:
 *   Passing NULL or non-null-terminated strings is undefined,
 *   matching the behaviour of strspn().
 *-----------------------------------------------------*/
size_t StrSpn(const char *str1, const char *str2);



#endif
