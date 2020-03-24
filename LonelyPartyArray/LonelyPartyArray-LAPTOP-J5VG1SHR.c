// Noah Avizemer
// COP 3502, Spring 2019
// no886776

#include <stdio.h>
#include <stdlib.h>
#include "LonelyPartyArray.h"

LonelyPartyArray *createLonelyPartyArray(int num_fragments, int fragment_length)
{
	int i;
	int m = num_fragments * fragment_length;
	// Checks if the num_fragments and fragment_length are valid
	if (num_fragments <= 0 || fragment_length <= 0)
	{
		return NULL;
	}
	// Creates the struct pointer, allocates memory, and sets the members
	// to the appropriate values
	LonelyPartyArray *LPA;
	LPA = malloc(sizeof(LonelyPartyArray));
	LPA->num_fragments = num_fragments;
	LPA->fragment_length = fragment_length;
	LPA->num_active_fragments = 0;
	LPA->size = 0;
	LPA->fragment_sizes = malloc(sizeof(int) * num_fragments);
	LPA->fragments = malloc(sizeof(int*) * num_fragments);
	for (i = 0; i < num_fragments; i++)
	{
		LPA->fragment_sizes[i] = 0;
	}
	for (i = 0; i < num_fragments; i++)
	{
		LPA->fragments[i] = NULL;
	}

	if (LPA->fragment_sizes == NULL)
	{
		free(LPA);
		return NULL;
	}
	if (LPA->fragments == NULL)
	{
		free(LPA);
		return NULL;
	}

	if (LPA == NULL)
	{
		free(LPA);
		return NULL;
	}
	printf("-> A new LonelyPartyArray has emerged from the void." 
		" (capacity: %d, fragments: %d)\n", m, num_fragments);
	return LPA;
}
// Frees all memory allocated for the LPA
LonelyPartyArray *destroyLonelyPartyArray(LonelyPartyArray *party)
{
	int i;
	for (i = 0; i < party->num_fragments; i++)
	{
		free(party->fragments[i]);
	}
	free(party->fragment_sizes);
	free(party->fragments);
	free(party);
	printf("-> The LonelyPartyArray has returned to the void.\n");
	return NULL;
}
// Puts the key in the correct index of the fragment
int set(LonelyPartyArray *party, int index, int key)
{
	int i;
	int frag_number;
	int frag_index;
	if (party == NULL)
	{
		printf("-> Bloop! NULL pointer detected in set().\n");
		return LPA_FAILURE;
	}
	frag_number = index / (party->fragment_length);
	frag_index =  index % (party->fragment_length);
	// Checks if index is in bounds
	if (index > (party->fragment_length * party->num_fragments) - 1 || index < 0)
	{
		printf("-> Bloop! Invalid access in set(). (index: %d, fragment: %d," 
			" offset: %d)\n", index, frag_number, frag_index);
		return LPA_FAILURE;
	}
	// Allocates memory for the fragment if not already done
	// Sets the cells to UNUSED
	if (party->fragments[frag_number] == NULL)
	{
		party->fragments[frag_number] = malloc(sizeof(int) * party->fragment_length);
		party->num_active_fragments++;
		printf("-> Spawned fragment %d. (capacity: %d, indices: %d..%d)\n", frag_number, party->fragment_length, 
		party->fragment_length * frag_number, (party->fragment_length * frag_number) + party->fragment_length - 1);
		
		for (i = 0; i < party->fragment_length; i++)
		{
			party->fragments[frag_number][i] = UNUSED;
		}
		// Updates the members of the struct when key is added
	}
	if (party->fragments[frag_number][frag_index] == UNUSED)
		{
			party->fragments[frag_number][frag_index] = key;
			party->fragment_sizes[frag_number]++; 
			party->size++;
		}
	// Changing existing key
	else
	{
		party->fragments[frag_number][frag_index] = key;
		return LPA_SUCCESS;
	}
	party->fragments[frag_number][frag_index] = key;
	return LPA_SUCCESS;
	
}

// Gets the value at the index
int get(LonelyPartyArray *party, int index)
{
	int frag_number;
	int frag_index;
	if (party == NULL)
	{
		printf("-> Bloop! NULL pointer detected in get().\n");
		return LPA_FAILURE;
	}
	frag_number = index / (party->fragment_length);
	frag_index =  index % (party->fragment_length);
	// Checks if the index is valid
	if (index > (party->fragment_length * party->num_fragments) - 1 || index < 0)
	{
		printf("-> Bloop! Invalid access in get(). (index: %d," 
			" fragment: %d, offset: %d)\n", index, frag_number, frag_index);
		return LPA_FAILURE;
	}
	if (party->fragments[frag_number] == NULL)
	{
		return UNUSED;
	}
	return party->fragments[frag_number][frag_index]; 

}

