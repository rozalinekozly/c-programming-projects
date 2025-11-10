#include <stdio.h> /* standard library input and output */
#include <math.h> /* included to use pow function for the tests */

  /* functions */
double Power(int); /* function to calculate 10 to the power of a given integer */
int Flip(int); /* function that flips the order of a given integer */
void Swap(int* , int*); /* function that swaps between 2 integers */
size_t PrintHelloHex(void); /* function that prints "Hello World!" using hex values */

  /* testers */
size_t TestPower(int*, size_t);
size_t TestFlip(int*, int*,size_t);
size_t TestSwap(int*, int*);


size_t PrintHelloHex() 
{
    const char str[] = {0x22, 0x48 ,0x65 ,0x6C ,0x6C ,0x6F ,0x20 ,0x57 ,0x6F ,0x72 ,0x6C,0x64 ,0x21 ,0x22};
    
    printf("%s ", str); 
    printf("- TEST PASSED\n\n");
    return 1;
}


void Swap(int* num1, int* num2)
{
  int tmp;
  
  if((NULL == num1) || (NULL == num2)) 
  {
    printf("ILLEGAL INPUT\n\n"); 
    return;
  }
  tmp = *num1;
  *num1 = *num2;
  *num2 = tmp;
}

size_t TestSwap(int* num1, int* num2)
{
  int old_num1_val = 0;
  int old_num2_val = 0;
  
  if((NULL == num1) || (NULL == num2)) 
  {
    printf("ILLEGAL TEST\n\n"); 
    return 0;  /* ILLEGAL TEST */
  }

  old_num1_val = *num1;
  old_num2_val = *num2;
  
  Swap(num1, num2);

  if ((*num1 == old_num2_val) && (*num2 == old_num1_val))
  {
	  printf("- TEST PASSED\n\n");
	  return 1;
  }
  else
  {
          printf("Before: a = %d, b = %d - ", old_num1_val, old_num2_val);
          printf("After: a = %d, b = %d - ", *num1, *num2);
	  printf("- TEST FAILED\n\n");
	  return 0;
  } 
}


double Power(int exp)
{
      double result = 1; /* initialize to ave the value of 10^0 */
      double multiplier = 10;
      
      if (exp < 0) 
       {
          multiplier = 0.1;
          exp = exp * (-1);
       }
      while (exp > 0)
       {
         result *= multiplier;
         exp--;
       }
      return result;
}


size_t TestPower(int* arr, size_t size)
{
      size_t i = 0;
      double result = 0, lib_result = 0;

      for (i = 0 ; i < size ; i++)
      {
         result = Power(arr[i]);
         lib_result = pow(10, arr[i]);
         if (fabs(result - lib_result) > 0.0001)
          {
              printf("power(%d) = %.2f ",arr[i],result);
              printf(" - TEST FAILED\n\n");
              return 0;
          }
      }
      printf(" - TEST PASSED\n\n");
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



size_t TestFlip(int* input, int* expected, size_t size)
{
      size_t i = 0;
      int result = 0;
      
      for(i = 0 ; i < size ; i++)
      {
            result = Flip(input[i]);
            if (result != expected[i])
              {
                   printf("flip(%d) = %d - ", input[i], result);
                   printf("expected: %d - ", expected[i]);
                   printf(" - TEST FAILED\n\n");
                   return 0; 
              }
            
        }
      printf(" - TEST PASSED\n\n");
      return 1;
}



int main()
{
        
        /* power function arguments */
       int arr_test_pow[] = {0,1,-1,10,-10,-12,4};
       size_t size_pow = sizeof(arr_test_pow)/sizeof(int);
       
       /* flip function arguments */
       int arr_test_flip[] = {12340, -1111, 909090, 1111000};
       int arr_exp_flip[] = {4321, -1111, 90909, 1111};
       size_t size_flip = sizeof(arr_test_flip)/sizeof(int);
       
       /* swap function arguments */ 
        int swap1 = 55;
        int swap2 = 66;
        
        /* counter of successd tests (out of 4) */
        size_t successed = 0;
        
        printf("\n1 - Print hello world test "); 
        successed += PrintHelloHex();
        
        printf("2 - 10^n function test: "); 
        successed += TestPower(arr_test_pow, size_pow);
        
        printf("3 - Flip function test: "); 
        successed += TestFlip(arr_test_flip,arr_exp_flip, size_flip);
        
        printf("4 - Swap function test: "); 
        successed += TestSwap(&swap1, &swap2);
        
        printf("Successed in %lu tests out of 4\n\n", successed);
        
        return 0;
}



