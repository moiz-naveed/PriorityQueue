/**Author: Moiz Naveed
 * 10/20/2017
 * CIS 2520 Assignment 2
 * main.c
 * "linkedlistAPI.h" created by Micheal Ellis is being used
 * in this program(unedited).
 * */

#include <stdio.h>
#include <string.h>
#include "client.h"
#include "linkedlistAPI.h"
/** HOSPITAL SIMULATOR. CIS 2520 ASSIGNMENT 2*/

int main(int argc, char **argv)
{
	/*Variable declaration*/
	char line[80], *token, cust_id[15], cust_code[2], junk[2], junk1;
	int cust_priority, x = 0, sim_clock = 1, time_comp, count, arr_len, i;
	List *queue = initializeList(&printNode, &deleteListNode, &compare);
	List *order = initializeList(&printNode, &deleteListNode, &compare);
	Pq *a, *b;
	Node *temp;
	/*end of variable declarations*/
	/*Reading File*/
	FILE *f = fopen(argv[1], "r");
	if (f == NULL)
	{
		printf("error! file empty or unreadable\n");
		return 1; /*file empty*/
	}
	/** Reading in the lines, make sure the format in the text file is "id priority code\n" 
	 * or it might not read it properly
	 */
	while (fgets(line, 80, f) != NULL)
	{
		Pq *q = malloc(sizeof(Pq));
		token = strtok(line, " "); /*splits by first space*/
		strcpy(cust_id, token);	   /*the first string is id*/
		token = strtok(NULL, " "); /*it wont read the single int so(kept reading whitespace) i had to assign this to junk*/
		strcpy(junk, token);
		token = strtok(NULL, "\n"); /*last string before the NEWLINE char is the code */
		strcpy(cust_code, token);
		cust_priority = (line[strlen(cust_id) + 1]) - '0'; /*well i know the length of id so i seek to int and read it*/
		strcpy(q->id, cust_id);
		q->priority = cust_priority;
		strcpy(q->code, cust_code);
		insertSorted(queue, q, cust_priority); /*queue is the sorted priority queue*/
		insertBack(order, q);				   /*order is the queue which keeps the data in the order it was entered*/
	}
	fclose(f);
	while (x != 619)
	{
		menu(); /*menu function is in client.c just a bunch of print statements*/
		do
		{
			printf("Enter an integer from 1-3\n");
			scanf("%d", &x);
		} while (x < 1 || x > 3); /*this is to avoid input of unusable ints*/
		if (x == 1)
		{								 /*Patient entry is before the sim because they all arrive at the same time*/
			Pq *q2 = malloc(sizeof(Pq)); /*It wont let me free these at the end. pls explain why
			if I free them here my data gets messed up obviously*/
			printf("Enter Patient ID\n");
			scanf("%s", cust_id);
			printf("Enter priority number\n");
			do
			{
				printf("Priority number must be between 1 and 5\n");
				scanf("%d", &cust_priority);
			} while (cust_priority < 1 || cust_priority > 5);
			printf("Enter the symptom code\n");
			scanf("%s", cust_code);
			strcpy(q2->id, cust_id);
			q2->priority = cust_priority;
			strcpy(q2->code, cust_code);
			insertSorted(queue, q2, cust_priority); /*InsertSort sorts by priorities*/
			insertBack(order, q2);
			printf("Patient Added\n");
		}
		else if (x == 2)
		{
			/*check if list is empty*/
			if (queue->head == NULL)
			{
				printf("Queue is empty\n");
			}
			else
			{ /*starting sim*/
				temp = queue->head;
				arr_len = 0;
				while (temp != NULL)
				{ /*counting how many patients are in the queue*/
					arr_len += 1;
					temp = temp->next;
				}
				int *times = (int *)malloc(arr_len * sizeof(int)); /*this array will hold the completion times in order*/
				while (queue->head != NULL)
				{
					time_comp = 0;
					a = queue->head->data;
					if (strcmp((a->code), "CV") == 0)
					{
						sim_clock += 5;
						time_comp = sim_clock;
					}
					else if (strcmp((a->code), "HN") == 0)
					{
						sim_clock += 3;
						time_comp = sim_clock;
					}
					else if (strcmp((a->code), "EV") == 0)
					{
						sim_clock += 10;
						time_comp = sim_clock;
					}
					else if (strcmp((a->code), "GI") == 0)
					{
						sim_clock += 2;
						time_comp = sim_clock;
					}
					else if (strcmp((a->code), "MH") == 0)
					{
						sim_clock += 5;
						time_comp = sim_clock;
					}
					else if (strcmp((a->code), "NC") == 0)
					{
						sim_clock += 5;
						time_comp = sim_clock;
					}
					else if (strcmp((a->code), "EC") == 0)
					{
						sim_clock += 1;
						time_comp = sim_clock;
					}
					else if (strcmp((a->code), "RC") == 0)
					{
						sim_clock += 1;
						time_comp = sim_clock;
					}
					else if (strcmp((a->code), "SK") == 0)
					{
						sim_clock += 2;
						time_comp = sim_clock;
					}
					else if (strcmp((a->code), "SA") == 0)
					{
						sim_clock += 7;
						time_comp = sim_clock;
					}
					else if (strcmp((a->code), "TR") == 0)
					{
						sim_clock += 4;
						time_comp = sim_clock;
					}
					count = 0;
					temp = order->head;
					while (temp != NULL)
					{ /*checks where in the order list is the patient*/
						b = temp->data;
						if (strcmp(a->id, b->id) == 0)
						{
							break;
						}
						else
						{
							count += 1;
							temp = temp->next;
						}
					}
					times[count] = time_comp;	  /*adds completion time to that spot in the times array*/
					sim_clock += 1;				  /*one second of paper work*/
					deleteNodeFromList(queue, a); /*patient leaves*/
				}
				temp = order->head;
				i = 0;
				f = fopen("output.txt", "w+"); /*creates an output file*/
				fprintf(f, "Patient ID          Priority            Symptom Code        Time Finished\n");
				while (temp != NULL)
				{
					printClient_file(temp->data, f); /*created a seperate print function to print to file*/
					fprintf(f, "%20d\n", times[i]);	 /*prints the completion times to the file*/
					i++;
					temp = temp->next;
				}
				fclose(f);
			}
			printf("Press Enter to continue\n");
			getchar();
			scanf("%c", &junk1);
			break;
		}
		else if (x == 3)
		{
			x = 619;
			break;
		}
	}
	return 0;
}
