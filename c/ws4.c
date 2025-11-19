/***************************
* Submitter: Rozaline Kozly
* Reviewer : Steve Evushenko
* Date: 19  Nov  2025
* Version 2.0
****************************/
#include <stdio.h> 	/* getchar() */
#include <stdlib.h>  	/* exit(); - to force quitting from the callee , system function */

/* special constant used characters */
#define ESC 27
#define CHAR1 'A'
#define CHAR2 'T'
#define ASCII_RANGE 256
#define PLAY_UNTIL_ESC_ENTERED 1
#define INITIALIZING_VAL 0 
#define SUCCESSED_BASH_OP 0
#define FAILED_BASH_OP 1
#define PROGRAM_ENDED_IN_SUCCESS 0

/* defining colors for printing */
#define YELLOW        "\033[1;93m"
#define CYAN          "\033[1;96m"
#define WHITE         "\033[1;97m"
#define RED           "\033[1;91m"

/* macros to print to string */
#define A_PRESSED(X) printf(X "A-Pressed\n"); /* X = color */
#define T_PRESSED(X) printf(X "T-Pressed\n");
#define DISABLE_ICANON system("stty -icanon"); 
#define DISABLE_ECHO  system("stty -echo"); 
#define ENABLE_ICANON  system("stty icanon"); 
#define ENABLE_ECHO  system("stty echo"); 

/* declaring on functions */
/* all the 3 functions perform the same thing;
   print A-PRESSED / T-PRESSED in case A or T
   keys entered by the user, it does it in an environment 
   where echo (printing to the terminal) and icanon are disabled (line based -> character based) */
void DetectLettersIfElse();
void DetectLettersCaseSwitch();
void DetectLettersLUT();

/* aux functions (internal functions for LUT implementation) */
static void func1(); /* A_PRESSED*/
static void func2();/* T_PRESSED */
static void func3(); /* AN EMPTY FUNCTION */
static void func4(); /* escape function */


int main()
{
	printf(WHITE "\nRunning the program using if-else implementation\n\tPress any key (press ESC to go to next implementation)\n");
	DetectLettersIfElse();
	
	printf(WHITE "\nRunning the program using switch-case implementation\n\tPress any key (press ESC to go to next implementation)\n");
        DetectLettersCaseSwitch();
         
        printf(WHITE "\nRunning the program using LUT implementation\n\tPress any key (press ESC to go to next implementation)\n");
        DetectLettersLUT();
         
	return PROGRAM_ENDED_IN_SUCCESS;
}

/* implementation using if-else */
void DetectLettersIfElse()
{
        char c = INITIALIZING_VAL;	         /* character to hold current char */
        int ret = INITIALIZING_VAL; 	/* return value from system function */
         
	ret = system("stty -icanon -echo"); /* configure bash to disable echo and icanon */
	
	if(SUCCESSED_BASH_OP != ret)
	{
		exit(FAILED_BASH_OP);
	}
	
	while (PLAY_UNTIL_ESC_ENTERED) 	/* keep reading characters until an ESC key pressed */
	{
	         c = getchar(); 		/* c holds the characters red from terminal */
	         
	         if (ESC == c)
	         {
	         	break;
	         }
		else if (CHAR1 == c) 
		{
			 A_PRESSED(YELLOW)
		}
		else if (CHAR2 == c) 
		{
			T_PRESSED(CYAN);
		}
	}
}

/* implementation using switch-case */
void DetectLettersCaseSwitch()
{	
	while (PLAY_UNTIL_ESC_ENTERED)
	{      
	   switch (getchar())
	        {
			case ESC:
			return;
			break; /* this break is not reachable - but for the consistency and conventions I will keep it */
		        
			case CHAR1:
			A_PRESSED(YELLOW) 
		        break;
			 
			case CHAR2:
			T_PRESSED(CYAN);
			 break;
		 }
	}
}

/* implementation using LUT */
void DetectLettersLUT()
{
	void (*functions[ASCII_RANGE])(); 		/* declare an array of pointers on functions size = 256 = ASCII values range (unsigned) */
	size_t i = INITIALIZING_VAL; 		/* iterator on function's cells */
	int c = INITIALIZING_VAL; 			/* character to hold read char from pipe(terminal) */
	
	/* initializing array */
	for (i = 0 ; i < ASCII_RANGE ; i++)
	{
	      functions[i] = func3; 		/* initialize all functions */
	}
	
	functions[CHAR1] = func1;
	functions[CHAR2] = func2;
        functions[ESC] = func4;
	
	while (PLAY_UNTIL_ESC_ENTERED)
	{	
	         c = getchar();
	         functions[(unsigned char) c ]();         
	}
}

/* aux functions */
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
	int ret = system("stty icanon echo");         /* perform proper exiting */
	if (SUCCESSED_BASH_OP != ret)
	{
		printf(RED"command execution did not complete successfully");
		exit(FAILED_BASH_OP);
	}
	exit(PROGRAM_ENDED_IN_SUCCESS);
	
}



