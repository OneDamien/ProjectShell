//shellmain.c
/*
Basic core of the the shell

Status:
Displays the welcome message,
then the prompt,
allows user to type in a command and reads it,
parses the command into an array of args,
forks a child and calls execvp and passes it
the arguements which it attempts to compute,
exits on the exit command
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include <string.h>
#include <dirent.h>
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>
#define BUFFER_SIZE 1200
#define ARRAY_SIZE 100
<<<<<<< HEAD
/*
=======

static char* args[BUFFER_SIZE];
pid_t pid;

>>>>>>> 2120013932c07f201f365738fef31e32289b17bd
char getche(){
    fflush(stdout);
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&buf,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    if(buf != '\t')
    printf("%c",buf);
    return buf;
 }
*/

//Helper functions
void parse(char *input, char** args) {
   
        while(*input != '\0') //while the input line is not empty
        {
            while(isspace(*input)) //take care of whitespace
                *input++ = '\0';
            *args++ = input;    //arg position
            while(!isspace(*input) && *input != '\0')
                input++;    //move to next arg
        }

        *args = (char *) '\0';  //end of command arguements
}

void tabComplete(char *input){
	char *temp = strchr (input, ' ');
        char *f;
        if (temp!=NULL)
        {
             char *s = strrchr (input, ' ');
             f = strdup(s+1);
        }
        else
             f = strdup(input);
        int wordlength = strlen(f);
        DIR           *d;
	struct dirent *dir;
  	d = opendir(".");
  	if (d)
  	{
    	    while ((dir = readdir(d)) != NULL)
    	    {
      		if(strncmp(f, dir->d_name, wordlength)==0)
		{
		    printf("%s", dir->d_name + wordlength);
		    strcat(input,dir->d_name + wordlength);
	    	}
	    }
            closedir(d);
         }      
}
/*
void getInput(char *input){
	int i = 0;
	//char inputChar=getche();
	while(inputChar!='\n'){
		if(inputChar==0) // Special Character
		{
			
			inputChar=getch();
			if(inputChar==ARROW_UP)
				Display History (Line++)
			else(inputChar==ARROW_DOWN)
				Display History (Line--)
			
		}
		else
		{
			if (inputChar == '\t')
	                tabComplete(input);
			else
			{
				input[i]=inputChar;
				i++;
			}
			inputChar=getche();
		}
	}
	input[i]='\n';
}
*/
void recordHistory(char *input){
	FILE * pHistory = fopen("shellhistory.txt", "a");
	if(pHistory == NULL)
		printf("Unable to open history");
	else
		fprintf(pHistory, "%s",input);
	fclose(pHistory);
}

/*
void displayHistory(int line){
	
}
*/

static int run(char *cmd, int input, int first, int last);
static int command(int input, int first, int last);
static int n = 0; //calls to 'command'

int main (void) {

<<<<<<< HEAD
    char *input;
    char *args[ARRAY_SIZE];
    pid_t pid;
=======
    char input[BUFFER_SIZE];
    //char *args[ARRAY_SIZE];
>>>>>>> 2120013932c07f201f365738fef31e32289b17bd
    int i;
    //Clear Screen
    system("clear");
    //print a welcome message (under construction)
    printf("====================================================\n");
    printf("\tYou are now running MysteryShell!\n");
    printf("\tType \"exit\" to quit.\n");
    printf("====================================================\n\n");
    //main loop
<<<<<<< HEAD
    rl_bind_key('\t', rl_complete);
 
    while(1){
        input = readline("MysteryShell$ ");
 
        // Check for EOF.
        if (!input)
            break;
 
        // Add input to history.
        add_history(input);
 
        // Do stuff...
 	//parse command line
	parse(input, args);
=======
    while (1) {
    	for(i=0; i<BUFFER_SIZE;i++)
    	input[i]= '\0';
        // display a prompt
        printf("MysteryShell$ ");
        //read in the command line
        //fgets(input, BUFFER_SIZE, stdin);

   	getInput(input);
        
        //**record command in history list here**
	    recordHistory(input);
        
        
        //parse command line
        parse(input, args);
        
>>>>>>> 2120013932c07f201f365738fef31e32289b17bd
        //exit if "exit" is typed in as command
        if(strcmp(input, "exit") == 0)
            exit(0);

        //find the full pathname for the file

        // create process - execute command
        char* cmd = input;
        char* next = strchr(cmd, '|');  //find first |
        int st = 0;
        int first = 1;

        while (next != NULL)
        {
            *next = '\0';
            st = run(cmd, st, first, 0);

            cmd = next + 1;
            next = strchr(cmd, '|');
            first = 0;
        }
        st = run(cmd, input, first, 1);
        
        

        /*
        pid = fork();  
        if (pid)
            pid = wait(NULL); //parent waits for child
        else
        {
            if(execvp(args[0],args))
                exit(1);
        }
<<<<<<< HEAD
	free(input);
      
    
	}
=======
        */

    }
>>>>>>> 2120013932c07f201f365738fef31e32289b17bd
    printf("\n");
    return 0;

}


static int run(char *cmd, int input, int first, int last)
{
    if(args[0] != NULL)
    {
        n += 1;
        return command(input, first, last);
    }
    return 0;
}


static int command(int input, int first, int last)
{
    int pipeline[2];
    pipe(pipeline);
    pid = fork();

    if(pid == 0)
    {
        if(first == 1 && last == 0 && input == 0)
            dup2( pipeline[1], STDOUT_FILENO );
        else if(first == 0 && last == 0 && input != 0)
        {
            dup2(input, STDIN_FILENO);
            dup2(pipeline[1], STDOUT_FILENO);
        }
        else
            dup2(input, STDIN_FILENO);
        if (execvp(args[0], args) == -1)
            exit(1);  //child fails
    }

    if(input != 0)
        close(input);

    close(pipeline[0]);
    if(last == 1)
        close(pipeline[0]);

    return pipeline[0];
}

