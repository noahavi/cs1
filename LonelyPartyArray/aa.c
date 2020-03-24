#include <stdio.h>
#include <stdlib.h>
#include "LonelyPartyArray.h"

// defining my own functions before calling them in assignment functions
int validIndex(LPA *party, int index)
{
     // index is considered valid if it falls on range
     // 0 through (num_fragments * fragment_length -1)
     int max = party->num_fragments * party->fragment_length -1;

     if(index >= 0 && index <= max)
          return 1;

     return 0;
}

int validParty(LPA *party)
{
     if(party == NULL)
          return 0;

     return 1;

}

LPA* createLonelyPartyArray(int num_fragments, int fragment_length)
{

     // Check for bad input
     if(num_fragments <= 0 || fragment_length <= 0)
          return NULL;


     // Allocate and check if successful
     LPA *party = malloc(sizeof(LonelyPartyArray));
     if(validParty(party) == 0)
          return 0;

     // initialize members
     party->num_fragments = num_fragments;
     party->fragment_length = fragment_length;
     party->size = 0;

     // sizeof(int*) because it's an array pointing to int arrays
     if(!(party->fragments = malloc(sizeof(int*) * num_fragments)))
     {
          destroyLonelyPartyArray(party);
          return NULL;
     }

     // normal int array
     if(!(party->fragment_sizes = malloc(sizeof(int) * num_fragments)))
     {
          destroyLonelyPartyArray(party);
          return NULL;
     }

      // Initialize values to NULL and 0
     for(int i = 0; i < num_fragments; i++)
     {
          party->fragments[i] = NULL;
          party->fragment_sizes[i] = 0;
     }

    // capacity is the number of integers that this LPA can contain (num_fragments X fragment_length)
    printf("-> A new LonelyPartyArray has emerged from the void.");
    printf(" (capacity: %d, fragments: %d)\n", num_fragments*fragment_length, num_fragments);

    return party;
}

LPA* destroyLonelyPartyArray(LPA *party)
{
     int i = 0;

     if(validParty(party) == 0)
          return NULL;

     // check if each fragment has been malloc'd, then free
     for(i = 0; i < party->num_fragments; i++)
          if(party->fragments[i])
               free(party->fragments[i]);

     if(party->fragments != NULL)
     {
          free(party->fragments);
          party->fragments = NULL;
     }

     if(party->fragment_sizes)
     {
          free(party->fragment_sizes);
          party->fragment_sizes = NULL;
     }

     free(party);

     printf("-> The LonelyPartyArray has returned to the void.\n");

     return NULL;
}

int set(LPA *party, int index, int key)
{
     int i, fragX, fragY, fragMin, fragMax;

     if(validParty(party) == 0)
     {
          printf("-> Bloop! NULL pointer detected in set().\n");
          return LPA_FAILURE;
     }
     // Separate place values of indexes using division and modulo
     fragX = index / party->fragment_length;
     fragY = index % party->fragment_length;

     // Find range
     fragMin = fragX * party->fragment_length;
     fragMax = fragMin + party->fragment_length -1;

     if(validIndex(party, index) == 0)
     {
          printf("-> Bloop! Invalid access in set(). (index: %d, fragment: %d, offset: %d)\n", index, fragX, fragY);
          return LPA_FAILURE;
     }

     // If fragment does not exist yet
     if (party->fragments[fragX] == NULL)
     {
          party->fragments[fragX] = malloc(sizeof(int) * party->fragment_length);
          party->num_active_fragments++;

          for(i = 0; i < party->fragment_length; i++)
          {
               // Initialize to Unused
               party->fragments[fragX][i] = UNUSED;

               // Set key at proper index
               if (i == fragY)
               {
                    party->fragments[fragX][fragY] = key;
                    party->fragment_sizes[fragX]++;
                    party->size++;
               }
          }

          printf("-> Spawned fragment %d. (capacity: %d, indices: %d..%d)\n", fragX, party->fragment_length, fragMin, fragMax);
     }
     else if(party->fragments[fragX] != NULL)
     {
          // If fragment exists but index is unused
          if(party->fragments[fragX][fragY] == UNUSED)
          {
               party->fragments[fragX][fragY] = key;
               party->fragment_sizes[fragX]++;
               party->size++;
          }
          else
          {
               // if fragment exists and index has been accounted for
               party->fragments[fragX][fragY] = key;
          }
     }
     return LPA_SUCCESS;
}

int get(LPA *party, int index)
{
     int fragX, fragY;

     if(validParty(party) == 0)
     {
          printf("-> Bloop! NULL pointer detected in get().\n");
          return LPA_FAILURE;
     }

     fragX = index / party->fragment_length;
     fragY = index % party->fragment_length;

     // If index is out of bounds
     if(validIndex(party, index) == 0)
     {
          printf("-> Bloop! Invalid access in get(). (index: %d, fragment: %d, offset: %d)\n", index, fragX, fragY);
          return LPA_FAILURE;
     }

     // Still a valid index, but not being used
     if(party->fragments[fragX] == NULL)
     {
          return UNUSED;
     }

     // If valid index
     if (party->fragments[fragX][fragY] != UNUSED && party->fragments[fragX] != NULL)
     {
          return party->fragments[fragX][fragY];
     }

}

