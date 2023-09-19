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
	(void)env;
	size_t size = 500;
	char pwd[size];

	if (tk[1] == NULL)
	{
		*n = cd_home(file);
	}
	else if (strcmp(tk[1], "-") == 0)
	{
		*n = cd_previous_path(file);
		if (*n == 0)
		{
			if (getcwd(pwd, size) == NULL)
			{
				perror(file);
				*n = -1;
				return (*n);
			}
			write(STDOUT_FILENO, pwd, _strlen(pwd));
			write(STDOUT_FILENO, "\n", 1);
		}
	}
	else
		*n = cd_path(file, tk[1]);
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
	size_t size = 500;
	char pwd[size], *tmp, home[256];

	tmp = getenv_value("HOME");
	strcpy(home, tmp);
	if (getcwd(pwd, size) == NULL)
	{
		perror(file);
		return (-1);
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
		perror(file);
		return (-1);
	}
	return (0);
}

/**
 * getenv_value - get value of a given environment variable
 * @env_name: environment variable name
 * Return; pointer to the environment value
 */

char *getenv_value(char *env_name)
{
	char *env;

	env = _getenv(env_name);
	env = strchr(env, '=');
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
	size_t size = 500;
	char oldpwd[size], pwd[size];

	if (getcwd(oldpwd, size) == NULL)
	{
		perror(file);
		return (-2);
	}
	if (chdir(path) == -1)
	{
		perror(file);
		return (-2);
	}
	if (_setenv("OLDPWD", oldpwd, 1) == -1)
		return (-1);
	if (getcwd(pwd, size) == NULL)
	{
		perror(file);
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
	size_t size = 500;
	char pwd[size], oldpwd[size], *tmp1, *tmp2;

	tmp1 = getenv_value("PWD");
	tmp2 = getenv_value("OLDPWD");
	strcpy(pwd, tmp1);
	strcpy(oldpwd, tmp2);
	if (chdir(oldpwd) == -1)
	{
		perror(file);
		return (-2);
	}
	/* update the PWD and OLDPWD environment variables */
	if (_setenv("PWD", oldpwd, 1) == -1)
		return (-1);
	if (_setenv("OLDPWD", pwd, 1) == -1)
		return (-1);
	return (0);
}
