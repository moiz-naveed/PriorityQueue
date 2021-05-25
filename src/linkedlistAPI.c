/**Author: Moiz Naveed, Michael Ellis
 *10/20/2017
 * CIS 2520 Assignment 2
 * linkedlistAPI.c
 * function definitions were created by Micheal Ellis
 */
#include <stdio.h>
#include "linkedlistAPI.h"
#include "client.h"

List *initializeList(void (*printFunction)(void *toBePrinted), void (*deleteFunction)(void *toBeDeleted), int (*compareFunction)(const void *first, const void *second))
{
	List *l = malloc(sizeof(List));
	l->head = NULL;
	l->tail = NULL;

	return l;
}

Node *initializeNode(void *data)
{
	Node *n = malloc(sizeof(Node));
	n->next = NULL;
	n->previous = NULL;
	n->data = data;
	return n;
}

void insertFront(List *list, void *toBeAdded)
{
	Node *add_data = initializeNode(toBeAdded);
	if (list->head == NULL)
	{
		list->head = add_data;
		list->tail = add_data;
	}
	else
	{
		list->head->previous = add_data;
		add_data->next = list->head;
		list->head = add_data;
	}
}

void insertBack(List *list, void *toBeAdded)
{
	Node *add_data = initializeNode(toBeAdded);
	if (list->tail == NULL)
	{
		list->head = add_data;
		list->tail = add_data;
	}
	else
	{
		list->tail->next = add_data;
		add_data->previous = list->tail;
		list->tail = add_data;
	}
}

void deleteList(List *list)
{
	Node *temp = list->head;
	Node *temp_next = temp->next;
	while (temp_next != NULL)
	{
		temp_next = temp->next;
		free(temp);
		temp = NULL;
		temp = temp_next;
	}
}

void insertSorted(List *list, void *toBeAdded, int prior_val)
{
	Node *add_data = initializeNode(toBeAdded);
	add_data->priority_value = prior_val;
	Node *temp = list->head;
	if (temp == NULL)
	{
		list->head = add_data;
		list->tail = add_data;
	}
	else
	{
		while (temp->next != NULL)
		{
			if (compare(temp->data, add_data->data) < 1)
			{
				temp = temp->next;
			}
			else
			{
				break;
			}
		}
		if (temp->next == NULL && temp->previous == NULL)
		{
			if (compare(temp->data, add_data->data) == 1)
				insertFront(list, toBeAdded);
			if (compare(temp->data, add_data->data) == -1)
				insertBack(list, toBeAdded);
		}
		else if (temp->next == NULL && compare(temp->data, add_data->data) == -1)
		{
			insertBack(list, toBeAdded);
		}
		else if (temp->previous == NULL && compare(temp->data, add_data->data) == 1)
		{
			insertFront(list, toBeAdded);
		}
		else
		{
			Node *temp_prev = temp->previous;
			add_data->next = temp;
			add_data->previous = temp_prev;
			temp->previous = add_data;
			temp_prev->next = add_data;
		}
	}
}

int deleteNodeFromList(List *list, void *toBeDeleted)
{
	Node *temp = list->head;
	Node *temp_next;
	Node *temp_prev;
	while (temp != NULL)
	{
		if (compare(temp->data, toBeDeleted) == 0)
		{
			temp_next = temp->next;
			temp_prev = temp->previous;
			deleteListNode(temp);
			if (temp_next == NULL && temp_prev == NULL)
			{
				list->head = NULL;
				list->tail = NULL;
			}
			else if (temp_prev == NULL)
			{
				list->head = temp_next;
			}
			else if (temp_next == NULL)
			{
				list->tail = temp_prev;
			}
			break;
		}
		temp = temp->next;
	}

	return 0;
}

void *getFromFront(List *list)
{
	Node *temp = list->head;
	return temp;
}

void *getFromBack(List *list)
{
	Node *temp = list->tail;
	return temp;
}

void printForward(List *list)
{
	Node *temp = list->head;
	if (temp == NULL)
	{
		printf("List empty\n");
	}
	else
	{
		while (temp != NULL)
		{
			printNode(temp->data);
			temp = temp->next;
		}
	}
}

void printBackwards(List *list)
{
	Node *temp = list->tail;
	if (temp == NULL)
	{
		printf("List empty\n");
	}
	else
	{
		while (temp != NULL)
		{
			printNode(temp->data);
			temp = temp->previous;
		}
	}
}

void deleteListNode(void *toBeDeleted)
{
	Node *temp = toBeDeleted;
	Node *temp_next = temp->next;
	Node *temp_prev = temp->previous;
	if (temp_next == NULL && temp_prev == NULL)
	{
		free(temp);
		temp = NULL;
		EXIT_SUCCESS;
	}
	else if (temp->previous == NULL)
	{
		free(temp);
		temp = NULL;
		temp = temp_next;
		temp->previous = NULL;
		EXIT_SUCCESS;
	}
	else if (temp->next == NULL)
	{
		free(temp);
		temp = NULL;
		temp = temp_prev;
		temp->next = NULL;
		EXIT_SUCCESS;
	}
	else
	{
		free(temp);
		temp = NULL;
		temp = temp_next;
		temp->previous = temp_prev;
		temp = temp_prev;
		temp->next = temp_next;
		EXIT_SUCCESS;
	}
}

/**
 * 
 * CHANGE APPLICATION SPECIFIC PRINT AND COMPARE FUNCTIONS HERE
 */
int compare(const void *first, const void *second)
{
	int x;
	x = compareClient(first, second);
	return x;
}

void printNode(void *toBePrinted)
{
	printClient(toBePrinted);
}