int delete(LonelyPartyArray *party, int index)
{
	int frag_number;
	int frag_index;
	if (party == NULL)
	{
		printf("-> Bloop! NULL pointer detected in delete().\n");
		return LPA_FAILURE;
	}
	frag_number = index / (party->fragment_length);
	frag_index =  index % (party->fragment_length);
	// Checks if index is in bounds
	if (index > (party->fragment_length * party->num_fragments) - 1 || index < 0)
	{
		printf("-> Bloop! Invalid access in delete(). (index: %d, fragment: %d, offset: %d)\n", index, frag_number, frag_index);
		return LPA_FAILURE;
	}
	if (party->fragments[frag_number] == NULL)
	{
		return LPA_FAILURE;
	}
	// Checks if the value is UNUSED
	if (party->fragments[frag_number][frag_index] == UNUSED)
	{
		return LPA_FAILURE;
	}
	// Sets the value to UNUSED and adjusts the size and fragment size accordingly
	if (party->fragments[frag_number][frag_index] != UNUSED)
	{
		party->fragments[frag_number][frag_index] = UNUSED;
		party->fragment_sizes[frag_number]--;
		party->size--;
		// Deallocates the fragment
	}
	if (party->fragment_sizes[frag_number] == 0)
		{
			free(party->fragments[frag_number]);
			party->fragments[frag_number] == NULL;
			printf("%p\n", party->fragments[1]);
			party->num_active_fragments--;
			printf("-> Deallocated fragment %d. (capacity: %d, indices: %d..%d)\n", frag_number, party->fragment_length,
				party->fragment_length * frag_number, (party->fragment_length * frag_number)+party->fragment_length - 1);
			//return LPA_SUCCESS;
		}
	else
	{
		party->fragments[frag_number][frag_index] = UNUSED;
	}
	return LPA_SUCCESS;

}

int containsKey(LonelyPartyArray *party, int key)
{
	int i, j;
	if (party == NULL)
	{
		return 0;
	}
	// Checks each element of fragments to see if key is there
	for (i = 0; i < party->num_fragments; i++)
	{
		for (j = 0; j < party->fragment_length; j++)
		{
			if (key == party->fragments[i][j])
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
}

int isSet(LonelyPartyArray *party, int index)
{
	int frag_number;
	int frag_index;
	if (party == NULL)
	{
		return 0;
	}
	if (party->fragments[frag_number] == NULL)
	{
		return 0;
	}
	frag_number = index / (party->fragment_length);
	frag_index =  index % (party->fragment_length);
	// Checks if index is in bounds
	if (index > (party->fragment_length * party->num_fragments) - 1 || index < 0)
	{
		return 0;
	}
	// Checks if the value is UNUSED
	if (party->fragments[frag_number][frag_index] == UNUSED)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int printIfValid(LonelyPartyArray *party, int index)
{
	int frag_number;
	int frag_index;
	if (party == NULL)
	{
		return LPA_FAILURE;
	}
	frag_number = index / (party->fragment_length);
	frag_index =  index % (party->fragment_length);

	// Checks if index is in bounds
	if (index > (party->fragment_length * party->num_fragments) - 1 || index < 0)
	{
		return LPA_FAILURE;
	}
	
	if (party->fragments[frag_number] == NULL)
	{
		return LPA_FAILURE;
	}
	
	// Checks if UNUSED
	if (party->fragments[frag_number][frag_index] == UNUSED)
	{
		return LPA_FAILURE;
	}
	// Otherwises prints the value
	else
	{
		printf("%d\n", party->fragments[frag_number][frag_index]);
		return LPA_SUCCESS;
	}

}

LonelyPartyArray *resetLonelyPartyArray(LonelyPartyArray *party)
{
	int i;
	if (party == NULL)
	{
		printf("-> Bloop! NULL pointer detected in resetLonelyPartyArray().\n");
		return 0;
	}
	// Resets size and num_active_frags
	party->size = 0;
	party->num_active_fragments = 0;
	// Resets all cells of fragment_sizes
	for (i = 0; i < party->num_fragments; i++)
	{
		party->fragment_sizes[i] = 0;
	}
	for (i = 0; i < party->num_fragments; i++)
	{
		free(party->fragments[i]);
		party->fragments[i] = NULL;
	}
	printf("-> The LonelyPartyArray has returned to its nascent state. (capacity: %d,"
		" fragments: %d)\n", party->num_fragments * party->fragment_length, party->num_fragments);
	return party;
}

int getSize(LonelyPartyArray *party)
{
	if (party == NULL)
	{
		return -1;
	}
	return party->size;
}

int getCapacity(LonelyPartyArray *party)
{
	if (party == NULL)
	{
		return -1;
	}
	return party->num_fragments * party->fragment_length;
}

int getAllocatedCellCount(LonelyPartyArray *party)
{
	if (party == NULL)
	{
		return -1;
	}
	return party->num_active_fragments * party->fragment_length;
}

long long unsigned int getArraySizeInBytes(LonelyPartyArray *party)
{
	if (party == NULL)
	{
		return 0;
	}
	return getCapacity(party) * sizeof(int);
}

long long unsigned int getCurrentSizeInBytes(LonelyPartyArray *party)
{
	int i, j;
	int fragment = 0;
	int frag_size = 0;
	int active_frags = 0;
	if (party == NULL)
	{
		return 0;
	}
	// Adds up the size of fragment and fragment_sizes
	for (i = 0; i < party->num_fragments; i++)
	{
		fragment += sizeof(party->fragments[i]);
		frag_size += sizeof(party->fragment_sizes[i]);
	}
	// Adds up active fragments size
	for (i = 0; i < party->num_fragments; i++)
	{
		if (party->fragments[i] != NULL)
		{
			for (j = 0; j < party->fragment_length; j++)
			{
				active_frags += sizeof(party->fragments[i][j]);
			}
		}
	}
	
	return (sizeof(LPA*) + sizeof(LPA) + fragment + frag_size + active_frags);
}

double difficultyRating(void)
{
	return 5;
}

double hoursSpent(void)
{
	return 10;
}
