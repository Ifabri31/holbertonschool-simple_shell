#include "main.h"
/**
 *
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	const char *pathname = "/bin/ls";
	char *const argv[] = {"ls", NULL};
	pid_t child;
	int status;

	while (1)
	{
		printf("$ ");
		read = getline(&line, &len, stdin);
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


