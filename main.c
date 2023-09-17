#include "shell.h"

/**
 * main - entry point.
 * @argc: argument count from commandline
 * @env: environment
 * @argv: pointer to an array of argument from commandline.
 * Return: succes code on success or error code on error
 */

int main(__attribute__((unused)) int argc, char **argv, char **envp)
{
	char *buffer, *sep;
	ssize_t rbyte;
	size_t buff_size;
	char **tokens, **env;
	int ret_code = 0;

	sep = " \n\t";
	/* make the environment variable dynamic (resizeable) */
	environ = dynamic_env(envp);
	while (1)
	{
		buffer = NULL;
		tokens = NULL;
		//env = environ;
		/* check if the keyboard is connected to the tty (inter. mod)*/
		if (isatty(STDIN_FILENO))
			prompt_user();
		rbyte = _getline(&buffer, &buff_size, STDIN_FILENO);
		if (handle_rbyte(buffer, rbyte, &ret_code, environ) == 1)
			continue;
		tokens = tokenize_buffer(buffer, sep);
		free(buffer);
		if (tokens == NULL)
			continue;
		ret_code = handle_path(tokens, argv[0], environ, &ret_code);
	}
	free_memory(environ);
	return (ret_code);
}
