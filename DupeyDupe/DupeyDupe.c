// Noah Avizemer
// COP 3502, Spring 2019
// no886776
#include "DupeyDupe.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	int i, j, dupe, dupe_amt, dupe_dupe;
	dupe_dupe = 0;
	int found_dupe = 0;
	dupe = 0;
	//dupe_amt to see if there are any dupes
	dupe_amt = 0;
	for (i = argc - 1; i > 0; i--)
	{	
		// starts at end of array and goes up from beginning comparing
		// each string
		for (j = 0; j < argc; j++)
		{
			if (strcmp(argv[i], argv[j]) == 0 && (j != i))
			{
				dupe = 1;
				dupe_amt++;
			}
			else
			{
				dupe = 0;
			}
			// j != i so not comparing same string
			if (dupe == 1 && (j != i))
			{
				printf("%s\n", argv[i]);
				found_dupe = 1;
				break;
			}
		}
		if (found_dupe == 1)
		{
			break;
		}
	}
	// goes through strings to check for 2 dupes right next to each other
	for (i = argc - 1; i > 0; i--)
	{
		// adds to counter if there is dupe
		// goes to 0 if no dupes, when 2 prints
		if (strcmp(argv[i], "dupe") == 0)
		{
			dupe_dupe++;
		}
		else
		{
			dupe_dupe = 0;
		}
		if (dupe_dupe == 2)
		{
			printf("dupe dupe!\n");
			break;
			
		}
	}
	if (dupe_amt == 0)
	{
		printf("no dupey dupe :(\n");
	}
	return 0;
}
double difficultyRating(void)
{
	return 4;
}
double hoursSpent(void)
{
	return 5;
}
