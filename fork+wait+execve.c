#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main (void)
{
	pid_t pid = fork();
	int status;

	if(pid == 0)
	{
		const char *pathname = "/bin/ls";
		char *const argv[] = { "/bin/ls", "-l", "/tmp", NULL };

		execve(pathname, argv, NULL);
	}
	else
	{
		wait(&status);
	}

	return(0);
}
