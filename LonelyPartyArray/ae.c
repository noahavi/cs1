#include <stdio.h>
#include <stdlib.h>
#include "LonelyPartyArray.h"

void check_size(LonelyPartyArray *party);
void check_fragments(LonelyPartyArray *party);
LonelyPartyArray *createLonelyPartyArray(int num_fragments, int fragment_length)
{
	int i;
	LPA *party = NULL;

	if (num_fragments <= 0 || fragment_length <= 0)
	{
		return NULL;
	}

	party = malloc(sizeof(LPA));

	if (party == NULL)
	{
		return NULL;
	}

	party->num_fragments = num_fragments;
	party->fragment_length = fragment_length;
	party->size = 0;

	party->fragments = (int **)malloc(party->num_fragments * sizeof(int *));

	if (party->fragments == NULL)
	{
		free(party);
		return NULL;
	}

	party->fragment_sizes = malloc(party->num_fragments * sizeof(int *));

	if (party->fragment_sizes == NULL)
	{
		free(party);
		free(party->fragments);
		return NULL;
	}

	for (i = 0; i < party->num_fragments; i++)
	{
		party->fragment_sizes[i] = 0;
		party->fragments[i] = NULL;
	}

	printf("-> A new LonelyPartyArray has emerged from the void. (capacity: %d, fragments: %d)\n", party->num_fragments * party->fragment_length, party->num_fragments);

	return party;
}

//Frees all dynamically allocated memory and sets the party to NULL
LonelyPartyArray *destroyLonelyPartyArray(LonelyPartyArray *party)
{
	int i;

	if (party == NULL)
	{
		return NULL;
	}

	for (i = 0; i < party->num_fragments; i++)
	{
		if (party->fragments[i] != NULL)
		{
			free(party->fragments[i]);
		}
	}

	free(party->fragments);
	free(party->fragment_sizes);
	free(party);

	printf("-> The LonelyPartyArray has returned to the void.\n");

	return NULL;
}

//Dynamically allocates a row of the 2D array if the row
//where the index refers to is NULL, otherwise the cell
//of the row is changed from UNUSED to key
int set(LonelyPartyArray *party, int index, int key)
{
	int lowest = 0;
	int highest = 0;
	int frag = 0;
	int cell = 0;
	int j;
	int i;

	if (party == NULL)
	{
		printf("-> Bloop! NULL pointer detected in set().\n");
		return LPA_FAILURE;
	}

	frag = index / party->fragment_length;

	cell = index - (party->fragment_length * frag);

	if (index < 0 || index >(party->num_fragments * party->fragment_length - 1))
	{
		printf("-> Bloop! Invalid access in set(). (index: %d, fragment: %d, offset: %d)\n", index, frag, cell);
		return LPA_FAILURE;
	}

	if (party->fragments[frag] == NULL)
	{
		lowest = (party->fragment_length * frag);
		highest = (party->fragment_length * (frag + 1)) - 1;
		party->fragments[frag] = malloc(party->fragment_length * sizeof(int *));

		if (party->fragments[frag] == NULL)
		{
			return LPA_FAILURE;
		}

		for (i = 0; i < party->num_fragments; i++)
		{
			for (j = 0; j < party->fragment_length; j++)
			{
				party->fragments[frag][j] = UNUSED;
				party->fragments[frag][cell] = key;
			}
		}
		printf("-> Spawned fragment %d. (capacity: %d, indices: %d..%d)\n", frag, party->fragment_length, lowest, highest);
	}

	else
	{
		party->fragments[frag][cell] = key;
	}

	check_fragments(party);
	check_size(party);

	return LPA_SUCCESS;
}

//Returns the value located at the index of the array

int get(LonelyPartyArray *party, int index)
{
	int frag = 0;
	int cell = 0;

	if (party == NULL)
	{
		printf("-> Bloop! NULL pointer detected in get().\n");
		return LPA_FAILURE;
	}

	frag = index / party->fragment_length;

	cell = index - (party->fragment_length * frag);

	if (index < 0 || index >(party->num_fragments * party->fragment_length - 1))
	{
		printf("-> Bloop! Invalid access in get(). (index: %d, fragment: %d, offset: %d)\n", index, frag, cell);
		return LPA_FAILURE;
	}

	if (party->fragments[frag] == NULL)
	{
		return UNUSED;
	}

	return party->fragments[frag][cell];
}


//Deletes the value located at the index of the array
//if there is one, otherwise it returns LPA_FAILURE
int delete(LonelyPartyArray *party, int index)
{
	int lowest = 0;
	int highest = 0;
	int frag = 0;
	int cell = 0;
	int i;

	if (party == NULL)
	{
		printf("-> Bloop! NULL pointer detected in delete().\n");
		return LPA_FAILURE;
	}

	frag = index / party->fragment_length;

	cell = index - (party->fragment_length * frag);

	if (index < 0 || index >(party->num_fragments * party->fragment_length - 1))
	{
		printf("-> Bloop! Invalid access in delete(). (index: %d, fragment: %d, offset: %d)\n", index, frag, cell);
		return LPA_FAILURE;
	}

	if (party->fragments[frag] == NULL || party->fragments[frag][cell] == UNUSED)
	{
		return LPA_FAILURE;
	}

	party->fragments[frag][cell] = UNUSED;
	party->size--;
	party->fragment_sizes[frag]--;

	if (party->fragment_sizes[frag] == 0)
	{
		free(party->fragments[frag]);
		party->fragments[frag] = NULL;
		check_fragments(party);
		check_size(party);
		lowest = (party->fragment_length * frag);
		highest = (party->fragment_length * (frag + 1)) - 1;
		printf("-> Deallocated fragment %d. (capacity: %d, indices: %d..%d)\n", frag, party->fragment_length, lowest, highest);
		return LPA_SUCCESS;
	}

	return LPA_SUCCESS;
}

