#include "ws1.h" 
#include <stdio.h>
int flip(int num)
{
   int flipped = 0;
   
   while(num != 0)
   {
       flipped *= 10;
       flipped += (num % 10);
       num /= 10;
   
   }
   
   return flipped;

}
