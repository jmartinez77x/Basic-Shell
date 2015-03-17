/***************************************************
  Programmer's name: Joe Martinez
  FileName: sshell.c
  Purpose: Execute all unix shell commands through the executable file.
  Description: Ties in all the individual pieces of the shell utility
        that we are creating.
***************************************************/

#include "parser.h"
#include "shell.h"
#include "hash_table.h"
#include "variables.h"
#include "shell_history.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>   
#include <unistd.h>  
#include <signal.h>

struct Table *t;    //CREATE TABLE

int main(void) {
  char input[MAXINPUTLINE];
  signal_c_init();

  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("Welcome to the sample shell!  You may enter commands here, one\n");
  printf("per line.  When you're finished, press Ctrl+D on a line by\n");
  printf("itself.  I understand basic commands and arguments separated by\n");
  printf("spaces, redirection with < and >, up to two commands joined\n");
  printf("by a pipe, tilde expansion, and background commands with &.\n\n"); 
  
  printf("\njmsh$ ");


  /**********************BEGIN MEAT OF PROGRAM********************************/

  t = Table_create();   //CREATING TABLE

  FILE *shistory;
  shistory = fopen(".simpleshell_history", "w"); //CREATE HISTORY FILE TO WRITE
  int i = 1;                                     //NUMERICAL MARKER FOR HISTORY FILE

  while (fgets(input, sizeof(input), stdin)) {   //KEEPS IT RUNNING, FUNCTIONS WILL BE HERE 
   
    //RECORD EACH COMMAND INTO SIMPLESHELL_HISTORY
    //recHistory(input, i, shistory);
    char c[16];
    sprintf(c,"%d ", i);    //C IS A CHAR STRING WITH I AS A NUMERICAL MARK
    i += 1;
    fputs(c, shistory);     //PUTS C INTO .SIMPLESHELL_HISTORY
    fputs(input, shistory); //PUTS INPUT (THE COMMAND) INTO .SIMPLESHELL_HISTORY
    //END RECORDING


    //SHOW HISTORY FROM SIMPLESHELL_HISTORY
    char h[16];                                      //BUFFER FOR READING HISTORY FILE
    char hstr[16] = "history\n";
    if(strcmp(input,hstr) == 0){                     //CHECK IF INPUT IS THE HISTORY COMMAND
      fclose(shistory);
      shistory = fopen(".simpleshell_history", "r"); //OPEN FILE TO READ
      while(fgets(h,16,shistory) !=  NULL){          //GETS INPUT FROM HISTORY FILE
        fputs(h, stdout);                            //OUTPUTS HISTORY TO CONSOLE
      }
      fclose(shistory);
      shistory = fopen(".simpleshell_history", "a"); //REOPEN FILE TO APPEND
    }//END SHOW HISTORY


    //CMD BEGINS WITH "!"
    if(strncmp(input, "!",1) == 0){                  //IF FIRST CHAR IS "!"
      fclose(shistory);
      shistory = fopen(".simpleshell_history", "r"); //OPEN HISTORY FILE TO READ
      
      char d[16];                                    //SEARCH HISTORY FILE BUFFER
      
      while(fgets(d,16,shistory) !=  NULL){          //FIND FIRST INSTANCE OF NUMBER(FROM !NUMBER COMMAND)
        
        // !NUMBER
        char *delim; 
        delim = strtok(input, "!");   //GET STRING AFTER "!" (THE ACUTAL COMMAND)
        if(strncmp(d, delim,1) == 0){ //IF BUFFER == COMMAND STRING 
          strcpy(input,d+2);          //INPUT == COMMAND STRING FROM READ FILE
        }
        //END !NUMBER


        // !STRING
        //COMPARES THE CMD OF EACH LINE IN HISOTRY FILE AND SETS THE LAST ONE TO INPUT
        if(strncmp(d+2,delim,sizeof(delim)/2) == 0){ 
          strcpy(input,d+2);
        }
        //END !STRING


        //CMD = !!
        if(strncmp(input,"!!",2) == 0){ //IF INPUT == "!!"
          char l[16];
          int k = i-2;
          sprintf(l,"%d ",k);           //MAKE STRING OF I-2 WHICH IS LAST EXECUTED CMD
          if(strncmp(d,l,1) == 0){
            strcpy(input,d+2);          //SET INPUT TO THAT CMD
          } 
        }
        //END CMD == !!


      }//END SEARCHING HISTORY FILE TO RECALL CMD

      fclose(shistory);
      shistory = fopen(".simpleshell_history", "a"); //OPEN HISTORY FILE TO APPNED FOR NEW CMD(S)

    }//END CMD BEGINS WITH "!"


    //BEGIN DEALING WITH VARIABLES
    if(strncmp(input, "read", 4) == 0){     //IF INPUT HAS "READ" (TO SET A VARIABLE)
      readCMD(input);
    }

    if(strchr(input, '=') != NULL){         //IF INPUT HAS AN "=" (TO SET A VARIABLE)   
      equalCMD(input);
    }

    if(strchr(input, '$') != NULL){         //IF INPUT HAS AN "$" (TO CALL A VARIABLE)
      callVarCMD(input);
    }
    //END DEALING WITH VARIABLES


    //BEGIN KEY LOGGING
    if(strncmp(input, "key_logger_off", 14) == 0){
      printf("%s\n", "Stopped key logging");
      //append temp file to permanent one
      //atexit(do this same command to save key log to file)
      printf("%s\n", "Would you like to append temporary file to permanent file?");
      printf("%s\n", "Enter Y/N");
      char ans[4];
      fgets(ans, sizeof(ans), stdin);
      if(strcmp(ans, "y")==0 | strcmp(ans, "Y")==0){
        //append file
        printf("%s\n", "File appended");
      }
      else{
        printf("%s\n", "File not appended");
        //exit(1);
      }
    }


    if(strncmp(input, "key_logger", 10) == 0){
      printf("%s\n", "Started key Logging");

      int status;
      int pid;
      int p[2];

      if(pipe(p) == -1){
        printf("%s\n", "Pipe failed");
        exit(1);
      }

      pid = fork();
      if(pid == -1){
        printf("%s\n", "Fork failed");
        exit(2);
      }
      if(pid == 0){ //CHILD PROCESS
        close(p[1]);
        //dup2(p[0], 0);
        close(p[0]);
        printf("%s\n", "In child process");
        execl("record", "record", input, NULL);    //WILL SUCCESFULY EXECUTE ./RECORD
        write(p[1], input, sizeof(input));
        exit(3);
      }
      else{ //PARENT PROCESS
        close(p[0]);
        dup2(p[1],1);
        close(p[1]);
        //printf("%s\n", "fork error");
        //write()
        wait(&status);
        exit(4);
      }
    }

    //reading for ctrl-c and ctrl-d
    //END KEY LOGGING


    //SENDING INPUT TO BE EXECUTED
    stripcrlf(input);
    parse(input);
    printf("\njmsh$ ");
    //END SEND INPUT
  }
  fclose(shistory); //CLOSE .SIMPLESHELL_HISTORY (REFRESHED WHEN SHELL IS REOPENED)
  return 0;
}