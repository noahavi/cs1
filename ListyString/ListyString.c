// Noah Avizemer
// COP 3502, Spring 2019
// no886776

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListyString.h"


int processInputFile(char *filename);
int main(int argc, char **argv)
{
	processInputFile(argv[1]);
	return 0;
}
// incomplete
int processInputFile(char *filename)
{
	int i, length;
	char buffer[1024];
	char *word, *list;
	ListyString *listy;
	FILE *ifp;
	if ((ifp = fopen(filename, "r")) == NULL)
	{
		return 1;
	}
	// gets the original string and creates a linked list
	if (fscanf(ifp, "%s", buffer) == 1)
		{
			list = malloc(sizeof(char) * (strlen(buffer) + 1));
			strcpy(list, buffer);
			listy = createListyString(list);
		}
	// incomplete
	while (fscanf(ifp, "%s", buffer) != EOF)
	{
		word = malloc(sizeof(char) * (strlen(buffer) + 1));
		strcpy(word, buffer);
		if (word[0] == '!')
		{
			printListyString(listy);
		}
		if (word[0] == '?')
		{
			printf("%d", listyLength(listy));
		}
		if (word[0] == '~')
		{
			reverseListyString(listy);
		}
	}
	return 0;
	
}


ListyString *createListyString(char *str)
{
	int i, len;
	ListyNode *Ln = malloc(sizeof(ListyNode));
	ListyString *Ls = malloc(sizeof(ListyString));
	if (str == NULL || strcmp(str, "") == 0)
	{
		Ls->head = NULL;
		Ls->length = 0;
		return Ls;
	}
	len = strlen(str);
	Ls->length = len;
	Ls->head = Ln;
	for (i = 0; i < len; i++)
	{
		// sets the last value and makes sure an extra node isnt created
		if (i == len - 1)
		{
			Ln->data = str[i];
			break;
		}
		Ln->data = str[i];
		Ln->next = malloc(sizeof(ListyNode));
		Ln = Ln->next;
		
	}
	Ln->next = NULL;
	return Ls;
}

ListyString *destroyListyString(ListyString *listy)
{
	ListyNode *Ln;
	ListyNode *temp;

	if (listy == NULL)
	{
		return NULL;
	}
	if (listy->head == NULL)
	{
		free(listy);
		return NULL;
	}

	Ln = listy->head;
	// moves through the listystring frees each node
	while (Ln != NULL)
	{
		temp = Ln->next;
		free(Ln);
		Ln = temp;
	}
	free(listy);
	return NULL;

}

ListyString *cloneListyString(ListyString *listy)
{
	int i;
	ListyString *clone = malloc(sizeof(listy));
	ListyNode *node_clone;
	if (listy == NULL)
	{
		return NULL;
	}
	if (listy->head == NULL)
	{
		clone->head == NULL;
		clone->length = 0;
		return clone;
	}
	ListyNode *node = listy->head;
	clone->head = listy->head;
	// creates a new node for clone and puts data in it
	while (node != NULL)
	{
		node_clone = malloc(sizeof(ListyNode));
		node_clone->data = node->data;
		node = node->next;
	}

	return clone;
}
// incomplete
void replaceChar(ListyString *listy, char key, char *str)
{
	if (listy == NULL || listy->head == NULL)
	{
		return;
	}
}


void reverseListyString(ListyString *listy)
{
	if (listy == NULL || listy->head == NULL)
	{
		return;
	}

	ListyNode *node = listy->head;
	ListyNode *next = NULL;
	ListyNode *last = NULL;

	while (node != NULL)
	{
		next = node->next;
		node->next = last;
		last = node;
		node = next;
		// puts the head at the end
		if (node == NULL)
		{
			listy->head = last;
		}
	}
}


ListyString *listyCat(ListyString *listy, char *str)
{
	int i, len, new_len;
	ListyString *new_listy;
	ListyNode *new_node, *node;
	ListyNode *temp;
	char *str2;
	if (listy == NULL && str == NULL)
	{
		return NULL;
	}
	// null or empty string
	if (str == NULL || strcmp(str, "") == 0)
	{
		return listy;
	}
	// non null empty string and null listy
	if (listy == NULL && (strcmp(str, "") == 0) && str != NULL)
	{
		ListyString *new_listy = malloc(sizeof(ListyString));
		listy->head = NULL;
		listy->length = 0;
		return new_listy;
	}
	// null listy and non empty string
	if (listy == NULL && strcmp(str, "") == 1)
	{
		return createListyString(str);
	}
	len = strlen(str);
	new_len = len + listy->length;
	// empty listy and non empty string
	// creates a new listy string from str
	if (listy->head == NULL)
	{
		new_node = malloc(sizeof(ListyNode));
		listy->head = new_node;
		listy->length = len;

		for (i = 0; i < len; i++)
		{
			new_node->data = str[i];
			if (i != len - 1)
			{
				new_node->next = malloc(sizeof(ListyNode));
				new_node = new_node->next;
			}
		}
		new_node->next = NULL;
		return listy;
	}
	// non empty listy string and non empty string
	else
	{
		node = listy->head;
		listy->length = len + listy->length;
		// goes to the end of the listy string
		while (node->next != NULL)
		{
			node = node->next;
		}
		// begins creating nodes at the end and adding the str to the end
		for (i = 0; i < len; i++)
		{
			if (i != len)
			{
				node->next = malloc(sizeof(ListyNode));
				node = node->next;
				node->data = str[i];
			}
		}
		node->next = NULL;
		return listy;
	} 
}
	


int listyCmp(ListyString *listy1, ListyString *listy2)
{
	int diff = 0;
	if (listy1 == NULL && listy2 == NULL)
	{
		return 0;
	}
	if (listy1 == NULL || listy2 == NULL)
	{
		return -1;
	}
	if (listy1->head == NULL && listy2->head == NULL)
	{
		return 0;
	}
	if (listy1->head == NULL || listy2->head == NULL)
	{
		return -1;
	}
	ListyNode *N1 = listy1->head;
	ListyNode *N2 = listy2->head;

	// goes through both listys until NULL
	while (N1 != NULL && N2 != NULL)
	{
		// if a difference is found, flag is set to 1
		if (N1->data != N2->data)
		{
			diff = 1;
		}
		N1 = N1->next;
		N2 = N2->next;
	}
	if (diff != 0)
	{
		return -1;
	}
	else
	{
		return 0;
	}

}

int listyLength(ListyString *listy)
{
	if (listy == NULL)
	{
		return -1;
	}
	if (listy->head == NULL)
	{
		return 0;
	}
	
	return listy->length;
}

void printListyString(ListyString *listy)
{
	if (listy == NULL || listy->head == NULL)
	{
		printf("(empty string)\n");
		return;
	}
	ListyNode *node = listy->head;
	// prints data in each node until node is NULL, then prints \n
	while (node != NULL)
	{
		printf("%c", node->data); 
		node = node->next;
		if (node == NULL)
		{
			printf("\n");
		}
	}
}


double difficultyRating(void)
{
	return 5;
}

double hoursSpent(void)
{
	return 14;
}
