// This template is included to help get you started. I've written some trie
// printing functions for you, which are included below. Please be sure to delete
// this comment and add your name to this source file.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "TriePrediction.h"

// Helper function called by printTrie(). (Credit: Dr. S.)
void printTrieHelper(TrieNode *root, char *buffer, int k)
{
	int i;

	if (root == NULL)
		return;

	if (root->count > 0)
		printf("%s (%d)\n", buffer, root->count);

	buffer[k + 1] = '\0';

	for (i = 0; i < 26; i++)
	{
		buffer[k] = 'a' + i;

		printTrieHelper(root->children[i], buffer, k + 1);
	}

	buffer[k] = '\0';
}

// If printing a subtrie, the second parameter should be 1; otherwise, if
// printing the main trie, the second parameter should be 0. (Credit: Dr. S.)
void printTrie(TrieNode *root, int useSubtrieFormatting)
{
	char buffer[1026];

	if (useSubtrieFormatting)
	{
		strcpy(buffer, "- ");
		printTrieHelper(root, buffer, 2);
	}
	else
	{
		strcpy(buffer, "");
		printTrieHelper(root, buffer, 0);
	}
}

// Helper function to create a Trie Node, everything initialized to NULL (inspired by Dr. S)
TrieNode *createTrieNode(void)
{
	TrieNode *n;
	int i;

	n = malloc(sizeof(TrieNode));

	for (i = 0; i < 26; i++)
		n->children[i] = NULL;

	n->subtrie = NULL;
	n->count = 0;

	return n;
}

// Helper function for prefixCount... Recursively goes through every child of the structure...
int prefixCountHelper(TrieNode *root)
{
	if (root == NULL)
		return 0;

	// behemoth return statement... please don't mind this and continue examining... 
	return root->count + prefixCountHelper(root->children[0]) + prefixCountHelper(root->children[1]) + prefixCountHelper(root->children[2])
		+ prefixCountHelper(root->children[3]) + prefixCountHelper(root->children[4]) + prefixCountHelper(root->children[5]) + prefixCountHelper(root->children[6])
		+ prefixCountHelper(root->children[7]) + prefixCountHelper(root->children[8]) + prefixCountHelper(root->children[9]) + prefixCountHelper(root->children[10])
		+ prefixCountHelper(root->children[11]) + prefixCountHelper(root->children[12]) + prefixCountHelper(root->children[13]) + prefixCountHelper(root->children[14])
		+ prefixCountHelper(root->children[15]) + prefixCountHelper(root->children[16]) + prefixCountHelper(root->children[17]) + prefixCountHelper(root->children[18])
		+ prefixCountHelper(root->children[19]) + prefixCountHelper(root->children[20]) + prefixCountHelper(root->children[21]) + prefixCountHelper(root->children[22])
		+ prefixCountHelper(root->children[23]) + prefixCountHelper(root->children[24]) + prefixCountHelper(root->children[25]);
}

// adds strings into the Trie and Subtrie (inspired by Dr. S)
// string is the string being added to the main trie, it is also the string being added into the sub trie of string2
TrieNode *insertString(TrieNode *root, char *string, char *string2)
{
	// printf("inside insertString function - string: %s, string2: %s \n", string, string2);
	// fflush(stdout);
	TrieNode *p;
	TrieNode *terminal;
	int i, len = strlen(string), len2 = strlen(string2), array_index;
	
	if (root == NULL)
		root = createTrieNode();
	
	p = root;

	for (i = 0; i < len; i++)
	{
		array_index = tolower(string[i]) - 'a';

		if (p->children[array_index] == NULL)
			p->children[array_index] = createTrieNode();

		p = p->children[array_index];
	}
	
	p->count++;

	// Inserting to subtrie: 
	// string 2 (string before string 1) isn't 0, insert string into subtrie of string 2.
	if (strlen(string2) != 0)
	{
		terminal = getNode(root, string2);

		if (terminal->subtrie == NULL)
			terminal->subtrie = createTrieNode();
		
		p = terminal->subtrie;

		for (i = 0; i < len; i++)
		{
			array_index = tolower(string[i]) - 'a';

			if (p->children[array_index] == NULL)
				p->children[array_index] = createTrieNode();
			
			p = p->children[array_index];
		}

		p->count++;
	}
	
	return root;
}

