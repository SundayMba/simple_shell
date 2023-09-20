#include "shell.h"

/**
 * main - entry point.
 * @argc: argument count from commandline
 * @envp: environment
 * @argv: pointer to an array of argument from commandline.
 * Return: succes code on success or error code on error
 */

int main(__attribute__((unused)) int argc, char **argv, char **envp)
{
	char *buffer, *sep;
	ssize_t rbyte;
	size_t buff_size;
	char **tokens, *buf;
	int ret_code = 0;

	sep = " \n\t";
	/* make the environment variable dynamic (resizeable) */
	environ = dynamic_env(envp);
	while (1)
	{
		buffer = NULL;
		tokens = NULL;
		buf = NULL;
		/* check if the keyboard is connected to the tty (inter. mod)*/
		if (isatty(STDIN_FILENO))
			prompt_user();
		rbyte = _getline(&buffer, &buff_size, STDIN_FILENO);
		if (handle_rbyte(buffer, rbyte, &ret_code, environ) == 1)
			continue;
		buf = preprocess_strtok(buffer);
		tokens = tokenize_buffer(buf, sep);
		free(buf);
		if (tokens == NULL)
			continue;
		ret_code = process_cmd(tokens, argv[0], environ, &ret_code);
	}
	free_memory(environ);
	return (ret_code);
}
