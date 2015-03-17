/***************************************************
	Programmer's name: Joe Martinez
	FileName: sshell.c
	Purpose: Execute all unix shell commands through the executable file.
	Description: Ties in all the individual pieces of the shell utility
        that we are creating.
***************************************************/
#include "parser.h"
#include "shell.h"
#include <stdio.h>
#include <string.h>
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

  FILE *shistory;
  shistory = fopen(".simpleshell_history", "w");
  int i = 1;

  while (fgets(input, sizeof(input), stdin)) {
   
    //record each command into simpleshell_history
    char c[16];
    sprintf(c,"%d ", i);    //c is a char string with i as a numerical marker
    i += 1;
    fputs(c, shistory);     //puts c into .simpleshell_history
    fputs(input, shistory); //puts input (the command) into .simpleshell_history
    //end recording


    //show history from simpleshell_history
    char h[16];                   //buffer for reading history file
    char hstr[16] = "history\n";
    if(strcmp(input,hstr) == 0){  //check if input is the history command
      fclose(shistory);
      shistory = fopen(".simpleshell_history", "r"); //open file to read
      while(fgets(h,16,shistory) !=  NULL){          //gets input from history file
        fputs(h, stdout);         //outputs history to console
      }
      fclose(shistory);
      shistory = fopen(".simpleshell_history", "a"); //reopen file to append
    }//end show history


    //cmd begins with "!"
    if(strncmp(input, "!",1) == 0){ //if first char is "!"
      fclose(shistory);
      shistory = fopen(".simpleshell_history", "r"); //open history file to read
      
      char d[16]; //search history file buffer
      
      while(fgets(d,16,shistory) !=  NULL){ //find first instance of number (from !number command)
        
        // !number
        char *delim; 
        delim = strtok(input, "!");   //get string after "!" (command string)
        if(strncmp(d, delim,1) == 0){ //if buffer == command string
          strcpy(input,d+2);          //input == command string from read file 
        }
        //end !number


        // !string
        //compares the cmd of each line in history file and sets the last one to input
        if(strncmp(d+2,delim,sizeof(delim)/2) == 0){ 
          strcpy(input,d+2);
        }
        //end !string


        // cmd = !!
        if(strncmp(input,"!!",2) == 0){ //if input == "!!"
          char l[16];
          int k = i-2;
          sprintf(l,"%d ",k);           //make string of i-2 which is last executed cmd
          if(strncmp(d,l,1) == 0){
            strcpy(input,d+2);          //set input to that cmd
          }    
        }
        //end cmd = !!
      }//end while loop (end of history file)

      fclose(shistory);
      shistory = fopen(".simpleshell_history", "a"); //ophen history file to append

    } //end cmd begins with "!"

    stripcrlf(input);
    parse(input);
    printf("\njmsh$ ");
  }
  fclose(shistory);
  return 0;
}
