#include "shell.h"

/**
 * handle_path - resolve path
 * @tokens: pointer to array of tokens
 * @filename: filename of execuation file
 * @env: environment
 * @code: status code
 * Return: error code
 */

int handle_path(char **tokens, char *filename, char **env, int *code)
{
	struct stat status;
	char *path;
	static int n = 1;

	/* check for builtin commands */
	if (builtin_command(tokens, filename, env, code) != NOT_BUILTIN)
	{
		/* free_memory(tokens); */
		return (*code);
	}
	/* check if the command file path is valid */
	else if (stat(tokens[0], &status) == 0)
	{
		*code = handle_execution(tokens, filename, env, code);
		free_memory(tokens);
		return (*code);
	}
	else
	{
		path = build_full_path(tokens[0], env);
		if (path == NULL)
		{
			handle_error(filename, tokens[0], n);
			*code = COMMAND_NOT_EXIST;
		}
		else
		{
			free(tokens[0]);
			tokens[0] = path;
			*code = handle_execution(tokens, filename, env, code);
		}
		if (!isatty(STDIN_FILENO))
			n++;
		free_memory(tokens);
		return (*code);
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
	char *var, *path = NULL, *sep = ":", **paths, **tmp;
	int size, res = 1;
	struct stat status;

	for (var = *env; var; var = *(++env))
	{
		path = _strnstr(var, "PATH=", 5);
		if (path != NULL)
			break;
	}
	if (path == NULL)
		return (NULL);
	path += 5;
	if (path == NULL || *path != '/' || *path == '=')
		return (NULL);
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

/**
 * builtin_command - builtin handler
 * @tokens: tokens array
 * @filename: executable filename
 * @env: environemnt variable
 * @n: return code
 * Return: 0 - success (-2) - not a builtin command
 */

int builtin_command(char **tokens, char *filename, char **env, int *n)
{
	int builtin_len, m, i;
	builtin_cmd builtin[] = {
		{"exit", handle_exit},
		{"env", handle_env},
		{"setenv", handle_setenv},
		{"unsetenv", handle_unsetenv},
		{"cd", handle_cd},
		{NULL, NULL}
	};

	builtin_len = 6;
	for (i = 0; i < builtin_len && builtin[i].cmd != NULL;  i++)
	{
		if (strcmp(builtin[i].cmd, tokens[0]) == 0)
		{
			m = builtin[i].builtin_func(tokens, filename, env, n);
			return (m);
		}
	}
	return (NOT_BUILTIN);
}
