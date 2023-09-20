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

	sp_char = special_char(tokens, sp_chars);
	if (sp_char)
	{
		while (tk[count])
		{
			prev = count;
			while (tk[count] && !_strstr(sp_chars, tk[count]))
				count++;
			new_tk = malloc(sizeof(char *) * ((count - prev) + 1));
			if (new_tk == NULL)
				return (-1);
			for (i = 0; i < (count - prev); i++)
				new_tk[i] = _strdup(tk[prev + i]);
			new_tk[i] = NULL;
			sp_char = tk[count];
			*status = handle_path(new_tk, file, env, status);
			if (sp_char != NULL)
			{
				if (_strcmp(sp_char, "||") == 0)
				{
					if (*status == 0)
						return (flush(tokens, status));
				}
				else if (strcmp(sp_char, "&&") == 0)
					if (*status != 0)
						return (flush(tokens, status));
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
 * @sp_char: special characeters
 * Return: pointer to special char if exist or NULL
 */

char *special_char(char **tokens, char *sp_chars)
{
	char *sp_char_ptr;
	int i;

	for (i = 0; tokens[i]; i++)
	{
		sp_char_ptr = _strstr(sp_chars, tokens[i]);
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


/**
 * handle_comment - strip off comments.
 * @tokens: array of tokens to process
 * @file: filename
 * @env: enivironment
 * @status: status code of process execution
 * Return: status code
 */

int handle_comment(char **tokens, char *file, char **env, int *status)
{
	char *new_tk;
	int count;

	count = 0;
	if (special_char(tokens, "#"))
	{
		for (i = 0; tokens[i] && !strstr("#", tokens[i]); i++)
			count++;
		if (count == 0)
			return (0);
		new_tk = malloc(sizeof(char *) * (count + 1));
		if (new_tk == NULL)
			return (-1);
		for (i = 0; i < count; i++)
			new_tk[i] = strdup(tokens[i]);
		new_tk[i] = NULL;
		free_memory(tokens);
		return (process_var(new_tk, file, env, status));
	}
	else
		return (process_var(new_tk, file, env, status));
}



/**
 * process_var - replace variable precede with $.
 * @tokens: array of tokens to process
 * @file: filename
 * @env: enivironment
 * @status: status code of process execution
 * Return: status code
 */

int process_var(char **tokens, char *file, char **env, int *status)
{
	int res;

	/* check for $ sign for variable replacement */
	for (i = 0; tokens[i]; i++)
	{
		dollar = strchr(tokens[i], '$');
		if (dollar)
		{
			dollar++;
			if (dollar && *dollar == '?')
				token[i] = get_status(tokens[i]);
			else if (dollar && *dollar == '$')
				tokens[i] = get_pid(tokens[i]);
			else
				tokens[i] = check_env_var(tokens[i]);
		}
	}
	return (process_cmd(tokens, file, env, status));
}
