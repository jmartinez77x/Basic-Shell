//Programmer's name: Joe Martinez
//hash_table.c holds the functions to store and access the variables entered via simpleshell


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "variables.h"
#include "shell.h"

extern struct Table *t;

enum{bucketCount = 1024};

struct Node{
	char *key;
	char *value;
	struct Node *next;
};

struct Table{
	struct Node *array[bucketCount];
};


//CREATE TABLE
struct Table *Table_create(void){
	struct Table *t;
	t = (struct Table*)calloc(1, sizeof(struct Table));
	return t; 
}


//HASH FUNCTION
unsigned int hash(const char *x){
	int i; 
	unsigned int h = 0U;
	for(i = 0; x[i] != '\0'; i++){
		h = h * 65599 + (unsigned char)x[i];
	}
	return h % bucketCount;
}


//ADD TO HASH TABLE
void Table_add(char *key, char *value){
	printf("TEST Table_add key (before)   = %s\n", key);
	printf("TEST Table_add value (before) = %s\n", value);
	
	struct Node *p = (struct Node*)malloc(sizeof(struct Node));
	int h = hash(key);
	p->key = (char*)malloc(strlen(key)+1); //"CONST" BEFORE CHAR?
	strcpy(p->key, key);
	p->value = value;
	p->next = t->array[h];
	t->array[h] = p;
	
	printf("TEST Table_add key (after)   = %s\n", p->key);
	printf("TEST Table_add value (after) = %s\n", p->value);
}


//SEARCH HASH TABLE
char* Table_search(const char *key){
	char *tmpValue;
	int *intValue;

	struct Node *p;
	int h = hash(key);
	for(p = t->array[h]; p != NULL; p = p->next){
		if(strcmp(p->key, key) == 0){
			tmpValue = p->value;

			printf("TEST Table_search p->value  = %s\n", p->value);
			printf("TEST Table_search p->key = %s\n", p->key);
			return tmpValue;
		}
	}
	return "***Search returned null***";
}


//FREE LOCATION IN HASH TABLE
void Table_free(struct Table *t){
	struct Node *p;
	struct Node *nextp;
	int b;
	for(b = 0; b < bucketCount; b++){
		for(p = t->array[b]; p != NULL; p = nextp){
			nextp = p->next;
			free(p);
		}
	}
	free(t);
}


//PRINT THE ARRAY.............CURRENTLY NOT WORKING
void Table_print(struct Table *t){
	// char *buf;
	// int i = 0;
	// while(t->array[i] != NULL){
	// 	strcpy(buf, t->array[i]);
	// 	fputs(buf, stdout);
	// 	i++;
	// }
 }