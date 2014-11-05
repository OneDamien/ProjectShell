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
void parse() {

}

int main (void) {

    //print a welcome message (under construction)
    printf("====================================================\n");
    printf("\tYou are now running MysteryShell!\n");
    printf("====================================================\n\n");

    //main loop
    while (1) {
        char input[BUFFER_SIZE];
        char *args[ARRAY_SIZE];

        // display a prompt
        printf("MysteryShell$ ");

        //read in the command line
        fgets(input, BUFFER_SIZE, stdin);
        printf(input); //test that line is read properly

        //**record command in history list here**

        //parse command line
        parse();

        //find the full pathname for the file

        // create process - execute command

        //parent waits until child finishes executing command
        exit(0);
        }   

    printf("\n");
    return 0;

}
