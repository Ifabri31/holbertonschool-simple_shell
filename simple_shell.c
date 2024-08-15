#include "main.h"
/**
 *
 */

extern char **environ;
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char *pathname;
	char **argv;
	pid_t child;
	int status;

	while (1)
	{
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


