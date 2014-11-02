//shellmain.c
/*
Basic core of the the shell

Status:
Displays the welcome message, then the prompt, then exits
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

//Helper functions
char* readCommandLine() {
    char* cmdLine;
    cmdLine = "test";
    return cmdLine;
}

void parse(char* cmdLine) {

}

int main (void) {

    //print a welcome message (under construction)
    printf("====================================================\n");
    printf("\tYou are now running MysteryShell!\n");
    printf("====================================================\n\n");

    char shellName[14] = "MysteryShell$ ";

    //main loop
    while (1) {
        char *cmdLine;

        // display a prompt
        printf(shellName);

        //read in the command line
        cmdLine = readCommandLine();

        //**record command in history list here**

        //parse command line
        parse(cmdLine);

        //find the full pathname for the file

        // create process to execute command

        //parent waits until child finishes executing command
        exit(0);
        }   

    printf("\n");
    return 0;

}
