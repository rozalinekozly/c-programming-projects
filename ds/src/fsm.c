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

typedef void (*transition_func)(fsm_ty* fsm, char input);

struct fsm
{
	states curr_state;
	states* accept_states;
	transition_func transition_func;
};

void Transition(fsm_ty* fsm, char input)
{
	states curr_state = fsm->curr_state;
	if(input == '0')
	{
		if(curr_state == START)
			curr_state = STARTS_WITH_ZERO;
			
		else if(curr_state == STARTS_WITH_ZERO || curr_state == STARTS_AND_ENDS_WITH_ZERO) 
			curr_state = STARTS_AND_ENDS_WITH_ZERO;
			
		else if(curr_state == STARTS_WITH_ONE)
			curr_state = STARTS_WITH_ONE;
			
		else 
			curr_state = INVALID_INPUT;
	}
	else if(input == '1')
	{
		if(curr_state == START)
			curr_state = STARTS_WITH_ONE;
			
		else if(curr_state == STARTS_WITH_ZERO)
			curr_state = STARTS_WITH_ZERO;
			
		else if(curr_state == STARTS_WITH_ONE)
			curr_state = STARTS_WITH_ONE;
		
		else if(curr_state == STARTS_AND_ENDS_WITH_ZERO)
			curr_state = STARTS_WITH_ZERO;
			
		else
			curr_state = INVALID_INPUT;
	}
	else
	{
		curr_state = INVALID_INPUT;
	}
	
	fsm->curr_state = curr_state;
}

fsm_ty* FSMCreate(states* accept_states, transition_func transition_func)
{
	fsm_ty* fsm = (fsm_ty*)malloc(sizeof(fsm_ty)*sizeof(char));
	if(NULL == fsm)
	{
		return NULL;
	}
	
	fsm->curr_state = START;
	fsm->accept_states = accept_states;
	fsm->transition_func = transition_func;
	
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
	/*add size*/
	fsm = FSMCreate(accept_states, Transition);
	
	FSMRun(fsm, input1);
	PrintRes(fsm, input1);
	FSMRun(fsm, input2);
	PrintRes(fsm, input2);
	
	return 0;
}

