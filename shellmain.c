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

int main (int argc, char *argv[]) {

//print a welcome message (under construction)
printf("====================================================\n");
printf("\tYou are now running MysteryShell!\n");
printf("====================================================\n\n");

char shellName[14] = "MysteryShell$ ";

while (1) {

// display a prompt
printf(shellName);

//read in the command line

//parse command line

//check for exit
exit(0);

//if no exit, execute command(s)

}

return 0;

}
