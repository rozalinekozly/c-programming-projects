/***************************
*
*
*
*
****************************/

#include <stdio.h> /* getchar() */
#include <stdlib.h> /* exit(); - to force quitting from the callee , system function */

/* special constant used characters */
#define ESC 27
#define CHAR1 'A'
#define CHAR2 'T'
#define ASCII_RANGE 256

/* defining colors for printing */
#define YELLOW        "\033[1;93m"
#define CYAN          "\033[1;96m"
#define WHITE         "\033[1;97m"
#define RED           "\033[1;91m"

/* macros to print to string*/
#define A_PRESSED(X) printf(X "A-Pressed\n"); /* X = color */
#define T_PRESSED(X) printf(X "T-Pressed\n");

/* declaring on functions */
void DetectLettersIfElse();
void DetectLettersCaseSwitch();
void DetectLettersLUT();

/* aux functions (internal functions for LUT implementation) */
static void func1(); /* A_PRESSED*/
static void func2();/* T_PRESSED */
static void func3(); /* AN EMPTY FUNCTION */
static void func4(); /* esc program */


int main()
{

	printf(WHITE  "\nRunning the program using if-else implementation\n\tPress any key (press ESC to go to next implementation)\n");
	DetectLettersIfElse();
	
	printf(WHITE  "\nRunning the program using switch-case implementation\n\tPress any key (press ESC to go to next implementation)\n");
         DetectLettersCaseSwitch();
         
         printf(WHITE "\nRunning the program using LUT implementation\n\tPress any key (press ESC to go to next implementation)\n");
         DetectLettersLUT();
         
 
	return 0;

}


void DetectLettersIfElse()
{
	char c = ' ';
         int ret = 0;
         
	ret = system("stty -icanon -echo");
	
	if(0 != ret)
	{
		printf(RED"command execution did not complete successfully");
		exit(1);
	}
	
	while(1) /* keep reading characters until a ESC key pressed */
	{
	         c = getchar(); /* c holds the characters red from terminal */
	         
	         if(ESC == c)
	         {
	         	break;
	         }
		else if(CHAR1 == c) 
		{
			 A_PRESSED(YELLOW)
		}
		else if(CHAR2 == c) 
		{
			T_PRESSED(CYAN);
		}
	
	}

}


void DetectLettersCaseSwitch()
{	
	while(1)
	{
	         
	        switch(getchar())
	         
	        {
			case ESC:
			 return;
			 break;
		        
			case CHAR1:
			 A_PRESSED(YELLOW) 
		          break;
			 
			case CHAR2:
			T_PRESSED(CYAN);
			 break;
		 }
	}
}


static void func1()
{
	A_PRESSED(YELLOW)

}
static void func2()
{
	T_PRESSED(CYAN);
}
static void func3() 
{
	/* do nothing */
 	return;
}
static void func4() 
{
	int ret = system("stty icanon echo");
	        if(0 != ret)
	{
		printf(RED"command execution did not complete successfully");
		exit(1);
	}
	exit(0);
	
}


void DetectLettersLUT()
{
	void (*functions[ASCII_RANGE])(); /* decalre an array of pointers on functions size = 256 = ASCII values range (unsigned) */
	size_t i = 0; /* iterator on function's cells */
	int c = ' '; /* character to hold read char from pipe(terminalt) */
	
	/* intializing array */
	for(i = 0 ; i < 256 ; i++)
	{
		if( i == 'A')
		{
			functions[i] = func1;
		}
		else if( i == 'T')
		{
			functions[i] = func2;
		}
		else if( i == ESC)
		{
			functions[i] = func4;
		}
		else
		{
			functions[i] = func3;
		}
	
	}
	
	
	while(1)
	{	
	         c = getchar();
	         functions[c]();         
	}
	         

}



