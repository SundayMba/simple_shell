#include "shell.h"

/**
 * handle_cd_error - handle error that occur due to change of directory
 * @filename: filename
 * @tk: token array
 * @n: error code
 * @msg: message to display
 * Return: void
 */

void handle_cd_error(char *filename, char **tk, int n, char *msg)
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
	strcat(error, " ");
	strcat(error, tk[1]);
	strcat(error, "\n");
	write(STDERR_FILENO, error, strlen(error));
	free(count_str);
}
