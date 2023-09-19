#include "shell.h"

/**
 * process_command - process user commands
 * @tokens: array of tokens to process
 * @file: filename
 * @env: enivironment
 * @status: status code of process execution
 * Return: status code
 */

int process_command(char **tokens, char *file, char *env, char *status)
{
	char **tk = tokens, *sp_char, sp_chars = ";||&&", **new_tk;
	int count = 0, i;

	sp_char = special_char(tokens);
	if (sp_char)
	{
		while (1)
		{
			i = count;
			/* count number of tokens before special char */
			while (tk[count] && !strstr(sp_chars, tk[count]))
					count++;
			/* construct a new token array */
			new_tk = malloc(sizeof(char *) * (count + 1));
			if (new_tk == NULL)
				return (-1);
			for (; i < count; i++)
				new_tk[i] = strdup(tk[i]);
			new_tk[i] = NULL;
			sp_char = tk[count++];

		if (check_semicolon(tokens))
			*status = handle_semicolon(tokens, file, env, status);
		
