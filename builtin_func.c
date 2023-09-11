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
	(void)file;
	(void)env;
	(void)n;

	if (tk[1] == NULL)
	{
		free_memory(tk);
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
