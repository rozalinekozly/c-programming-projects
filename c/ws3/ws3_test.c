#include "ws3.h"
#include <assert.h>
#include <stdio.h>

/* macro to silent an argument (to prevent unused paramenter warning) */
#define UNUSED(x) (void)(x)

/*colors used in printing */		
#define RED           "\033[1;91m"
#define WHITE         "\033[1;97m"
#define CYAN          "\033[1;96m"
#define GREEN         "\033[1;92m"
#define YELLOW        "\033[1;93m"

#define NUM_OF_TESTS 2
size_t TestJosephus(void);
size_t TestSum2D(void);
void PrintDataTypeSizes(void);
void PrintEnvVarInLowerCase(char**);


int main(int argc, char *argv[], char *envp[])
{
    size_t counter = 0;
    UNUSED(argc);/* compiler treat thoese as warnings (for not using them) so */
    UNUSED(argv);/* we silent them */
    

    counter += TestSum2D();
    counter += TestJosephus();
    printf(YELLOW "\t-----PRINTING DATA TYPES & THEIR SIZES FUNCTION: -----\n");
    PrintDataTypeSizes();
      printf(YELLOW "\t-----PRINTING ENVIRONMENT VARIABLES IN LOWER CASE FUNCTION: -----\n");
    PrintEnvVarInLowerCase(envp);
    
    if(counter == NUM_OF_TESTS)
    {
      printf(CYAN"\n\n\t\tPASSED ALL TESTS!\n");
       printf(CYAN"\t\tWELL DONE ROZA!\n\n");
    }
    

    return 0;
}


size_t TestSum2D()
{
    int arr1[2][COLS] = {
        {1,1,1},
        {1,1,1}
    };

    int arr2[3][COLS] = {
        {2,2,2},
        {3,3,3},
        {1,1,1}
    };


    printf(YELLOW "\t-----TESTING Sum2D FUNCTION: -----\n");
    
    /* Test 1 */
    if (Sum2D(arr1, 2) != 6)
    {
        printf(RED"\t\tTestSum2D FAILED on arr1\n");
        return 0;
    }

    /* Test 2 */
    if (Sum2D(arr2, 3) != 18)
    {
        printf(RED"\t\tTestSum2D FAILED on arr2\n");
        return 0;
    }

    printf(GREEN"\n\t\tAll tests passed.\n\n");
    return 1;
}


size_t TestJosephus()
{
    int res = 0;
    size_t i = 0;
    int n_arr[] =    {0,1,2,3,5,100,-1};
    int expected[] = {0,0,0,2,2,72,-1};
    size_t arr_size = (sizeof(n_arr)/sizeof(n_arr[0]));

    printf(YELLOW "\t-----TESTING Josephus FUNCTION: -----\n");
    
    for(i = 0; i < arr_size ; i++)
    {
    	res = JosephusCircularArray(n_arr[i]);
         
	    if (res != expected[i])
	    {
	        printf(RED"\n\tFAILED test %ld: expected %d, gor %d\n",i,expected[i], res);
	        return 0;
	    }

    
    }
    
    printf(GREEN"\n\t\tAll tests passed.\n\n");
    return 1;
}



