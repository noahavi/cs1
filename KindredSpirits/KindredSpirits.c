// Noah Avizemer
// COP 3502, Spring 2019
// no886776

#include <stdio.h>
#include <stdlib.h>
#include "KindredSpirits.h"


// From Szum's notes on stacks
typedef struct Stack
{
	int *array;
	int size;
	int capacity;

} Stack;

int isReflection(node *a, node *b)
{
	// if both null then they are empty
	if (a == NULL && b == NULL)
	{
		return 1;
	}
	// if one or the other is null they cant be ref
	if (a == NULL && b != NULL || a != NULL && b == NULL)
	{
		return 0;
	}
	// The roots must be equal to be reflections
	if (a->data == b->data)
	{
		// The left on a must match right on b and vice versa
		return isReflection(a->left, b->right) && isReflection(a->right, b->left);
	}
	else
	{
		return 0;
	}
}

// from szumlanski's test case, creates new node
node *createNodeTree(int data)
{
	node *n = malloc(sizeof(node));

	n->data = data;
	n->left = n->right = NULL;

	return n;
}


node *makeReflection(node *root)
{
	if (root == NULL)
	{
		return NULL;
	}

	// Makes root node first and matches left with right vice versa
	node *ref = createNodeTree(root->data);
	ref->left = makeReflection(root->right); 
	ref->right = makeReflection(root->left);
	
	return ref;
}


int countNodes(node *root)
{
	if (root == NULL)
	{
		return 0;
	}
	else
	{
		return 1 + countNodes(root->left) + countNodes(root->right);
	}
}

// From Szum's notes on stacks
// Returns a new stack
Stack *createStack(int capacity)
{
	Stack *s;
	
	if ((s = malloc(sizeof(Stack))) == NULL)
		return NULL;

	if ((s->array = malloc(sizeof(int) * capacity)) == NULL)
	{
		free(s);
		return NULL;
	}

	s->size = 0;
	s->capacity = capacity;

	return s;
}

// From Szum's notes on stacks
// Pushes the data into the array
void push(Stack *s, int data)
{
	s->array[ s->size++ ] = data;
}

// Does the post order traversal, pushes into stack
Stack *createPostStackHelp(node *n, Stack *s)
{
	if (n == NULL)
	{
		return NULL;
	}

	createPostStackHelp(n->left, s);
	createPostStackHelp(n->right, s);
	push(s, n->data);

	return s;
}

// Preorder traversal, pushes data into stack
Stack *createPreStackHelp(node *n, Stack *s)
{
	if (n == NULL)
	{
		return NULL;
	}
	push(s, n->data);
	createPreStackHelp(n->left, s);
	createPreStackHelp(n->right, s);

	return s;
}

Stack *createPreStack(node *n)
{
	int capacity = countNodes(n);
	return createPreStackHelp(n, createStack(capacity));
}


Stack *createPostStack(node *n)
{
	int capacity = countNodes(n);
	return createPostStackHelp(n, createStack(capacity));
}

int kindredSpirits(node *a, node *b)
{
	int diff = 0;
	int i = 0;
	int j;
	int nodeCountA = countNodes(a);
	int nodeCountB = countNodes(b);

	if (a == NULL && b == NULL)
	{
		return 1;
	}
	if (a == NULL || b == NULL)
	{
		return 0;
	}
	// If node count is different, trees cant be kindred spirits
	if (nodeCountA != nodeCountB)
	{
		return 0;
	}

	Stack *stackA = createPreStack(a);
	Stack *stackB = createPostStack(b);


	// Sets flag to 1 if difference is found in data
	for (i = 0; i < nodeCountA; i++)
	{
		if (stackA->array[i] != stackB->array[i])
		{
			diff = 1;
		}
	}


	// Switches order of trees and checks again
	if (diff == 1)
	{
		Stack *stackA = createPreStack(b);
		Stack *stackB = createPostStack(a);
		diff = 0;

		for (j = 0; j < nodeCountA; j++)
		{
			if (stackA->array[j] != stackB->array[j])
			{
				diff = 1;
			}
		}
		// If the flag is set to 1, the trees are not kindred spirits
		if (diff > 0)
		{
			return 0;
		}
		else
		{
			return 1;
		}

	}
	
}

double difficultyRating(void)
{
	return 4;
}

double hoursSpent(void)
{
	return 9;
}
