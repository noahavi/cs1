#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void stripPunctuators(char *str)
{
	int i, j;
	int len = strlen(str);
	char buffer[1024];
	for (i = 0, j = 0; i < len; i++)
	{
		if (!ispunct(str[i]))
		{
			buffer[j] = str[i];
			j++;
		}
	}
	strcpy(str, buffer);
}

int main(void)
{
	char *str = malloc(sizeof(char) * 10);
	strcpy(str, "dodof.,.sd");
	printf("%s\n", str);
	stripPunctuators(str);
	printf("%s\n", str);
}