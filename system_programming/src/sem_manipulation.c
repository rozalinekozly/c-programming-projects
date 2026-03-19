#include <sys/ipc.h>	/*ftok(), key_t*/
#include <stddef.h>		/*NULL*/
#include <stdio.h>		/*FILE, fopen(), fclose(), fgets()*/
#include <errno.h>		/*EEXIST, errno*/
#include <sys/sem.h>	/*semget(), semctl(), IPC_CREAT, IPC_EXCL, struct sembuf*/
#include <string.h>		/*strcmp()*/
#include "utils.h"
TODO:
1- evald: add static to helper functions and make sure they end in IMP
2- evald: rename func's arguments to end with _
3- evald: rename return arguement to ret
4- modularity: sepperate handling operations into a new function (the while 1 loop)
5- code duplication: encapulate handling INCREMENT, INCREMENT_UNDO, DECREMENT, DECREMENT_UNDO into one function 
6- check: who's responsible for cleanup? 
-------------------------------------------------------------------------------

union semun {
    int              val;
    struct semid_ds *buf;
    unsigned short  *array;
};


typedef enum
{
    DECREMENT,
    DECREMENT_UNDO,
    INCREMENT,
    INCREMENT_UNDO,
    VIEW,
    EXIT,
    INVALID
} cmd_ty;

key_t ConstructKeyIMP(const char* name)
{
	key_t key;
	FILE* f;
	/*create file if not exists*/
	f = fopen(name, "a");
	EXIT_IF_BAD((NULL != f), 1, "fopen failed");
	fclose(f);
	/*construct a key*/
	/*create file with arv[1] if not exist open*/
	key = ftok(name, 1);
	EXIT_IF_BAD((-1 != key), 1, "ftok failed");
	/*return key*/
	return key;
}

int CreateConnectToSemIMP(key_t key)
{
	int semid = -1;
	union semun arg;
	
	/*create/connect to semaphore*/
	semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0666);
	/*if failed*/
		/*if with errno EEXIST*/
			/*connect process to semaphore*/
		/*otherwise*/
			/*exit, and print failure or whatever*/
	if(-1 == semid)
	{
		EXIT_IF_BAD ( EEXIST == errno, 1, "failed to connect/create");
		semid = semget(key, 1, 0666);
		EXIT_IF_BAD(-1 != semid, 1, "semget failed");
	}
	/*else (then it's the creator)*/
	else
	{
		/*initialize semaphore and set it's value to somevalue*/
		arg.val = 3;
		EXIT_IF_BAD(-1 != semctl(semid, 0, SETVAL, arg), 1, "semctl GETVAL failed");
	}
	return semid;
	/*return semid*/
}

cmd_ty IdentifyOperationIMP(int* number)
{
    /*declare line buffer*/
    char line_buffer[100];
    /*declare cmd char*/
    char cmd;
    /*declare undo_str buffer*/
    char undo_buffer[10];
    /*declare tokens_count int*/
    int tokens_count = 0;

    /*read whole line with fgets into line*/
    EXIT_IF_BAD(NULL != fgets(line_buffer, sizeof(line_buffer), stdin), 1, "failed fgets");
    /*parse line with sscanf into cmd, number, undo_str*/
    /*store result in tokens_count*/
    tokens_count = sscanf(line_buffer, "%c %d %s", &cmd, number, undo_buffer);
    
    /*switch on allcases of cmd*/
    /*if cmd == v*/
    if('V' == cmd)
    {
       /*return VIEW*/
        return VIEW;
    }
      
    /*if cmd == x*/
    if('X' == cmd)
    {
        /*return EXIT*/
        return EXIT;
     }
     
    /*if cmd == D*/
    if('D' == cmd)
    {
       /*if tokens_count == 2*/
       if(2 == tokens_count)
       {
       		/*return DECREMENT*/
       		return DECREMENT;
       }

        /*if tokens_count == 3 and undo_str == undo*/
        if(3 == tokens_count && (0 == strcmp(undo_buffer, "undo")))
    	{
    		/*return DECREMENT_UNDO*/
    		return DECREMENT_UNDO;
    	}
    	/*otherwise return invalid*/
    	return INVALID;
    }
    /*if cmd == I*/
    if('I' == cmd)
     {
     	   /*if tokens_count == 2*/
     	   if(2 == tokens_count)
            {
            	/*return INCREMENT*/
            	return INCREMENT;
            }
            /*if tokens_count == 3 and undo_str == undo*/
            if(3 == tokens_count && (0 == strcmp(undo_buffer, "undo")))
			{
				/*return INCREMENT_UNDO*/
				return INCREMENT_UNDO;
			}
			/*OYHERWISE RETURN INVALID*/
			return INVALID;
     }
    /*return INVALID*/
    return INVALID;
}

