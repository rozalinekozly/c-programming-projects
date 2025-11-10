#include <stdio.h> /* standard library input and output */
#include <math.h> /* included to use pow function for the tests */

  /* functions */
float Power(int n); /* function to calculate 10 to the power of a given integer */
int Flip(int num); /* function that flips the order of a given integer */
void Swap(int* a, int* b); /* function that swaps between 2 integers */
int PrintHelloHex(void); /* function that prints "Hello World!" using hex values */

  /* testers */
int TestPower(int* arr,int size);
int TestFlip(int* , int* ,int);
int TestSwap(int* , int* );


int PrintHelloHex()
{
    const char str[] = {0x22, 0x48 ,0x65 ,0x6C ,0x6C ,0x6F ,0x20 ,0x57 ,0x6F ,0x72 ,0x6C,0x64 ,0x21 ,0x22};
    printf("%s ", str); 
    printf("- TEST PASSED\n\n");
    return 1;
}


void Swap(int* a, int* b)
{
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}

int TestSwap(int* a, int* b)
{
  int old_a_val = *a;
  int old_b_val = *b;
  Swap(a, b);
  printf("Before: a = %d, b = %d - ", old_a_val, old_b_val);
  printf("After: a = %d, b = %d - ", *a, *b);

	if ((*a == old_b_val) && (*b == old_a_val))
	{
		printf("TEST PASSED\n\n");
		return 1;
	}
	else
	{
		printf("TEST FAILED\n\n");
		return 0;
	}
    
}


float Power(int n)
{
   float result = 1;
   float multiplier = 10;
   if (n == 0) return 1;
   if (n < 0) 
     {
        multiplier = 0.1;
        n = n * (-1);
     }
   while (n > 0)
     {
       result *= multiplier;
       n--;
     }
   return result;

}



int TestPower(int* arr, int size)
{
    int i;
    double result, lib_result;
  
   for(i = 0; i < size;i++)
   {
   
       result = Power(arr[i]);
       lib_result = pow(10, arr[i]);
       printf("power(%d) = %f ",arr[i],result);
       if (fabs(result - lib_result) > 0.0001)
        {
            printf(" - TEST FAILED\n\n");
            return 0;
        }
        else
        {
            printf(" - TEST PASSED\n");
        }
  }
  
  return 1;
}




int Flip(int num)
{
   int flipped = 0;
   while (num != 0)
     {
         flipped *= 10;
         flipped += (num % 10);
         num /= 10;
     
     }
   
   return flipped;
}



int TestFlip(int* input, int* expected, int size)
{
   int i;
   int result;
   for(i = 0 ; i< size ; i++)
    {
          result = Flip(input[i]);
          printf("flip(%d) = %d - ", input[i], result);
          printf("Expected: %d - ", expected[i]);

          if (result == expected[i])
            {
                printf("TEST PASSED\n\n");
               
            }
          else
            {
                printf("TEST FAILED\n\n");
                return 0;
            }
      }
      
    return 1;
}



int main()
{

   int arr_test_pow[] = {0,1,-1,10,-10,-12,1};
   int size_pow = sizeof(arr_test_pow)/sizeof(int);
   
   int arr_test_flip[] = {12340, 1111, 909090, 1111000};
   int arr_exp_flip[] = {4321, 1111, 90909, 1111};
   int size_flip = sizeof(arr_test_flip)/sizeof(int);
    
    int swap1 = 55;
    int swap2 = 66;
    
    int successed = 0;
    
    printf("\n1 - Print hello world test: \n\n"); 
    successed += PrintHelloHex();
    
    printf("2 - 10^n function test: \n\n"); 
    successed += TestPower(arr_test_pow, size_pow);
    
    printf("3 - Flip function test: \n\n"); 
    successed += TestFlip(arr_test_flip,arr_exp_flip, size_flip);
    
    printf("4 - Swap function test: \n\n"); 
    successed += TestSwap(&swap1, &swap2);
    
    printf("Successed in %d tests out of 4\n\n", successed);
    
    return 0;
}



