#include <stdio.h>
#include <stdlib.h>
#include "KindredSpirits.h"

typedef struct Queue
{
	int capicity;
	int rear;
	int *array;

} Queue;

int count_nodes( node *root)
{
    if(root == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + count_nodes(root->left) +count_nodes(root->right);
    }
}

Queue *createQueue(int capicity)
{
	Queue *q = malloc(sizeof(Queue));
	q->array = malloc(sizeof(int) * capicity);
	q->capicity = capicity;
	q->rear = 0;

	return q;
}

void enqueue(Queue *q, int data)
{
	if (q->capicity == q->rear)
	{
		return;
	}
	q->array[q->rear++] = data;
}

Queue *PreorderQueue(node *root, Queue *q)
{
	if (root == NULL)
	{
		return NULL;
	}

	enqueue(q, root->data);
	PreorderQueue(root->left, q);
	PreorderQueue(root->right, q);

	return q;
}

Queue *PostorderQueue(node *root, Queue *q)
{
	if (root == NULL)
	{
		return NULL;
	}

	PostorderQueue(root->left, q);
	PostorderQueue(root->right, q);
	enqueue(q, root->data);

	return q;
}

Queue *PostorderHelp(node *root)
{
	Queue *q = createQueue(count_nodes(root));
	return PostorderQueue(root, q);
}

Queue *PreorderHelp(node *root)
{
	Queue *q = createQueue(count_nodes(root));
	return PreorderQueue(root, q);
}

int kindredSpirits(node *a, node *b)
{
	int i, j;
	int size = count_nodes(a);
	int size1 = count_nodes(b);
	int diff = 0;

	if (a == NULL && b == NULL)
	{
		return 1;
	}
	else if ((a == NULL && b != NULL) || (a != NULL && b == NULL))
	{
		return 0;
	}
	else if(count_nodes(a) != count_nodes(b))
	{
		return 0;
	}

	Queue *PreA = PreorderHelp(a);
	Queue *PostB = PostorderHelp(b);

	//printf("%d \n", PostB->array[0]);
	//printf("%d \n", PostB->array[1]);
	//printf("%d \n", PostB->array[2]);
	//printf("%d \n", PostB->array[3]);

	for (i = 0; i < size; i++)
	{
		if (PreA->array[i] != PostB->array[i])
		{
			diff = 1;
		}
	}


	// Switches order of trees and checks again
	if (diff == 1)
	{
		Queue *PreA = PreorderHelp(b);
		Queue *PostB = PostorderHelp(a);
		diff = 0;

		for (j = 0; j < size; j++)
		{
			if (PreA->array[j] != PostB->array[j])
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
	