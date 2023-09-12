#include "shell.h"

/**
 * _strtok - copies string from source to destination
 * @str: destination
 * @sep: string to copy
 * Return: pointer to dest
 */
char *_strtok(char *str, char *sep)
{
	/* create a static variable to point to next token */
	static char *next_token;
	char *current_token = NULL;

	/* check for first function call */
	if (str != NULL)
		next_token = str;
	/* skip leading delimiters */
	while (*next_token && strchr(sep, *next_token))
		next_token++;
	/* check for null char */
	if (*next_token == '\0')
		return (NULL);
	/* found first valid token, iterate to find end of token  */
	current_token = next_token;
	while (*next_token && !strchr(sep, *next_token))
		next_token++;
	/* replace seperators with null chars */
	if (*next_token)
	{
		*next_token = '\0';
		next_token++;
	}
	return (current_token);
}
/**
 * _strlen - count length of string
 * @s: string to be counted
 * Return: length
 */
int _strlen(char *s)
{
	int count = 0;

	while (*s != '\0')
	{
		count++;
		s++;
	}
	return (count);
}
/**
 * _strcpy - copies string from source to destination
 * @dest: destination
 * @src:string to copy
 * Return: pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
	return (dest);
}
/**
 * _strcat - function to concatenate strings
 * @dest: string
 * @src: string to concatenate
 * Return:dest
 */
char *_strcat(char *dest, char *src)
{
	int len1;
	int len2;

	len1 = 0;
	while (dest[len1] != '\0')
	{
		len1++;
	}
	len2 = 0;
	while (src[len2] != '\0')
	{
		dest[len1] = src[len2];
		len1++;
		len2++;
	}
	dest[len1] = '\0';
	return (dest);
}
/**
 * _strcmp - function to compare two strings
 * @s1: first string
 * @s2: second string
 * Return: s1[i] - s2[i]
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	return (0);
}
