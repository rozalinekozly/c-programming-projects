/*
	make it generic, pass size of each array
	in checking acceptance, check all i till you get accept_states array size

*/

#include <stdio.h>
#include <stdlib.h>

#define ACCEPT		0
#define DO_NOT_ACCEPT	1

typedef enum 
{
	START = 0, 
	STARTS_WITH_ZERO = 1, 
	STARTS_WITH_ONE = 2, 
	STARTS_AND_ENDS_WITH_ZERO = 3,
	INVALID_INPUT = 4
}states; 

typedef struct fsm fsm_ty; 

/*typedef void (*transition_func)(fsm_ty* fsm, char input);*/

struct fsm
{
	states curr_state;
	states* accept_states;
	states (*transition_table)[5];
};

void Transition(fsm_ty* fsm, char input)
{
	fsm->curr_state = fsm->transition_table[input - '0'][fsm->curr_state];
}

fsm_ty* FSMCreate(states* accept_states, states (*transition_table)[5])
{
	int i = 0, j = 0;
	fsm_ty* fsm = (fsm_ty*)malloc(sizeof(fsm_ty)*sizeof(char));
	if(NULL == fsm)
	{
		return NULL;
	}
	
	fsm->curr_state = START;
	fsm->accept_states = accept_states;
	fsm->transition_table = transition_table;
	
	for(i = 0 ; i < 3 ; i++)
	{
		for(j = 0 ; j < 5 ; j++)
		{
			printf("%d\t", transition_table[i][j]);
		}
		printf("\n");
	
	}
	
	return fsm;
}


int CheckAceeptanceState(fsm_ty* fsm)
{
	size_t i = 0;
	if(fsm->curr_state != fsm->accept_states[i])
	{
		return DO_NOT_ACCEPT;
	}
	return ACCEPT;
}

void FSMRun(fsm_ty* fsm, char* input)
{

	/*intialize it to start*/
	fsm->curr_state = 0;
	while(*input != '\0')
	{
		Transition(fsm, *input);
		printf("input is %c then state is %d\n", *input, fsm->curr_state);
		++input;
	}
}

void PrintCurrentStateAcceptance(fsm_ty* fsm)
{
	int accept_or_nah = CheckAceeptanceState(fsm);
	
	if(accept_or_nah == ACCEPT)
			printf("ACCEPT\n");
	else
			printf("DENY\n");
}

void PrintInput(char* input)
{
	printf("input:%s\t", input);
}

void PrintRes(fsm_ty* fsm, char* input)
{
	PrintInput(input);
	PrintCurrentStateAcceptance(fsm);
}

int main()
{
	fsm_ty* fsm = NULL;
	states accept_states[] = {STARTS_AND_ENDS_WITH_ZERO};
	char* input1 = "011010";
	char* input2 = "111010";
	
	states transition_table [3][5] = 
	{
		{1,3,2,3,4},
		{2,1,2,1,4},
		{4,4,4,4,4}
	};
	/*add size*/
	fsm = FSMCreate(accept_states, transition_table);
	
	FSMRun(fsm, input1);
	PrintRes(fsm, input1);
	FSMRun(fsm, input2);
	PrintRes(fsm, input2);
	
	return 0;
}

