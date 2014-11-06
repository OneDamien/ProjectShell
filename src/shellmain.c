//shellmain.c
/*
Basic core of the the shell

Status:
Displays the welcome message, then the prompt,
allows user to type in a command and reads it, then exits
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
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

int main (void) {

    char input[BUFFER_SIZE];
    char *args[ARRAY_SIZE];

    //print a welcome message (under construction)
    printf("====================================================\n");
    printf("\tYou are now running MysteryShell!\n");
    printf("====================================================\n\n");

    //main loop
    while (1) {
        // display a prompt
        printf("MysteryShell$ ");

        //read in the command line
        fgets(input, BUFFER_SIZE, stdin);

        //**record command in history list here**

        //parse command line
        parse(input, args);
  
        //find the full pathname for the file

        // create process - execute command

        //parent waits until child finishes executing command
        exit(0);
        }   

    printf("\n");
    return 0;

}
