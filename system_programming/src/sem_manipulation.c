
typedef enum
{
    DECREMENT,
    DECREMENT_UNDO,
    INCREMENT,
    INCREMENT_UNDO,
    VIEW,
    EXIT,
    INVALID
} command_t;

key_t ConstructKeyIMP(const char* name)
{
	/*construct a key*/
	/*create file with arv[1] if not exist open*/
	/*get key file is argv[1]*/
	/*return key*/
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
int main(int argc, char* argv[])
{
	/*validate argc value is 2*/
		/*if not exit*/
	
	/*key = construct a key by calling ConstructKeyIMP*/
	
	/*semid = create/connect to semaphore by calling CreateConnectToSemIMP*/
		
	/*loop while 1*/
		/*read whole line with fgets*/
		/*parse with sscanf, cmd, number, undo_str*/
		/*check how many tokens returned store it in tokens_count var*/
		
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
