typedef enum
{
	NOT_INTERNAL_CMD = 0,
	EXIT = 1
}internal_cmd_ty;

/* return value : 0 = not an internal command
				  other value = relevant internal command number*/
int IsInternalCmd(command);

void RunInternal(internal_cmd);

int main()
{
	int internal_cmd = NOT_INTERNAL_CMD;
    /* while 1 */
        /* print prefix <username>@<machine_name>:<current_dir>$ */
        /* read input and split it into words */
        /* if input is an internal command*/
        internal_cmd = IsInternalCmd(command);
        if(internal_cmd)
        {
        	/*call relevant function*/
        	RunInternal(internal_cmd);
        }
        /*else */
			/* hand the command to the OS to run and save return status*/
			/*if running command failed*/
				/*print to stderr proper error massage*/
    }
    return 0;
}

int IsInternalCmd(command)
{
	/*if command is one of internal_cmd_ty*/
		/*return command's code*/
	/*else*/
		/*return NOT_INTERNAL_CMD */
}

void RunInternal(internal_cmd)
{
	/*run internal command according to the passed code*/
}

