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
#include "conio.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include <string.h>
#define BUFFER_SIZE 1200
#define ARRAY_SIZE 100


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

void getInput(char *input){
	int i = 0;
	char inputChar=getche();
	while(inputChar!='\n'){
		if(inputChar==0) // Special Character
		{
			/*
			inputChar=getch();
			if(inputChar==ARROW_UP)
				Display History (Line++)
			else(inputChar==ARROW_DOWN)
				Display History (Line--)
			*/
		}
		else
		{
			input[i]=inputChar;
			i++;
			inputChar=getche();
		}
	input[i]='\n';
	}
}

void recordHistory(char *input){
	FILE * pHistory = fopen("shellhistory.txt", "a");
	if(pHistory == NULL)
		printf("Unable to open history");
	else
		fprintf(pHistory, input);
	fclose(pHistory);
}

int main (void) {

    char input[BUFFER_SIZE];
    char *args[ARRAY_SIZE];
    pid_t pid;
    //Clear Screen
    system("clear");
    //print a welcome message (under construction)
    printf("====================================================\n");
    printf("\tYou are now running MysteryShell!\n");
    printf("\tType \"exit\" to quit.\n");
    printf("====================================================\n\n");
    //main loop
    while (1) {
        // display a prompt
        printf("MysteryShell$ ");
        //read in the command line
        fgets(input, BUFFER_SIZE, stdin);

	    //getInput(input);
        
        //**record command in history list here**
	    recordHistory(input);
        
        //parse command line
        parse(input, args);
        //exit if "exit" is typed in as command
        if(strcmp(args[0], "exit") == 0)
            exit(0);
        
        //find the full pathname for the file

        // create process - execute command
        pid = fork();  
        if (pid)
            pid = wait(NULL); //parent waits for child
        else
        {
            if(execvp(args[0],args))
                exit(1);
        }
      
    }
    printf("\n");
    return 0;

}
