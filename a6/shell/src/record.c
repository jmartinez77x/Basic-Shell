//Programmer's name: Joe Martinez
//record.c records input to key_logger when prompted 

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h>
#include <assert.h>
#include <signal.h>
#include "shell.h"


void offHandler(int sig){
	signal(SIGINT, offHandler);
	printf("%s\n", "Key logging is now off"); 
	printf("%s\n", "Would you like to append temporary record file to permanent record file? ");
	printf("%s\n", "Enter Y/N");
	char ans[4];
	//Need to get input from pipe...
	//fgets(ans, sizeof(ans), stdin);
	if(strcmp(ans, "y")==0 | strcmp(ans, "Y")==0){
		//append file
		printf("%s\n", "File appended");
	}
	else{
		//exit(1);
		printf("%s\n", "File not appended");
	}
	//pause();         
}


int main(int argc, char *argv[]){
	//signal(SIGINT, offHandler);
    char recBuf[256];
    int ret;
    for(;;){
    	ret = read(0, recBuf, 256);
    	if(ret < 256){
    		recBuf[ret] = '\0';
    		//printf("%s\n", recBuf);
    	}
    	//printf("%s\n", recBuf);

    	record(recBuf);
	}
	//printf("%s\n", argv[3]);
	//record("");
	return 0;	
}


void record(char *Buf){
	FILE *temp_logger;
	temp_logger = fopen(".temp_logger", "a");

	printf("%s\n", "Line recorded...");

	time_t time_stamp;
	time(&time_stamp);
	fputs(ctime(&time_stamp), temp_logger);
	fputs("   ", temp_logger);
	fputs(Buf,   temp_logger);
	fputs("\n",  temp_logger);

	fclose(temp_logger);
}