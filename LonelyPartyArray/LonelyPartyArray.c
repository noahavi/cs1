#include <stdio.h>
#include <stdlib.h>
#include "LonelyPartyArray.h"
/*
int main (void)
{
	LPA *p = createLonelyPartyArray (5, 10);
	p->num_fragments = 3;
	printf("%d\n", p->num_fragments);
}
*/

LonelyPartyArray *createLonelyPartyArray(int num_fragments, int fragment_length)
{
	int i;
	LonelyPartyArray *LPA = malloc(sizeof(LonelyPartyArray));
	LPA->num_fragments = num_fragments;
	LPA->fragment_length = fragment_length;
	//LPA->num_active_fragments = 
	//LPA->size = num_fragments * fragment_length;
	//LPA->fragment_sizes = malloc(sizeof())
	LPA->fragments = malloc(sizeof(int *) * num_fragments)
	//return NULL;
}

LonelyPartyArray *destroyLonelyPartyArray(LonelyPartyArray *party)
{
	//return NULL;
}

int set(LonelyPartyArray *party, int index, int key)
{
	//return NULL;
}

int get(LonelyPartyArray *party, int index)
{
	//return NULL;
}

int delete(LonelyPartyArray *party, int index)
{
	//return NULL;
}

int containsKey(LonelyPartyArray *party, int key)
{
	//return NULL;
}

int isSet(LonelyPartyArray *party, int index)
{
	//return NULL;
}

int printIfValid(LonelyPartyArray *party, int index)
{
	//return NULL;
}

LonelyPartyArray *resetLonelyPartyArray(LonelyPartyArray *party)
{
	//return NULL;
}

int getSize(LonelyPartyArray *party)
{
	//return NULL;
}

int getCapacity(LonelyPartyArray *party)
{
	//return NULL;
}

int getAllocatedCellCount(LonelyPartyArray *party)
{
	//return NULL;
}

long long unsigned int getArraySizeInBytes(LonelyPartyArray *party)
{
	//return NULL;
}

long long unsigned int getCurrentSizeInBytes(LonelyPartyArray *party)
{
	//return NULL;
}

double difficultyRating(void)
{
	return 5;
}

double hoursSpent(void)
{
	return 10;
}