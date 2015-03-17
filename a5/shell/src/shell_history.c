//Programmer's name: Joe Martinez
//shell_history.c holds the functions to deal with history file of the simple shell


#include <stdio.h>
#include <string.h>

#include "shell.h"


void headerTest(int j){
	printf("%d\n", j);
	printf("%s\n", "Test successful");
}


void recHistory(char input, int i /*FILE *shistory*/){
	char c[16];
    sprintf(c,"%d ", i);    //C IS A CHAR STRING WITH I AS A NUMERICAL MARK
    i += 1;
    //fputs(c, shistory);     //PUTS C INTO .SIMPLESHELL_HISTORY
    //fputs(input, shistory); //PUTS INPUT (THE COMMAND) INTO .SIMPLESHELL_HISTORY
}