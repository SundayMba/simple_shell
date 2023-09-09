#include "shell.h"

/**
 * main - entry point.
 * @argc: argument count from commandline
 * @env: environment
 * @argv: pointer to an array of argument from commandline.
 * Return: succes code on success or error code on error
 */

int main(__attribute__((unused)) int argc, char **argv, char **env)
{
	char *buffer, *sep;
	ssize_t rbyte;
	size_t buff_size;
	char **tokens;

	buff_size = 0;
	sep = " \n\t";
	while (1)
	{
		buffer = NULL;
		tokens = NULL;
		/* check if the keyboard is connected to the tty (inter. mod)*/
		if (isatty(STDIN_FILENO))
			prompt_user();
		rbyte = getline(&buffer, &buff_size, stdin);
		if (handle_rbyte(buffer, rbyte) == 1)
			continue;
		tokens = tokenize_buffer(buffer, sep);
		free(buffer);
		if (tokens == NULL)
			continue;
		handle_execution(tokens, argv[0], env);
		free_memory(tokens);
	}
	return (0);
}
