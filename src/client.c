/**Author: Moiz Naveed
 *10/20/2017
 * CIS 2520 Assignment 2
 * client.c*/
 
#include <stdio.h>
#include "linkedlistAPI.h"
#include "client.h"

/**Function to print the Pq struct
 * Didn't want to change the API definitions so
 * the print function in the API calls this */
void printClient (Pq *a){
	printf("%s %d %s\n", a->id, a->priority, a->code);
}

void printClient_file (Pq *a,FILE *f){
	fprintf(f,"%s %20d %20s", a->id, a->priority, a->code);
}

/**Function to compare the data. The only thing that needs 
 * to be compared is the time to intersection. This function is called
 * by the compare function in the linkedlistAPI */
int compareClient (const Pq *A,const Pq *B){
	if(A->priority > B-> priority)	return 1;
	if(A->priority < B-> priority)	return -1;
	return 0;
}

/** This Function compares the priority values in the Nodes
 * used in linkedlistAPI*/
int compareClient_prior (const Node *A,const Node *B){
	if(A->priority_value > B-> priority_value)	return 1;
	if(A->priority_value < B-> priority_value)	return -1;
	return 0;
}

/** This function prints the menu for the user
 * used in main*/
void menu(){
	printf("Please choose one of the options by entering a number\n");
	printf("1. Add new patient\n");
	printf("2. Run simulation\n");
	printf("3. Exit\n");
}


