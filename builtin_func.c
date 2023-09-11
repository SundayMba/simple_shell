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
	(void *)file;
	(void *)env;
	(void *)n;
	free_memory(tk);
	exit(*n);
}
