#include "shell.h"

/**
 * process_cmd - process user commands
 * @tokens: array of tokens to process
 * @file: filename
 * @env: enivironment
 * @status: status code of process execution
 * Return: status code
 */

int process_cmd(char **tokens, char *file, char **env, int *status)
{
	char **tk = tokens, *sp_char, *sp_chars = ";||&&", **new_tk;
	int count = 0, i, prev;

	sp_char = special_char(tokens);
	if (sp_char)
	{
		while (tk[count])
		{
			prev = count;
			while (tk[count] && !strstr(sp_chars, tk[count]))
				count++;
			new_tk = malloc(sizeof(char *) * ((count - prev) + 1));
			if (new_tk == NULL)
				return (-1);
			for (i = 0; i < (count - prev); i++)
				new_tk[i] = strdup(tk[prev + i]);
			new_tk[i] = NULL;
			sp_char = tk[count];
			*status = handle_path(new_tk, file, env, status);
			if (sp_char != NULL)
			{
				if (strcmp(sp_char, "||") == 0)
				{
					if (*status == 0)
						return (flush(tokens, status));
				}
				else if (strcmp(sp_char, "&&") == 0)
				{
					if (*status != 0)
						return (flush(tokens, status));
				}
			}
			else
				return (flush(tokens, status));
			count++;
		}
	}
	else
		*status = handle_path(tokens, file, env, status);
	return (*status);
}


/**
 * special_char - check if special char like &&, ;, || exist.
 * @tokens: array of tokens that contain the command
 * Return: pointer to special char if exist or NULL
 */

char *special_char(char **tokens)
{
	char *sp_chars = ";&&||", *sp_char_ptr;
	int i;

	for (i = 0; tokens[i]; i++)
	{
		sp_char_ptr = strstr(sp_chars, tokens[i]);
		if (sp_char_ptr != NULL)
			return (sp_char_ptr);
	}
	return (NULL);
}

/**
 * flush - clean up the memory and return to the caller
 * @tokens: array of tokens to free up
 * @status: status code to return
 * Return: status value
 */

int flush(char **tokens, int *status)
{
	free_memory(tokens);
	return (*status);
}
