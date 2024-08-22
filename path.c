#include"main.h"
/**
 * command_in_path - look for the command in path
 * @command: Command
 * Return: null
 */
char *command_in_path(const char *command)
{
	char *path_env = getenv("PATH");
	char *path, *token, *command_path;
	int command_length, path_length;

	if (!path_env)
		return (NULL);

	path = strdup(path_env);
	if (path == NULL)
		return (NULL);

	command_length = strlen(command);
	token = strtok(path, ":");
	while (token != NULL)
	{
		path_length = strlen(token);
		command_path = malloc(path_length + command_length + 2);
		if (!command_path)
		{
			free(path);
			return (NULL);
		}
		strcpy(command_path, token);
		strcat(command_path, "/");
		strcat(command_path, command);

		if (access(command_path, X_OK) != -1)
		{
			free(path);
			return (command_path);
		}
		free(command_path);
		token = strtok(NULL, ":");
	}
	free(path);
	return (NULL);
}
