//Programmer's name: Joe Martinez
//Variable.c contains functions to handle variables entered in simpleshell

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash_table.h"
#include "shell.h"

extern struct Table *t;

//IF INPUT HAS "READ" (TO SET A VARIABLE)
void readCMD(char *input){
	char varName[16];
	char varValue[16];
	char *readCMD_buf;

	readCMD_buf = strtok(input, " ");
	while(readCMD_buf != NULL){
		strcpy(varName, readCMD_buf);			//EXTRACT VARIABLE NAME FROM INPUT
		readCMD_buf = strtok(NULL, " ");
	}
	fgets(varValue, sizeof(input), stdin);		//GET VALUE FOR VARIABLE VIA FGETS

	printf("TEST readCMD varName = %s\n", varName);
	printf("TEST readCMD varValue = %s\n", varValue);

	Table_add(varName, varValue);				//ADD TO TABLE
}


//IF INPUT HAS AN "=" (TO SET A VARIABLE)
void equalCMD(char *input){
    char varName[16];
    char varValue[16];

    char *equalCMD_buf;
    equalCMD_buf = strtok(input, "=");	
    strcpy(varName, equalCMD_buf);				//EXTRACT VARIABLE NAME FROM INPUT
    while(equalCMD_buf != NULL){
    	strcpy(varValue, equalCMD_buf);			//EXTRACT VARIABLE VALUE FROM INPUT
    	equalCMD_buf = strtok(NULL, "\n");
    }

    printf("TEST equalCMD varName = %s\n", varName);
    printf("TEST equalCMD varValue = %s\n", varValue);
    
    Table_add(varName, varValue);				//ADD TO TABLE
}


//IF INPUT HAS AN "$" (TO CALL A VARIABLE)
const char* callVarCMD(char *input){
	char varName[16];
	char *buf;
	buf = strtok(input, " ");
	while(buf != NULL){
		if(strncmp(buf, "$", 1) == 0){
			strcpy(varName, buf+1);				//EXTRACT VARIABLE NAME FROM INPUT
		}
		buf = strtok(NULL, " ");
	}


	//TESTING STUFF
 	// printf("varName = %s\n", varName);
 	// char nname[8];
 	// strcpy(nname, varName);
 	// char vvalue[8];
 	// strcpy(vvalue, varName);
 	// Table_add(nname, vvalue);                                    				
 	// printf("\nTEST callVarCMD received (nname) = %s\n", Table_search(nname));
	//END TESTING STUFF


	printf("callVarCMD received (varName) = %s\n", Table_search(varName));
	return varName;
}
