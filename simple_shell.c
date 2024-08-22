#include "main.h"

#define DELIM " \t\n\r"

/**
 * count_tok - count tokens
 * @line: line to tokenize
 * Return: number of tokens
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
 * tokenizar - now if we tokenize the input
 * @command: commands to tokenize
 * Return: an array of arguments
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
 * command_in_shell - execute the commands in shell
 * @line: input command line
 * @envp: Environment variables
 * Return: 0
 */
int command_in_shell(char *line, char **envp)
{
	char *command_path, **argv;
	pid_t child;
	int status;

	argv = tokenizar(line);
	if (argv == NULL)
		return (-1);

	command_path = command_in_path(argv[0]);
	if (command_path == NULL)
	{
		free(argv);
		return (-1);
	}

	child = fork();
	if (child < 0)
	{
		free(argv);
		free(command_path);
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
	free(command_path);
	return (0);
}

/**
 * main - the program
 * Return: 0 on success
 */
int main(void)
{
	char *line = NULL, *envp[] = { "PATH=/usr/bin:/bin", NULL};
	size_t len = 0;
	ssize_t read;
	int _isatty = isatty(STDIN_FILENO);

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

		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		if (command_in_shell(line, envp) == -1)
			continue;

	}
	free(line);
	return (0);
}
