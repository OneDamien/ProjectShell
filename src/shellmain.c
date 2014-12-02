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

static char* args[BUFFER_SIZE];
pid_t pid;
int argCount = 0;

/*
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

void parse(char *input, char** args) {
    
    argCount = 0 ;
   
    while(*input != '\0') //while the input line is not empty
        {
            while(isspace(*input)) //take care of whitespace
                *input++ = '\0';
            *args++ = input;    //arg position
            
            argCount++;

            while(!isspace(*input) && *input != '\0')
                input++;    //move to next arg
        }

    *args = (char *) '\0';  //end of command arguements
    
    //subtract one to get ctual count.
    argCount--;  
}

void tabComplete(char *input){
	char *temp = strchr (input, ' ');
        char *f;
        int i,x=0;
        char y[50][BUFFER_SIZE];
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
		    strcpy(y[x],dir->d_name);
		    x++;
	    	}
	    }
	    if(x==1)
	    {
	    	printf("%s", y[0] + wordlength);
	    	strcat(input,y[0] + wordlength);
	    }
	    else if(x>1)
	    {
	    	printf("\nError: Multiple files");
	    	for(i=0; i<=x; i++)
	    	{
	    		printf("%s      ", y[i]);
	    	}
	    	printf("\nMysteryShell$ %s", input);
	    }
  	}
  	closedir(d);      
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

//redirection code
void setupRedirct(char *args[])
{
    int i=0;
        
    char *outputFileName = "", *inputFileName="";
    FILE *fp;
    
    
    //scan for redirection chacarcters ">" or "<"
    for(i=0 ; i<=argCount-1 ; i++)
    {
        if( strcmp(args[i],">") == 0)
        {
            outputFileName = args[i+1];
            // remove following argments
            args[i] =   NULL;
            args[i+1] = NULL;
            break;
        }

        if( strcmp(args[i],"<") == 0)
        {
            inputFileName = args[i+1];
            
            // remove following argments
            args[i] =   NULL;
            args[i+1] = NULL;
            break;
        }   
    }
    
    
    if( strcmp(outputFileName,"") != 0)
        {
            fp = fopen(outputFileName, "w+");
            dup2(fileno(fp), 1);
        }
    
    if( strcmp(inputFileName,"") != 0)
        {
            fp = fopen(inputFileName, "r");
            dup2(fileno(fp), 0);
        }

}

static int run(char *cmd, int st, int first, int last);
static int command(int st, int first, int last);
static int n = 0; //calls to 'command'

int main (void) {
    char *input;
    char *args[ARRAY_SIZE];
    char add[50];
    char commit[200];
    char push[50];
    pid_t pid;
   // char input[BUFFER_SIZE];
    //char *args[ARRAY_SIZE];
    int i;
    //Clear Screen
    system("clear");
    //print a welcome message (under construction)
    printf("====================================================\n");
    printf("\tYou are now running MysteryShell!\n");
    printf("\tType \"exit\" to quit.\n");
    printf("====================================================\n\n");
    //main loop
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
	strcpy(add,"git add ");
	strcpy(commit, "git commit -m \"Quick Commit Changes\"");
	strcpy(push, "git push");
	strcat(add, args[1]);
	
        //exit if "exit" is typed in as command
        if(strcmp(input, "exit") == 0)
            exit(0);
	if(strcmp(args[0], "cd") == 0)
	    chdir(args[1]);
	if(strcmp(args[0], "acp") == 0)
	{
	    system(add);
	    system(commit);
	    system(push);
	}
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
        st = run(cmd, st, first, 1);
        pid = fork();  
        if (pid)
            pid = wait(NULL); //parent waits for child
        else
        {
            
            // apply redirction if redirection symbole ">" or "<" exist
            setupRedirct(args);	

            if(execvp(*args,args))
                exit(1);
        }
	free(input);
	}
    printf("\n");
    return 0;

}


static int run(char *cmd, int st, int first, int last)
{
    if(args[0] != NULL)
    {
        n += 1;
        return command(st, first, last);
    }
    return 0;
}


static int command(int st, int first, int last)
{
    int pipeline[2];
    pipe(pipeline);
    pid = fork();

    if(pid == 0)
    {
        if(first == 1 && last == 0 && st == 0)
            dup2( pipeline[1], STDOUT_FILENO );
        else if(first == 0 && last == 0 && st != 0)
        {
            dup2(st, STDIN_FILENO);
            dup2(pipeline[1], STDOUT_FILENO);
        }
        else
            dup2(st, STDIN_FILENO);
        if (execvp(args[0], args) == -1)
            exit(1);  //child fails
    }

    if(st != 0)
        close(st);

    close(pipeline[0]);
    if(last == 1)
        close(pipeline[0]);

    return pipeline[0];
}