// required functions: 
TrieNode *buildTrie(char *filename)
{
	int i = 0, j = 0, k = 0, flag = 0, len;
	TrieNode *n;
	TrieNode *root = NULL;
	char buffer[1024], filtered_buffer[1024], filtered_buffer2[1024];

	FILE * ifp = fopen(filename, "r");

	if (ifp == NULL)
		return NULL;

	// filtered_buffer2 will contain the string before the scanned string.
	strcpy(filtered_buffer2, "");

	while (fscanf(ifp, "%s", buffer) != EOF)
	{
		len = strlen(buffer);
		i = 0;
		j = 0;
		
		if (flag == 1)
		{
			strcpy(filtered_buffer2,"");
			flag = 0;
		}

		for (i = 0; i < len; i++)
		{
			// flags if the scanned string is at the end of a sentence.
			if (buffer[i] == 63 || buffer[i] == 32 || buffer[i] == 46)
				flag = 1;

			if ((buffer[i] >= 97 && buffer[i] <= 122) || (buffer[i] >= 65 && buffer[i] <= 90))
			{
				filtered_buffer[j] = buffer[i];
				filtered_buffer[++j] = '\0';
			}
		}

	
		root = insertString(root, filtered_buffer, filtered_buffer2);
		strcpy(filtered_buffer2, filtered_buffer);
	}

	return root;
}

int processInputFile(TrieNode *root, char *filename)
{
	char buffer[1024];
	int n, len, i;
	TrieNode *p;

	FILE * ifp = fopen(filename, "r");

	if (ifp == NULL)
		return 1;

	while (fscanf(ifp, "%s", buffer) != EOF)
	{
		// if statements that calls the other functions depending on commands given from file
		if ((strcmp(buffer, "!")) == 0)
			printTrie(root, 0);

		else if ((strcmp(buffer, "@")) == 0)
		{
			fscanf(ifp, "%s", buffer);
			fscanf(ifp, "%d", n);
			// NEEDS TO BE WORKED ON REEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
		}

		else
		{
			printf("%s\n", buffer);
			len = strlen(buffer);

			for (i = 0; i < len; i++)
				buffer[i] = tolower(buffer[i]);

			p = getNode(root, buffer);

			if (p == NULL)
				printf("(INVALID STRING)\n");

			else
			{
				if (p->subtrie == NULL)
					printf("(EMPTY)\n");

				else
					printTrie(p->subtrie, 1);
			}
		}
	}

	return 0;
}

TrieNode *destroyTrie(TrieNode *root)
{
	int i;

	// if the root is NULL, returns NULL
	if (root == NULL)
		return NULL;

	// for loop to recursively call destroy function for every children of the alphabet
	for (i = 0; i <= 26; i++)
		destroyTrie(root->children[i]);

	// frees the current root
	free(root);

	return NULL;
}

TrieNode *getNode(TrieNode *root, char *str)
{
	TrieNode *p;
	int len = strlen(str), i = 0, array_index;

	p = root;

	for (i = 0; i < len; i++)
	{
		array_index = tolower(str[i]) - 'a';

		if (p->children[array_index] == NULL)
			return NULL;

		else
			p = p->children[array_index];
	}

	if (p->count > 0)
		return p;

	else
		return NULL;
}

void getMostFrequentWord(TrieNode *root, char *str)
{
}

int containsWord(TrieNode *root, char *str)
{
	TrieNode *p;
	int i, len = strlen(str), array_index = 0;

	p = root;

	for (i = 0; i < len; i++)
	{
		array_index = tolower(str[i]) - 'a';

		if (p->children[array_index] == NULL)
			return 0;

		p = p->children[array_index];
	}

	if (p->count > 0)
		return 1;

	else
		return 0;
}

int prefixCount(TrieNode *root, char *str)
{
	int i, len = strlen(str), array_index;
	TrieNode *p;

	if (root == NULL)
		return 0;

	else if (strlen(str) == 0)
		return prefixCountHelper(root);
	
	else
	{
		p = root;

		for (i = 0; i < len; i++)
		{
			array_index = tolower(str[i]) - 'a';
			p = p->children[array_index];

			if (p == NULL)
				return 0;
		}

		return prefixCountHelper(p);
	}
}

double difficultyRating(void)
{
	return 3.5;
}

double hoursSpent(void)
{
	return 20.0;
}

int main(int argc, char **argv)
{
	char input[5];
	strcpy(input, "name");
	TrieNode *root;
	TrieNode *p;

	root = buildTrie(argv[1]);
	processInputFile(root, argv[2]);
	destroyTrie(root);

	return 0;
}
