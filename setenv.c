#include "header.h"

extern char **environ;

/**
 * _setenv - set environment variable
 * @name: name of variable to be added
 * @value: Value of the variable
 * @overwrite: if 1 it replaces the value, if 0 it appends it to existing value
 * Return: 0 on success, -1 on failure
 */

int _setenv(const char *name, const char *value, int overwrite)
{
	int i = 0, l = 0;
	char *token, *envcpy, *namecpy;

	namecpy = malloc(1024);
	if (namecpy == NULL)
		return (-1)
	strcpy(namecpy, name);
	envcpy = malloc(2048);
	if (envcpy == NULL)
		return (-1);

	while (environ[i])
	{
		strcpy(envcpy, environ[i]);
		token = strtok(envcpy, "=");
		if (strcmp(namecpy, token) == 0)
		{
			if (overwrite == 1)
			{
				strcat(namecpy, "=");
				strcat(namecpy, value);
				environ[i] = namecpy;

				return (0);
			}
			else if (overwrite == 0)
				return (0);
		}
		i++;
	}
	strcat(namecpy, "=");
	strcat(namecpy, value);
	environ[i] = namecpy;
	environ[i + 1] = NULL;
	return (0);
}

/**
 * _unsetenv - removes a variable from the environment
 * @name: name of variable to be removed
 * Return: 0 on success, -1 on failure
 */

int _unsetenv(const char *name)
{
	int i;
	char *token, *envcpy;

	envcpy = malloc(2048);
	if (envcpy == NULL)
		return (-1);

	for (i = 0; environ[i]; i++)
	{
		strcpy(envcpy, environ[i]);
		token = strtok(envcpy, "=");
		if (strcmp(name, token) == 0)
		{
			while (environ[i])
			{
				environ[i] = environ[i + 1];
				i++;
			}
			return (0);
		}
		i++;
	}
	return (0);
}
