#include "shell.h"

/**
 * _strncmp - compares n bytes of two string
 * @s1: first string
 * @s2: second string
 * @n: number of bytes to be compared
 * Return: -1 if n byte of s1 != s2 else 0
 */

int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
	{
		if (s1[i] == s2[i])
		{
			continue;
		}
		else
			return (-1);
	}
	return (0);
}

/**
 * _strstr - finds the first occurence of the substring
 * needle in the string haystack.
 * @haystack: parent string
 * @needle: substring
 * Return: pointer to the begining of substring
 */

char *_strstr(const char *haystack, const char *needle)
{
	size_t i;
	int j = 0;
	char *s;

	for (i = 0; needle[i]; i++)
		;
	while (*haystack)
	{
		if (_strncmp(needle, haystack, i) == 0)
		{
			s = _strdup(haystack);
			return (s);
		}
		haystack++;
	}
	return (NULL);
}

/**
 * _strchr - searches for first appearance of
 * character in a given string
 * @s: string to look through
 * @c: character to search for
 * Return: On success returns a pointer to the start
 * address of the first appearance of the character
 * else return NULL
 */

char *_strchr(const char *s, int c)
{
	char *ptr;
	int i;

	ptr = _strdup(s);
	for (i = 0; *ptr; ptr++)
	{
		if (c == *ptr)
			return (ptr);
	}
	return (NULL);
}

/**
 * _strdup - duplicates a string
 * @s: string to be duplicated
 * Return: pointer to the new string on success, else return NULL
 */

char *_strdup(const char *s)
{
	char *new;
	int i;

	for (i = 0; *s; s++)
		i++;
	new = malloc(sizeof(char) * (i + 1));
	if (new == NULL)
		return (NULL);
	s -= i;

	for (i = 0; *s; s++)
	{
		new[i] = *s;
		i++;
	}
	new[i] = '\0';
	return (new);
}

/**
 * _realloc - reallocates memory with a given size
 * @ptr: address of old memory
 * @size: size of new memory to be created
 * Return: void
 */

void *_realloc(void *ptr, size_t size)
{
	char *s;

	s = malloc(size);
	if (s == NULL)
		return (NULL);
	s = _strdup(ptr);
	free(ptr);
	return (s);
}
