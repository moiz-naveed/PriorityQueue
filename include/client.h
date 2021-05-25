/**Author: Moiz Naveed
 *10/20/2017
 * CIS 2520 Assignment 2
 * client.h*/

#ifndef CLIENT_H
#define CLIENT_H
#include <stdlib.h>
#include "linkedlistAPI.h"
/** THE Client STRUCT */
typedef struct pq
{
	char id[15];
	int priority;
	char code[2];
} Pq;

/** Function definitions*/

void printClient(Pq *a);

void printClient_file(Pq *a, FILE *f);

int compareClient(const Pq *A, const Pq *B);

int compareClient_prior(const Node *A, const Node *B);

void menu();

#endif
