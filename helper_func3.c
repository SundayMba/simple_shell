#include "shell.h"

/**
 * handle_path - resolve path
 * @tokens: pointer to array of tokens
 * @filename: filename of execuation file
 * @env: environment
 * Return: void
 */

void handle_path(char **tokens, char *filename, char **env)
{
	struct stat status;
	char *path;
	static int n = 1;

	/* check if the command file path is valid */
	if (stat(tokens[0], &status) == 0)
	{
		handle_execution(tokens, filename, env);
		free_memory(tokens);
	}
	else
	{
		path = build_full_path(tokens[0], env);
		if (path == NULL)
			handle_error(filename, tokens[0], n);
		else
		{
			free(tokens[0]);
			tokens[0] = path;
			handle_execution(tokens, filename, env);
		}
		if (!isatty(STDIN_FILENO))
			n++;
		free_memory(tokens);
	}
}

/**
 * build_full_path - construct a full path to a given command with env
 * @cmd: command
 * @env: environment
 * Return: path
 */

char *build_full_path(char *cmd, char **env)
{
	char *var, *path, *sep;
	int len, size, res;
	char **paths, **tmp;
	struct stat status;

	len = 4;
	sep = ":";
	res = 1;
	for (var = *env; var; var = *(++env))
	{
		path = strnstr(var, "PATH", len);
		if (path != NULL)
			if (*(path + len) == '=')
				break;
	}
	/* move to starting location of the path */
	path += 5;
	paths = tokenize_buffer(path, sep);
	path = NULL;
	tmp = paths;
	while (*paths)
	{
		size = strlen(*paths) + strlen(cmd);
		path = malloc(sizeof(char) * (size + 2));
		if (path == NULL)
			break;
		strcpy(path, *paths);
		strcat(path, "/");
		strcat(path, cmd);
		res = stat(path, &status);
		if (res == 0)
			break;
		free(path);
		paths++;
	}
	free_memory(tmp);
	if (res == 0)
		return (path);
	return (NULL);
}
