#include "main.h"
#define DELIMS " \t\n\r"
char **token(char *command)
{
	char *token;
	char **args;
	int i = 0;

	args = malloc(sizeof(char *) * 1024);
	if (!args)
	{
		free(args);
		exit(-1);
	}
	token = strtok(command, DELIMS);
	while(token != NULL)
	{
		args[i] = token;
		token = strtok(NULL, DELIMS);
		i++;
	}
	free(args);
	return (args);
}
