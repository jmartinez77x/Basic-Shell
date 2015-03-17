/***************************************************
	FileName: parser.h
	Purpose: Define function prototypes to be used in parser.c
	Description: Contains all the functions that make up the object file
        for parser.
     Once the object files are created these prototypes are all that we need.
***************************************************/
/* C Macros to create definitions for maximum number of arguments and things
such as how to know when to use pipe */
#ifndef PARSER_H
#define PARSER_H

#define MAXINPUTLINE 10240
#define MAXARGS 1024
#define PARSE_NOPIPE -1        /* Default is no pipe */
#define PARSE_USEPIPE -2    /* Using pipes, but FD not yet known */


void parse(char *cmdline);
void parse_cmd(char *cmdpart);
void splitcmd(char *cmdpart, char *args[]);
char *expandtilde(char *str);
void freeargs(char *args[]);
void argsdelete(char *args[]);
char *parseredir(char oper, char *args[]);
int checkbackground(char *cmdline);
char *gethomedir(void);
char *getuserhomedir(char *user);

#endif
