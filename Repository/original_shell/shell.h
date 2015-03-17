/***************************************************
	FileName: shell.h
	Purpose: Provide protypes for our shell functionality
	Description: File contains all the necessary prototypes and macros
        to be used in the implementation file, "shutil.c"
***************************************************/

#ifndef SHELL_H
#define SHELL_H

int checkbackground(char *cmdline);
void stripcrlf(char *temp);
char *gethomedir(void);
char *getuserhomedir(char *user);
void signal_c_init(void);
void waitchildren(int signum);
void striptrailingchar(char *temp, char tc);

#endif
