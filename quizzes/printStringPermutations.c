#include <stdio.h>
#include <string.h>
/*belief: this funciton can print all permutations of str, from
	letter_to_swap pointer (everything before it keeps it the same) */
void PrintAllPermWrapped(char* str, char* letter_to_swap);

void Swap(char* a, char* b)
{
	char tmp = *a;
	*a = *b;
	*b = tmp;
}

 void PrintAllPerm(char* str)
 {
 	PrintAllPermWrapped(str, str);
 }
 
void PrintAllPermWrapped(char* str, char* letter_to_swap)
{
	char* runner = letter_to_swap;
	/*trivial case i can solve */
	if('\0' == *letter_to_swap)
	{
		printf("%s\n", str);
	}
	
	while('\0' != *runner)
	{
		/*pick out one letter and place it at the begining*/
		Swap(str, runner);
		/*print all permutation with that letter at the begining */
		PrintAllPermWrapped(str, letter_to_swap+1);
		/*return string to it's state (swap back)*/
		Swap(str, runner);
		/*increment runner so another letter will be at the front*/
		++runner;
	}
}

int main() 
{
	/*defining like that and not char* str so it won't be string literal*/
    char str[] = "abc";
    PrintAllPerm(str);
    return 0;
}
