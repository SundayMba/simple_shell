#include "shell.h"

/**
 * handle_exit - handle_exit
 * @tk: tokens
 * @file: filename
 * @env: environment
 * @n: status code
 * Return: 0 - success
 */

int handle_exit(char **tk, char *file, char **env, int *n)
{
	int status_code;
	(void)file;
	(void)env;
	(void)n;

	if (tk[1] == NULL)
	{
		free_memory(tk);
		exit(*n);
	}
	status_code = _atoi(tk[1]);
	free_memory(tk);
	*n = status_code;
	exit(*n);
}