//Checks the entire array for the key and returns 1
//if found and 0 if not found
int containsKey(LonelyPartyArray *party, int key)
{
	int i;
	int j;

	if (party == NULL)
	{
		return 0;
	}

	for (i = 0; i < party->num_fragments; i++)
	{
		if (party->fragments[i] != NULL)
		{
			for (j = 0; j < party->fragment_length; j++)
			{
				if (party->fragments[i][j] == key)
				{
					return 1;
				}
			}
		}
	}

	return 0;
}

//Checks if a value other than UNUSED is located at
//the index of the array
int isSet(LonelyPartyArray *party, int index)
{
	int frag = 0;
	int cell = 0;

	if (party == NULL)
	{
		return 0;
	}

	if (index < 0 || index >(party->num_fragments * party->fragment_length - 1))
	{
		return 0;
	}

	frag = index / party->fragment_length;

	cell = index - (party->fragment_length * frag);

	if (party->fragments[frag] == NULL || party->fragments[frag][cell] == UNUSED)
	{
		return 0;
	}

	return 1;
}

//Prints the value located at the index of the array
//if it isn't UNUSED or if the row is NULL
int printIfValid(LonelyPartyArray *party, int index)
{
	int frag = 0;
	int cell = 0;

	if (party == NULL)
	{
		return LPA_FAILURE;
	}

	if (index < 0 || index >(party->num_fragments * party->fragment_length - 1))
	{
		return LPA_FAILURE;
	}

	frag = index / party->fragment_length;

	cell = index - (party->fragment_length * frag);

	if (party->fragments[frag] == NULL || party->fragments[frag][cell] == UNUSED)
	{
		return LPA_FAILURE;
	}

	printf("%d\n", party->fragments[frag][cell]);
	return LPA_SUCCESS;
}

//Resets the array back to when it was first created
LonelyPartyArray *resetLonelyPartyArray(LonelyPartyArray *party)
{
	int i;

	if (party == NULL)
	{
		printf("-> Bloop! NULL pointer detected in resetLonelyPartyArray().\n");
		return party;
	}

	for (i = 0; i < party->num_fragments; i++)
	{
		if (party->fragments[i] != NULL)
		{
			free(party->fragments[i]);
		}
		party->fragments[i] = NULL;
	}

	check_fragments(party);
	check_size(party);

	printf("-> The LonelyPartyArray has returned to its nascent state. (capacity: %d, fragments: %d)\n", party->num_fragments * party->fragment_length, party->num_fragments);

	return party;
}

//Returns the number of non-UNUSED integers in the
//entire array
int getSize(LonelyPartyArray *party)
{
	if (party == NULL)
	{
		return -1;
	}

	return party->size;
}

//Returns the number of integers that the array can
//store altogether
int getCapacity(LonelyPartyArray *party)
{
	if (party == NULL)
	{
		return -1;
	}

	return party->num_fragments * party->fragment_length;
}

//Returns the number of non-NULL fragment cells in
//the array
int getAllocatedCellCount(LonelyPartyArray *party)
{
	int i;
	int j;
	int x = 0;

	if (party == NULL)
	{
		return -1;
	}

	for (i = 0; i < party->num_fragments; i++)
	{
		if (party->fragments[i] != NULL)
		{
			for (j = 0; j < party->fragment_length; j++)
			{
				x++;
			}
		}
	}

	return x;
}

//Returns the size the array would be if all possible
//fragment cells were allocated at once
long long unsigned int getArraySizeInBytes(LonelyPartyArray *party)
{
	return (party->num_fragments * party->fragment_length) * sizeof(int);
}

//Returns the size of the actual LonelyPartyArray
long long unsigned int getCurrentSizeInBytes(LonelyPartyArray *party)
{
	long long unsigned int x = 0;
	int i;
	int j;

	if (party == NULL)
	{
		return 0;
	}

	for (i = 0; i < party->num_fragments; i++)
	{
		x += sizeof(party->fragments[i]);
		x += sizeof(party->fragment_sizes[i]);

		if (party->fragments[i] != NULL)
		{
			for (j = 0; j < party->fragment_length; j++)
			{
				x += sizeof(party->fragments[i][j]);
			}
		}
	}

	x += sizeof(LPA*);
	x += sizeof(LPA);

	return x;
}

//Checks the number of dynamically allocated
//array fragments
void check_fragments(LonelyPartyArray *party)
{
	int i;

	if (party == NULL)
	{
		return;
	}

	party->num_active_fragments = 0;

	for (i = 0; i < party->num_fragments; i++)
	{
		if (party->fragments[i] != NULL)
		{
			party->num_active_fragments++;
		}
	}
}

//Checks the number of non-NULL fragment cells in
//the array and the number of non-UNUSED cells in
//each fragment
void check_size(LonelyPartyArray *party)
{
	int i;
	int j;

	if (party == NULL)
	{
		return;
	}

	party->size = 0;

	for (i = 0; i < party->num_fragments; i++)
	{
		party->fragment_sizes[i] = 0;

		if (party->fragments[i] != NULL)
		{
			for (j = 0; j < party->fragment_length; j++)
			{
				if (party->fragments[i][j] != UNUSED)
				{
					party->size++;
					party->fragment_sizes[i]++;
				}
			}
		}
	}
}

double difficultyRating(void)
{
	return 3.0;
}

double hoursSpent(void)
{
	return 50.0;
}