void View(int semid)
{
	int val = semctl(semid, 0 , GETVAL);
	EXIT_IF_BAD(-1 != val, 1, "semctl GETVAL failed");
	printf("semaphore value: %d\n", val);
}

void Exit(int semid)
{
	exit(0);
}

void Decrement(int semid, int number)
{
    struct sembuf op;
	/* first semaphore */
    op.sem_num = 0;
    /* decrement */          
    op.sem_op  = -number;
    /* no SEM_UNDO */    
    op.sem_flg = 0;          

    EXIT_IF_BAD(-1 != semop(semid, &op, 1), 1, "semop failed");
}

void DecrementUndo(int semid, int number)
{
    struct sembuf op;
	/* first semaphore */
    op.sem_num = 0;
    /* decrement */          
    op.sem_op  = -number;
    /*  SEM_UNDO */    
    op.sem_flg = SEM_UNDO;          

    EXIT_IF_BAD(-1 != semop(semid, &op, 1), 1, "semop failed");
}

void Increment(int semid, int number)
{
    struct sembuf op;
	/* first semaphore */
    op.sem_num = 0;
    /* increment */          
    op.sem_op  = number;
    /* no SEM_UNDO */    
    op.sem_flg = 0;          

    EXIT_IF_BAD(-1 != semop(semid, &op, 1), 1, "semop failed");
}

void IncrementUndo(int semid, int number)
{
    struct sembuf op;
	/* first semaphore */
    op.sem_num = 0;
    /* increment */          
    op.sem_op  = number;
    /*  SEM_UNDO */    
    op.sem_flg = SEM_UNDO;          

    EXIT_IF_BAD(-1 != semop(semid, &op, 1), 1, "semop failed");
}
int main(int argc, char* argv[])
{
	key_t key;
	int semid = -1;
	int number;
	cmd_ty cmd;
	
	struct sembuf op;
	/*validate argc value is 2*/
		/*if not exit*/
	EXIT_IF_BAD(2 == argc, 1, "wrong arguments");

	/*key = construct a key by calling ConstructKeyIMP*/
	key = ConstructKeyIMP(argv[1]);

	/*semid = create/connect to semaphore by calling CreateConnectToSemIMP*/
	semid = CreateConnectToSemIMP(key);

	/*loop while 1*/
	while(1)
	{
		/*identify user's request'*/
			/*cmd = IdentifyOperationIMP(&num)*/
			cmd = IdentifyOperationIMP(&number);
			
		/*switch cmd*/
		    /*case VIEW*/
		    if(VIEW == cmd)
		        /*print value*/
		        View(semid);
		    
		    /*case EXIT*/
		    else if(EXIT == cmd)
		    	/*exit*/
		    	Exit(semid);

		    
		    /*case DECREMENT*/
		    else if(DECREMENT == cmd)
		    {
		    	Decrement(semid, number);
		    }
		    
		    /*case DECREMENT_UNDO*/
		    else if(DECREMENT_UNDO == cmd)
		    {
		    	DecrementUndo(semid, number);
		    }
		        
			/*case INCREMENT*/
			else if(INCREMENT == cmd)
			{
				Increment(semid, number);
			}

			/*case INCREMENT_UNDO*/
			else if(INCREMENT_UNDO == cmd)
			{
				IncrementUndo(semid, number);
			}
			else
			{
				/*invalid*/
				printf("invalid operation ! try again\n");
			}
	}
	return 0;
}
