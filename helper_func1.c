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
	char *buff_cpy, *buff_tmp, *token;
	int token_count = 0;

	/* duplicate the buffer memory */
	buff_cpy = strdup(buffer);
	buff_tmp = buff_cpy;
	if (buff_cpy == NULL)
		return (-1);
	token = strtok(buff_cpy, sep);
	while (token != NULL)
	{
		token_count++;
		token = strtok(NULL, sep);
	}
	free(buff_tmp);
	return (token_count);
}

/**
 * free_memory - free memory
 * @tokens: array of tokens
 * Return: void
 */

void free_memory(char **tokens)
{
	int count = 0;
	char **tokens_cpy;

	if (tokens == NULL)
		return;
	tokens_cpy = tokens;
	while (*tokens_cpy)
	{
		free(*tokens_cpy);
		tokens_cpy++;
	}
	free(tokens);
}

/**
 * handle_rbyte - check the type of data return from getine
 * @buffer: user input from stdin
 * @rbyte: return byte from getline
 * Return: integer
 */

int handle_rbyte(char *buffer, int rbyte)
{
	/* when user press enter key */
	if (rbyte == 1)
	{
		free(buffer);
		return (1);
	}

	/* end of file */
	if (rbyte == -1)
	{
		free(buffer);
		exit(0);
	}
}