int delete(LPA *party, int index)
{
     int fragX, fragY, fragMin, fragMax;

     if(validParty(party) == 0)
     {
          printf("-> Bloop! NULL pointer detected in delete().\n");
          return LPA_FAILURE;
     }

     if(validIndex(party, index) == 0)
     {
          printf("-> Bloop! Invalid access in delete(). (index: %d, fragment: %d, offset: %d)\n", index, index/party->fragment_length, index%party->fragment_length);
          return LPA_FAILURE;
     }

     fragX = index / party->fragment_length;
     fragY = index % party->fragment_length;
     fragMin = fragX * party->fragment_length;
     fragMax = fragMin + party->fragment_length - 1;

     if(party->fragments[fragX] != NULL)
     {
          if(party->fragments[fragX][fragY] == UNUSED)
          {
               return LPA_FAILURE;
          }
          // if index is being used, set to unused
          if(party->fragments[fragX][fragY] != UNUSED)
          {
               party->fragments[fragX][fragY] = UNUSED;
               party->size--;
               party->fragment_sizes[fragX]--;
          }
     }

     if(party->fragments[fragX] == NULL)
          return LPA_FAILURE;

     // if fragment is now empty, deallocate
     if(party->fragment_sizes[fragX] == 0)
     {
          free(party->fragments[fragX]);
          party->fragments[fragX] = NULL;
          party->num_active_fragments--;
          printf("-> Deallocated fragment %d. (capacity: %d, indices: %d..%d)\n", fragX, party->fragment_length, fragMin, fragMax);
     }

     return LPA_SUCCESS;
}

int containsKey(LPA *party, int key)
{
     if(party == NULL)
          return 0;

     // linear search through fragments
     for(int i = 0; i < party->num_fragments; i++)
          if(party->fragments[i])
               for(int j = 0; j < party->fragment_length; j++)
                    if(party->fragments[i][j] == key)
                         return 1;

     // if search fails
     return 0;
}

int printIfValid(LPA *party, int index)
{
     int fragX, fragY;
     // similar to get() function
     // print the value stored at the index

     if(validParty(party) == 0)
          return LPA_FAILURE;

     if(validIndex(party, index) == 0)
          return LPA_FAILURE;

     fragX = index / party->fragment_length;
     fragY = index % party->fragment_length;

     if(party->fragments[fragX] == NULL)
     {
          return LPA_FAILURE;
     }

     if (party->fragments[fragX][fragY] != UNUSED && party->fragments[fragX] != NULL)
     {

          printf("%d\n", party->fragments[fragX][fragY]);
          return LPA_SUCCESS;
     }

     return LPA_FAILURE;
}

LPA *resetLonelyPartyArray(LPA *party)
{
     int i;

     if(validParty(party) == 0)
     {
          printf("-> Bloop! NULL pointer detected in resetLonelyPartyArray().\n");
     }
     else
     {
          // free fragments
          for(i = 0; i < party->num_fragments; i++)
          {
               free(party->fragments[i]);
               party->fragments[i] = NULL;
               party->fragment_sizes[i] = 0;
          }
          party->num_active_fragments = 0;
          party->size = 0;
          printf("-> The LonelyPartyArray has returned to its nascent state. (capacity: %d, fragments: %d)\n", party->num_fragments * party->fragment_length, party->num_fragments);
     }
     return party;
}

int getCapacity(LPA *party)
{
     if(party)
     {
          return party->num_fragments * party->fragment_length;
     }
     else
     {
          return -1;
     }
}

int getSize(LPA *party)
{
     if(validParty(party) == 0)
          return -1;
     return party->size;
}

int getAllocatedCellCount(LPA *party)
{
     if(party)
     {
          return party->num_active_fragments * party->fragment_length;
     }
     else
     {
          return -1;
     }
}

long long unsigned int getArraySizeInBytes(LPA *party)
{
     if(party)
     {
          return party->num_fragments * party->fragment_length * sizeof(int);
     }
     else
     {
          return -1;
     }
}

long long unsigned int getCurrentSizeInBytes(LPA *party)
{
     long long unsigned int sum = 0;
     if(party != NULL)
     {
          sum += sizeof(LPA*);
          sum += sizeof(LPA);

          for(int i = 0; i < party->num_fragments; i++)
          {
               sum += sizeof(int*);
               sum += sizeof(int);
               if(party->fragments[i] != NULL)
               {
                    for(int k = 0; k < party->fragment_length; k ++)
                    {
                         sum += sizeof(int);
                    }

               }

          }
     }
     return sum;

}
