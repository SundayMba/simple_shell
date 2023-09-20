#include "shell.h"

/**
 * handle_execution - create and execute process and handle error on process.
 * @tokens: list of commands and argument to execute
 * @filename: name of the execution file
 * @env: environment pointer
 * @code: status code
 * Return: error code
 */

int handle_execution(char **tokens, char *filename, char **env, int *code)
{
	pid_t pid;
	static int n = 1;
	int status = 0;

	/* create a child process */
	pid = fork();
	/* check for error during creation */
	if (pid < 0)
		*code = -1;
	/* check for successful child creation */
	else if (pid == 0)
	{
		/* check if command was executed successfully */
		if (execve(tokens[0], tokens, env) == -1)
		{
			if (isatty(STDIN_FILENO))
				perror(filename);
			else
				handle_error(filename, tokens[0], n);
			free_memory(tokens);
			free_memory(env);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* wait for the child to terminate */
		wait(&status);
		if (!isatty(STDIN_FILENO))
			n++;
		/* error occurred during child process */
		if (status > 0)
			*code = FILE_NOT_EXIST;
		else
			*code = status;
	}
	return (*code);
}

/**
 * handle_error - print error message
 * @filename: execution file name
 * @arg: argument
 * @n: number of times a child process fail to execute a command
 * Return: void
 */

void handle_error(char *filename, char *arg, int n)
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
	strcat(error, arg);
	strcat(error, ": ");
	strcat(error, "not found\n");
	write(STDERR_FILENO, error, strlen(error));
	free(count_str);
}

/**
 * int_to_str - convert int to string
 * @count: integer to convert
 * Return: pointer to char array rep. converted integer
 */

char *int_to_str(int count)
{
	int num, temp, rem;
	char *ptr;

	num = 0;
	temp = count;
	while ((temp / 10) > 0)
	{
		temp /= 10;
		num++;
	}
	num++;

	ptr = malloc(sizeof(char) * (num + 1));
	if (ptr == NULL)
		return (NULL);
	ptr += num;
	*ptr = '\0';
	ptr--;
	while ((count / 10) != 0)
	{
		rem = count % 10;
		*ptr-- = rem + 48;
		count /= 10;
	}
	rem = count % 10;
	*ptr = rem + 48;
	return (ptr);
}

/**
 * print_env_error - print environment error
 * @file: filename of the process
 * @msg: message to display
 * Return: void
 */

void print_env_error(char *file, char *msg)
{
	write(STDERR_FILENO, file, _strlen(file));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, msg, _strlen(msg));
	write(STDERR_FILENO, "\n", 1);
}
