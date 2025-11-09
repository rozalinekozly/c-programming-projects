#include "ws1.h" 
#include <stdio.h>
float power(int n)
{
   float res = 1;
   float unit = 10;
   if(n == 0) return 1;
   if(n < 0) 
   {
      unit = 0.1;
      n = n * (-1);
   }
   
   while(n > 0)
   {
     res *= unit;
     n--;
   }
   +
   return res;

}
