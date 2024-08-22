#include"main.h"
char *_getenv(char *data)
{
	extern char **environ;
	char **env = environ;
	size_t len_data = strlen(data);
	size_t len;
	char *DELIM;

	while (*env)
	{
		DELIM = strchr(*env, '=');
		if (DELIM)
			len = DELIM - *env;
		if (len_data == len && strncmp(*env, data, len_data) == 0)
			return (DELIM + 1);
		env++;
	}
	return (NULL);
}
/**
 * command_in_path - look for the command in path
 * @command: Command
 * Return: null
 */
char *command_in_path(char *command)
{
	char *path_env = _getenv("PATH");
	char *path, *token, *command_path;
	int command_length, path_length;

	if (access(command, X_OK) != -1)
		return (command);
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
