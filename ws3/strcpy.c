#include <stdio.h>
#include "String.h"
/* srcpy copies from src to dest including '\0'.
   According to it's man page, strcpy doen't check NULL/lengths
 - legal : if |dst| >= |src| 
 - illegal and may cause undefined behaviour: 
   1- if |dst| < |src| (might distroy memory) 
   2- src =   NULL
   3- dst type is const (segmentation fault & undefined behaviour)  */
char* StrCpy(char* dst, const char* src)
{
   char* copied_string = dst;
   
   while(*src != '\0')
   {
   	*dst = *src;
   	src++;
   	dst++;
   }
   
   *dst = '\0'; /* strcpy copies the \0 char too*/
   return copied_string;

}


