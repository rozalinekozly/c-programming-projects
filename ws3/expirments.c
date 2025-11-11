#include <stdio.h>
#include <string.h>

int main()
{

 char* str1 = "123";
 char str2[28];
 
 char* str3 = strcpy(str2, str1);
 
 printf("%s\n", str3);
 return 0;


}
