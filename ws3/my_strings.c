#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include "String.h"

#define RESET         "\033[0m"

#define RED           "\033[1;91m"
#define WHITE         "\033[1;97m"
#define CYAN          "\033[1;96m"
#define GREEN         "\033[1;92m"
#define YELLOW        "\033[1;93m"
#define PINK "\033[1;95m"



size_t TestStrcpy();
size_t TestStrncpy();



int main()
{
	
	size_t passed_func = 0;
         passed_func += TestStrcpy();
         printf(PINK "\t-----------------------------------");
         printf(PINK "\n\t\tPASSED %lu FUNCTIONS\n", passed_func);
         
         return 0;


}

size_t TestStrcpy()
{
	  size_t i = 0;
	  const char* src[] = {"hello", "world", "Infinty Labs R&D",
	  	        "Rina", "Erik", "workshop 3!!@@@&&&"};
	  char* dst;
	  size_t test_size = sizeof(src)/sizeof(src[0]);
	  size_t current_tested_str_len = 0;
	  size_t test_res = 0;
	  size_t strcmp_ret_val = -1;
	  
	  printf(YELLOW "\t-----TESTING StrCpy FUNCTION: -----\n");
	  for(i = 0 ; i < test_size ; i++)
	  {
	  	printf(WHITE "Test %lu: input = ", i);
	  	printf(CYAN "%s",src[i]);
	  	current_tested_str_len = strlen(src[i]) + 1;
	  	dst = (char*)malloc(current_tested_str_len);
	  	if(!dst)
	  	{
	  		printf(CYAN " - MALLOC FAILED\n");
	  		return 0;
	  	
	  	}
	  	dst = StrCpy(dst, src[i]);
	  	strcmp_ret_val = strcmp(dst, src[i]);
	  	free(dst);
	  	if(strcmp_ret_val == 0) test_res++;
	  	if(strcmp_ret_val != 0)
	  	{
			printf(RED " - FAILED");
			return 0;
					
	  	}
	  		printf(GREEN" - PASSED\n");
	  
	  }
	  printf(GREEN"\nPASSED %lu TESTS!\n", test_res);
	  return 1;


}






