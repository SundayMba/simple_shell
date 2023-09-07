#include "shell.h"

/**
 * main - entry point.
 * @argc: argument count from commandline
 * @argv: pointer to an array of argument from commandline.
 * Return: succes code on success or error code on error
 */

int main(__attribute__((unused)) int argc, char *argv[])
{
	int tty;
	char *buffer, *token, *sep;
	ssize_t rbyte;
	size_t buff_size = 1024;
	char **tokens;

	sep = " \n\t";
	while (1)
	{
		buffer = NULL;
		tokens = NULL;
		/* check if the keyboard is connected to the tty (inter. mod)*/
		if (isatty(STDIN_FILENO))
			prompt_user();
		rbyte = getline(&buffer, &buff_size, stdin);
		if (rbyte == 1)
			continue;
		else if (rbyte == -1)
			exit(0);
		tokens = tokenize_buffer(buffer, sep);
		/* free buffer after use */
		if (tokens == NULL)
			continue;
		free(buffer);
		free_memory(tokens);
	}
	return (0);
}
