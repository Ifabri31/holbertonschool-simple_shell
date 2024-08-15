#include "main.h"
/**
 *
 */

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char *pathname;
	char **argv;
	pid_t child;
	int status;
	int _isatty = isatty(STDIN_FILENO);

	while (1)
	{
		if (_isatty)
			printf("$ ");
		read = getline(&line, &len, stdin);
		argv = token(line);
		pathname = argv[0];
		child = fork();
		if (child == -1)
                {
			break;
                }
		if (read == -1)
		{
			break;
		}
		if (child == 0)
			execve(pathname, argv, NULL);
		else
			wait(&status);

	}
	free(line);
	return (0);
}


