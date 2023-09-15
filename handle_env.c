#include "shell.h"

/**
 * _setenv - set an environment variable
 * @name: name of environment variable
 * @value: value of environment variable
 * @overwrite: (0) - don't overwrite, (1) - overwrite.
 * @env: address of the env variable
 * Return: (0) - success : (-1) - on error
 */

int _setenv(const char *name, const char *value, int overwrite)
{
	char *new_env;

	/* len = len(name) +len(value) + len('=') + len('\0') */
	len = strlen(name) + strlen(value) + 2;
	new_env = malloc(sizeof(char) * len);
	if (new_env == NULL)
		return (-1);
	/* construct the new environment */
	strcpy(new_env, name);
	strcat(new_env, "=");
	strcat(new_env, value);
	strcat(new_env, "\0");
	if (check_env(name) == 0)
		_putenv(new_env);
	else
	{
		if (overwrite == 0)
			free(new_env);
		else
		{
			_unsetenv(name);
			_putenv(new_env);
		}
	}
	return (0);
}

/**
 * check_env - check if an environment variable exist
 * @name: name of the environment variable
 * Return: 1 (exist) 0 (does not exist)
 */

int check_env(char *name)
{
	int i;
	char *var;

	i = 0;
	var = environ[i];
	while (var != NULL)
	{
		if (_strnstr(var, name, _strlen(name)))
			return (1);
		i++;
		var = environ[i];
	}
	return (0);
}

/**
 * _putenv - put an environment variable into a list of env variables
 * @new_env: name of the env variable
 * Return: (0) - success, (-1) - error
 */

int _putenv(char *new_env)
{
	int i;
	char ***environ_p = &environ;

	i = 0;
	while (environ[i])
		i++;
	*environ_p = realloc(*environ_p, (sizeof(char *) * (i + 2)));
	if (*environ_p == NULL)
		return (-1);
	/* *environ_p is same as environ (it can be used interchangeably */
	(*environ_p)[i++] = new_env;
	(*environ_p)[i] = NULL;
	return (0);
}

/**
 * dynamic_env - allocate memory for env and make it resizable
 * @env: environment variable
 * Return: pointer to redesign environment variable
 */

char **dynamic_env(char **env)
{
	int i, j;
	char *tmp;
	char **env_array;

	/* Get size of the Array of pointers */
	i = 0;
	while (env[i])
		i++;
	env_array = malloc(sizeof(char *) * (i + 1));
	if (env_array == NULL)
		return (NULL);
	i = 0;
	while (env[i])
	{
		tmp = malloc(sizeof(char) * (strlen(env[i]) + 1));
		if (tmp == NULL)
		{
			for (j = i - 1; j >= 0; j--)
				free(env_array[j]);
			free(env_array);
			return (NULL);
		}
		strcpy(tmp, env[i]);
		strcat(tmp, "\0");
		env_array[i] = tmp;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

/**
 * _unsetenv - remove an environ variable
 * @name: name of the environment variable to remove
 * Return: (0) - successful, (-1) - failure
 */

int _unsetenv(char *name)
{
	int i, len, index, env_name_found = 0;
	char *tmp, ***environ_p = &environ;

	i = 0;
	while (environ[i])
		i++;
	env_array = malloc(sizeof(char *) * i);
	if (env_array == NULL)
		return (-1);
	len = i;
	for (i = 0; i < len; i++)
	{
		if (env_name_found = 0)
			if (_strnstr(environ[i], name, _strlen(name)))
				env_name_found = 1;
		index = env_name_found ? (i + 1) : i;
		if (environ[index] != NULL)
			tmp = malloc((_strlen(environ[index]) + 1));
		if (tmp == NULL)
		{
			for (j = i - 1; j >= 0; j--)
				free(env_array[j]);
			free(env_array);
			return (-1);
		}
		if (environ[index] == NULL)
			env_array[i] = NULL;
		else
		{
			strcpy(tmp, environ[index]);
			strcat(tmp, "\0");
			env_array[i] = tmp;
		}
	}
	free_memory(environ);
	*environ_p = env_array;
	return (0);
}
