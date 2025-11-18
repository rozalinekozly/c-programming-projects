#include <stdio.h> /* getchar() */
#include <stdlib.h> /* exit(); - to force quitting from the callee */

#define ESC 27
#define CHAR1 'A'
#define CHAR2 'T'

void DetectLettersIfElse();
void DetectLettersCaseSwitch();

void DetectLettersLUT();
void func1();
void func2();
void func3(); /* AN EMPTY FUNCTION */
void func4(); /* esc program */


int main()
{
	
	DetectLettersLUT();
	
	return 0;

}


void DetectLettersIfElse()
{
	char c = ' ';
	
	while(1)
	{
	
	         c = getchar();
	         if(ESC == c)
	         {
	         	break;
	         }
		else if(CHAR1 == c) 
		{
			printf("A-Pressed\n");
		}
		else if(CHAR2 == c) 
		{
			printf("T-Pressed\n");
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
			
			 printf("A-Pressed\n");
			 
			 break;
			 
			case CHAR2:
			
			printf("T-Pressed\n");
			
			 break;
		 }
	}
}


void func1()
{
	printf("A-Pressed\n");

}
void func2()
{
	printf("T-Pressed\n");
}
void func3() /* AN EMPTY FUNCTION */
{
 	return; /* do nothing*/
}
void func4() /* esc program */
{
	exit(0);
}

void DetectLettersLUT()
{
	void (*functions[256])();
	size_t i = 0;
	int c = ' ';
	
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



