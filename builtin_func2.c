#include "shell.h"

/**
 * handle_cd - handles the directory changes
 * @tk: tokens
 * @file: filename
 * @env: environment
 * @n: status code
 * Return: 0 - success, -1 failure
 */

int handle_cd(char **tk, char *file, char **env, int *n)
{
	size_t size;
	char pwd[500];
	static int err = 1;

	(void)env;
	size = 500;
	if (tk[1] == NULL)
	{
		*n = cd_home(file);
		if (*n == -2)
		{
			*n = -1;
			handle_cd_error(file, tk, err, "can't cd to");
		}
	}
	else if (_strcmp(tk[1], "-") == 0)
	{
		*n = cd_previous_path(file);
		if (*n == 0)
		{
			if (getcwd(pwd, size) == NULL)
			{
				handle_cd_error(file, tk, err, "can't cd to");
				*n = -1;
				return (*n);
			}
			write(STDOUT_FILENO, pwd, _strlen(pwd));
			write(STDOUT_FILENO, "\n", 1);
		}
	}
	else
		*n = cd_path(file, tk[1]);
	if (*n == -2)
		handle_cd_error(file, tk, err, "can't cd to");
	if (*n == -1)
		print_env_error(file, "Invalid path");
	free_memory(tk);
	return (*n);
}

/**
 * cd_home - change directory to home directory
 * @file: filename
 * Return: 0 - success, -1 - failure
 */

int cd_home(char *file)
{
	size_t size;
	char pwd[500], *tmp, home[500];

	size = 500;
	tmp = getenv_value("HOME");
	_strcpy(home, tmp);
	if (getcwd(pwd, size) == NULL)
	{
		return (-2);
	}
	if (_setenv("PWD", home, 1) == -1)
	{
		print_env_error(file, "Inavlid path");
		return (-1);
	}
	if (_setenv("OLDPWD", pwd, 1) == -1)
	{
		print_env_error(file, "Invalid, path");
		return (-1);
	}
	if (chdir(home) == -1)
	{
		return (-2);
	}
	return (0);
}

/**
 * getenv_value - get value of a given environment variable
 * @env_name: environment variable name
 * Return: pointer to the environment value
 */

char *getenv_value(char *env_name)
{
	char *env;

	env = _getenv(env_name);
	env = _strchr(env, '=');
	env++;
	return (env);
}

/**
 * cd_path - change directory to the given path
 * @file: filename
 * @path: path name to cd to
 * Return: 0 -success, -1 -failure, -2 -special case failure
 */

int cd_path(char *file, char *path)
{
	size_t size;
	char oldpwd[500], pwd[500];

	(void)file;
	size = 500;
	if (getcwd(oldpwd, size) == NULL)
	{
		return (-2);
	}
	if (chdir(path) == -1)
	{
		return (-2);
	}
	if (_setenv("OLDPWD", oldpwd, 1) == -1)
		return (-1);
	if (getcwd(pwd, size) == NULL)
	{
		return (-1);
	}
	if (_setenv("PWD", pwd, 1) == -1)
		return (-1);
	return (0);
}

/**
 * cd_previous_path - change directory to the given path
 * @file: filename
 * Return: 0 -success, -1 -failure, -2 -special case failure
 */

int cd_previous_path(char *file)
{
	char pwd[500], oldpwd[500], *tmp1, *tmp2;

	(void)file;
	tmp1 = getenv_value("PWD");
	tmp2 = getenv_value("OLDPWD");
	_strcpy(pwd, tmp1);
	_strcpy(oldpwd, tmp2);
	if (chdir(oldpwd) == -1)
	{
		return (-2);
	}
	/* update the PWD and OLDPWD environment variables */
	if (_setenv("PWD", oldpwd, 1) == -1)
		return (-1);
	if (_setenv("OLDPWD", pwd, 1) == -1)
		return (-1);
	return (0);
}
