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
	static int error_num = 1;
	(void)env;

	if (tk[1] == NULL)
	{
		free_memory(tk);
		free_memory(environ);
		exit(*n);
	}
	status_code = _atoi(tk[1]);
	if (status_code < 0)
	{
		handle_exit_error(file, tk, error_num, "Illegal number");
		error_num++;
		*n = ILLEGAL_NUMBER;
	}
	else
		*n = status_code;
	free_memory(tk);
	free_memory(environ);
	exit(*n);
}

/**
 * handle_exit_error - print error message
 * @filename: execution file name
 * @tk: argument
 * @msg: message to display
 * @n: number of times a child process fail to execute a command
 * Return: void
 */

void handle_exit_error(char *filename, char **tk, int n, char *msg)
{
	char error[100];
	char *count_str;

	strcpy(error, filename);
	strcat(error, ": ");
	count_str = int_to_str(n);
	if (count_str == NULL)
		count_str = "1";
	strcat(error, count_str);
	/* check if operating in non interactive mode */
	strcat(error, ": ");
	strcat(error, tk[0]);
	strcat(error, ": ");
	strcat(error, msg);
	strcat(error, ": ");
	strcat(error, tk[1]);
	strcat(error, "\n");
	write(STDERR_FILENO, error, strlen(error));
	free(count_str);
}

/**
 * handle_env - handle environment
 * @tk: tokens
 * @file: filename
 * @env: environment
 * @n: status code
 * Return: 0 - success
 */

int handle_env(char **tk, char *file, char **env, int *n)
{
	int len, i;
	(void)env;

	for (i = 0; environ[i]; i++)
	{
		len = strlen(environ[i]);
		if (write(STDOUT_FILENO, environ[i], len) == -1)
		{
			*n = -1;
			perror(file);
			free_memory(tk);
			return (*n);
		}
		write(STDOUT_FILENO, "\n", 1);
	}
	*n = 0;
	free_memory(tk);
	return (0);
}

/**
 * handle_setenv - set an environment variable
 * @tk: tokens
 * @file: filename
 * @env: environment
 * @n: status code
 * Return: 0 - success
 */

int handle_setenv(char **tk, char *file, char **env, int *n)
{
	(void)env;

	if (tk[1] == NULL || (tk[1] != NULL && tk[2] == NULL))
	{
		print_env_error(file, "Invalid argument");
		free_memory(tk);
		return (*n);
	}
	if (_setenv(tk[1], tk[2], 1) == -1)
	{
		print_env_error(file, "Invalid argument");
		free_memory(tk);
		*n = -1;
		return (*n);
	}
	free_memory(tk);
	*n = 0;
	return (*n);
}

/**
 * handle_unsetenv - unset an environment variable
 * @tk: tokens
 * @file: filename
 * @env: environment
 * @n: status code
 * Return: 0 - success
 */

int handle_unsetenv(char **tk, char *file, char **env, int *n)
{
	(void)env;

	if (tk[1] == NULL)
	{
		print_env_error(file, "Invalid argument");
		free_memory(tk);
		*n = -1;
		return (*n);
	}
	if (_unsetenv(tk[1]) == -1)
	{
		handle_error(file, tk[0], *n);
		free_memory(tk);
		*n = -1;
		return (*n);
	}
	free_memory(tk);
	*n = 0;
	return (*n);
}
