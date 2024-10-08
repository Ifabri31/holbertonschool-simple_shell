#include "main.h"

#define DELIM " \t\n\r"
/**
 *
 */
void free_argv(char **pepe)
{
	int i = 0;

	if (pepe == NULL)
		return;
	while (pepe[i] != NULL)
	{
		free(pepe[i]);
		i++;
	}
	free(pepe);
}

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
	{
		free(copy);
		return (NULL);
	}
	args = malloc((num_tok + 1) * sizeof(char *));
	if (!args)
	{
		free(copy);
		free(args);
		return (NULL);
	}
	tok = strtok(copy, DELIM);
	while (tok != NULL)
	{
		args[i] = strdup(tok);
		if (args[i] == NULL)
		{
			for (; i >= 0; i--)
				free(args[i]);
			free(args);
			free(copy);
			return (NULL);
		}
		tok = strtok(NULL, DELIM);
		i++;
	}
	args[i] = NULL;
	free(copy);
	return (args);
}

/**
 * command_in_shell - execute the commands in shell
 * @line: input command line
 * @envp: Environment variables
 * Return: 0
 */
int command_in_shell(char *line)
{
	char *command_path, **argv;
	pid_t child;
	int status;
	int flag  = 0;

	argv = tokenizar(line);
	if (argv == NULL)
		return (-1);

	command_path = command_in_path(argv[0], &flag);
	if (command_path == NULL)
	{
		free_argv(argv);
		return (-1);
	}
	if (flag == 1)
		free(argv[0]);
	argv[0] = command_path;
	child = fork();
	if (child < 0)
	{
		free_argv(argv);
		free(command_path);
		return (-1);
	}
	else if (child == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			perror("execve");
			_exit(EXIT_FAILURE);
		}
	}
	else
		wait(&status);

	free_argv(argv);
	return (0);
}

/**
 * main - the program
 * Return: 0 on success
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int _isatty = isatty(STDIN_FILENO);

	while (1)
	{
		if (_isatty)
			printf("$ ");

		read = getline(&line, &len, stdin);

		if (read == -1)
			break;

		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		if (command_in_shell(line) == -1)
		{
			perror("error");
			continue;
		}

	}
	free(line);
	return (0);
}
