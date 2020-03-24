// Noah Avizemer
// COP 3502, Spring 2019
// no886776
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

// takes a string and removes punctuation
void stripPunctuators(char *str)
{
	int i, j;
	int len = strlen(str);
	char buffer[1024];
	for (i = 0, j = 0; i < len; i++)
	{
		// only copies over if not punc
		if (!ispunct(str[i]))
		{
			buffer[j] = str[i];
			j++;
		}
	}
	strcpy(str, buffer);
}

// From Dr.Szumlanski's notes on tries
// creates the node and initializes the members
TrieNode *createNode(void)
{
	int i;
	TrieNode *n = malloc(sizeof(TrieNode));

	n->count = 0;
	n->subtrie == NULL;
	for (i = 0; i < 26; i++)
	{
		n->children[i] = NULL;
	}

	return n;
}

// From Dr.Szumlanski's notes on tries
// Insert a string into a trie. This function returns the root of the trie.
TrieNode *insert(TrieNode *root, char *str)
{
	int i, index, len = strlen(str);
	TrieNode *wizard;

	if (root == NULL)
	{
		root = createNode();
	}

	wizard = root;

	// skips over non alphabetic chars
	for (i = 0; i < len; i++)
	{
		if (!isalpha(str[i]))
		{
			continue;
		}
		index = tolower(str[i]) - 'a';

		// creates a node where it is null
		if (wizard->children[index] == NULL)
		{
			wizard->children[index] = createNode();
		}
		wizard = wizard->children[index];
	}

	wizard->count++;
	return root;
}

// From Dr.Szumlanski's notes on tries
TrieNode *buildTrie(char *filename)
{
	TrieNode *root = NULL;
	char buffer[1024];

	FILE *ifp;

	if ((ifp = fopen(filename, "r")) == NULL)
	{
		return NULL;
	}

	// Insert strings one-by-one into the trie.
	while (fscanf(ifp, "%s", buffer) != EOF)
	{
		root = insert(root, buffer);
	}

	fclose(ifp);
	return root;
	
}



// incomplete, only opens the file
int processInputFile(TrieNode *root, char *filename)
{
	FILE *ifp;
	char buffer[1024];
	if ((ifp = fopen(filename, "r")) == NULL)
	{
		return 1;
	}


	fclose(ifp);
	return 0;
}

TrieNode *destroyTrie(TrieNode *root)
{
	int i;
	if (root == NULL)
	{
		return NULL; 
	} 

	for (i = 0; i < 26; i++)
	{
		// skip children that are null
		if (root->children[i] == NULL)
		{
			continue;
		}
		else
		{
			destroyTrie(root->children[i]);
		}
	}
	
	free(root);

	return NULL;
}

TrieNode *getNode(TrieNode *root, char *str)
{
	int i, j;
	int len = strlen(str);
	TrieNode *node = root;
	if (root == NULL)
	{
		return NULL;
	}
	if (str == NULL)
	{
		return NULL;
	}
	// if the string is empty, then it is in the root
	if (str[0] == '\0')
	{
		return root;
	}
	
	// goes checks each child
	for (i = 0; i < len; i++)
	{

		j = str[i] - 'a';

		if (node->children[j] == NULL)
		{
			return NULL;
		}
		node = node->children[j];
	}

	// if we get to the end of the string and the count is zero, it does not exist
	if (str[i] == '\0' && (node->count == 0))
	{
		return NULL;
	}
	else
	{
		return node;
	}
	
}

// incomplete, only includes some initial checks and for empty string
void getMostFrequentWord(TrieNode *root, char *str)
{
	char buffer[1024];
	int count;
	int i;
	// if root is null then return empty string
	if (root == NULL)
	{
		strcpy(str, "");
		return;
	}
	if (str == NULL)
	{
		return;
	}
	
}

int containsWord(TrieNode *root, char *str)
{
	int i, j;
	int len = strlen(str);
	TrieNode *node = root;
	if (root == NULL)
	{
		return 0;
	}
	if (str == NULL)
	{
		return 0;
	}
	
	//  checks each child
	for (i = 0; i < len; i++)
	{

		j = str[i] - 'a';

		if (node->children[j] == NULL)
		{
			return 0;
		}
		node = node->children[j];
	}
	// if at end of string and the count is 0, it is not there
	if (str[i] == '\0' && (node->count == 0))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}


// Incomplete, only includes initial checks
int prefixCount(TrieNode *root, char *str)
{
	int i, j, count = 0;
	int len = strlen(str);
	TrieNode *node = root;

	if (root == NULL)
	{
		return 0;
	}
	if (str == NULL)
	{
		return 0;
	}
	

	return count;
}

double difficultyRating(void)
{
	return 5;
}

double hoursSpent(void)
{
	return 8;
}

int main(int argc, char **argv)
{
	TrieNode *trie = buildTrie(argv[1]);
	processInputFile(trie, argv[2]);
	destroyTrie(trie);
	return 0;
}
