#include "shell.h"

/**
 * prompt_user - prompt user to input data from commandline
 * Return: void
 */

void prompt_user(void)
{
	char *message;

	message = "($) ";
	write(STDOUT_FILENO, message, strlen(message));
}

/**
 * tokenize_buffer - tokenize a string of character
 * @buffer: a string of characters rep. user commands
 * @sep: seperation
 * Return: pointer to a pointer to a char
 */

char **tokenize_buffer(char *buffer, char *sep)
{
	char **token_array;
	char *token;
	int token_count;

	token = NULL;
	token_count = get_N_token(buffer, sep);
	/*printf("token_count before: %d\n", token_count);*/
	/* check if no token or failure occur */
	if (token_count <= 0)
		return (NULL);
	/*printf("token_count after: %d\n", token_count);*/

	/* allocate memory for the token array */
	token_array = malloc(sizeof(char *) * (token_count + 1));

	/* validate memory allocation */
	if (token_array == NULL)
		return NULL;
	token = strtok(buffer, sep);
	token_count = 0;
	while (token != NULL)
	{
		/* make a copy of the token since it will be modified */
		token_array[token_count] = strdup(token);
		token_count++;
		/*printf("token inside: %s\n", token);*/
		token = strtok(NULL, sep);
	}
	token_array[token_count] = NULL;
	return (token_array);
}

/**
 * get_N_token - get total number of tokens
 * @buffer: string buffer
 * @sep: seperator
 * Return: integer representing total number of tokens
 */

int get_N_token(char *buffer, char *sep)
{
	char *buff_cpy, *token;
	int token_count = 0;

	/* duplicate the buffer memory */
	buff_cpy = strdup(buffer);
	if (buff_cpy == NULL)
		return (-1);
	token = strtok(buff_cpy, sep);
	while (token != NULL)
	{
		token_count++;
		token = strtok(NULL, sep);
	}
	free(buff_cpy);
	return (token_count);
}
