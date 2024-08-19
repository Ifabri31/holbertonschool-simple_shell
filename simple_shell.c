#include "main.h"

#define DELIM " \t\n"

char count_tok(char *line)
{
	int count = 0;
	char *token;

	token = strtok(line, DELIM);
	while (token)
	{
		count++;
		token = strtok(NULL, DELIM);
	}
	return(count);
}

char **tokenizar(char *command)
{
	int i = 0;
	int num_tok;
	char *tok;
	char **args;
	char *copy;

	copy = strdup(command);
	num_tok = count_tok(command);
	args = malloc((num_tok + 1) * sizeof(char*));
	if (!args)
	{
		free(args);
		return (NULL);
	}
	tok = strtok(copy, DELIM);
	while (tok != NULL)
	{
		args[i] = strdup(tok);
		tok = strtok(NULL, DELIM);
		i++;
	}
	args[i] = NULL;
	return(args);
}

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char **argv;
	pid_t child;
	int _isatty = isatty(STDIN_FILENO);
	char *command_path;

	while (1)
	{
		if (_isatty)
			printf("$ ");
		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			return(-1);
			break;
		}
		argv = tokenizar(line);
		if (argv == NULL)
		{
			free(argv);
			break;
		}
		command_path = command_in_path(argv[0]);
		if (command_path == NULL)
			break;
		child = fork();
		if (child < 0)
                {
			free(argv);
			free(line);
			return(-1);
                }
		else if (child == 0)
		{
			if (execve(command_path, argv, NULL) == -1)
			{
				printf("./hsh: No such file or directory\n");
				return(1);
			}
			else
			{
				execve(argv[0], argv, NULL);
				printf("./hsh: No such file or directory\n");
				return(-1);
			}
		}
		else
			wait(&child);
		free(argv);
	}
	free(line);
	return(0);
}
