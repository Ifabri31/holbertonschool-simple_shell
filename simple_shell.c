#include "main.h"

#define DELIM " \t\n"

/**
 * count_tok - contador de tokens para memoria
 * line: linea para tokenizar
 *
 * Return: cantidad de tokens
 */
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
	return (count);
}

/**
 * tokenizar - ahora si tokenizamos la entrada
 * command: commandos a tokenizar
 *
 * Return: un array de argumentos
 */
char **tokenizar(char *command)
{
	int i = 0;
	int num_tok;
	char *tok;
	char **args;
	char *copy;

	copy = strdup(command);
	num_tok = count_tok(command);
	if (num_tok == 0)
		return (NULL);
	args = malloc((num_tok + 1) * sizeof(char *));
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
	return (args);
}

/**
 * main - the program
 *
 * Return: 0 on success
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char **argv;
	pid_t child;
	int status;
	int _isatty = isatty(STDIN_FILENO);
	char *command_path;
	char *envp[] = { "PATH=/usr/bin:/bin", NULL};

	while (1)
	{
		if (_isatty)
			printf("$ ");
		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			free(line);
			return (-1);
		}
		argv = tokenizar(line);
		if (argv == NULL)
		{
			free(argv);
			continue;
		}
		command_path = command_in_path(argv[0]);
		if (command_path == NULL)
		{
			free(argv);
			continue;
		}
		child = fork();
		if (child < 0)
		{
			free(argv);
			free(line);
			return (-1);
		}
		else if (child == 0)
		{
			if (execve(command_path, argv, envp) == -1)
			{
				perror("execve");
				_exit(EXIT_FAILURE);
			}
		}
		else
			wait(&status);
		free(argv);
	}
	free(line);
	return (0);
}
