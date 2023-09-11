#include "shell.h"

/**
 * handle_exit - handle_exit
 * @tk: tokens
 * @file: filename
 * @env: environment
 * @n: return code
 * Return: 0 - success 
 */

int handle_exit(char **tk, char *file, char **env, int *n)
{
	(void *)file;
	(void *)env;
	(void *)n;
	*n = EXIT_SUCCESS;
	free_memory(tk);
	exit(EXIT_SUCCESS);
}
