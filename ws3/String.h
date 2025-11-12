#ifndef STRING_H
#define STRING_H

/* srcpy copies from src to dest including '\0'.
According to it's man page, strcpy doen't check NULL/lengths
 - legal : if |dst| >= |src| 
 - illegal and may cause undefined behaviour: 
   1- if |dst| < |src| (might distroy memory) 
   2- src =   NULL
   3- dst type is const (segmentation fault & undefined behaviour)  */
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
#endif 
