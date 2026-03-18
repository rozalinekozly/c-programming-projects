
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
	/*create/connect to semaphore*/
	/*if failed*/
		/*if with errno EEXIST*/
			/*connect process to semaphore*/
		/*otherwise*/
			/*exit, and print failure or whatever*/
	/*else (then it's the creator)*/
		/*initialize semaphore and set it's value to somevalue*/
	/*return semid*/
}

cmd_ty IdentifyOperationIMP(int* number)
{
    /*declare line buffer*/
    /*declare cmd char*/
    /*declare undo_str buffer*/
    /*declare tokens_count int*/
    
    /*read whole line with fgets into line*/
    /*parse line with sscanf into cmd, number, undo_str*/
    /*store result in tokens_count*/
    
    /*if cmd == v*/
        /*return VIEW*/
    
    /*if cmd == x*/
        /*return EXIT*/
    
    /*if cmd == D*/
        /*if tokens_count == 2*/
            /*return DECREMENT*/
        /*if tokens_count == 3 and undo_str == undo*/
            /*return DECREMENT_UNDO*/
    
    /*if cmd == I*/
        /*if tokens_count == 2*/
            /*return INCREMENT*/
        /*if tokens_count == 3 and undo_str == undo*/
            /*return INCREMENT_UNDO*/
    
    /*return INVALID*/
}

int main(int argc, char* argv[])
{
	/*validate argc value is 2*/
		/*if not exit*/
	
	/*key = construct a key by calling ConstructKeyIMP*/
	
	/*semid = create/connect to semaphore by calling CreateConnectToSemIMP*/
		
	/*loop while 1*/
		/*identify user's request'*/
			/*cmd = IdentifyOperationIMP(&num)*/
		
		/*switch cmd*/
		    /*case VIEW*/
		        /*print value*/
		    
		    /*case EXIT*/
		        /*cleanup*/
		        /*exit*/
		    
		    /*case DECREMENT*/
		    	/*set sem_flg = 0 (no undo)*/
		        /*set sem_op to be -number*/
		        /*call semop with op*/
		        
		    /*case DECREMENT_UNDO*/
		    	/*set sem_flg to be SEM_UNDO*/
				/*set sem_op to be -number*/
		        /*call semop with op*/
		        
			/*case INCREMENT*/
				/*set sem_flg = 0*/
				/*set sem_op to be number*/
				/*call semop with op*/

			/*case INCREMENT_UNDO*/
				/*set sem_flg = SEM_UNDO*/
				/*set sem_op to be number*/
				/*call semop with op*/
	}
