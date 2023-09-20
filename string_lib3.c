#include "shell.h"

/**
 * _getline - get a line of byte from a file
 * @line: where to store the data
 * @fd: where to read the data from
 * @size: size of buffer
 * Return: read data from buffer up until newline
 */

ssize_t _getline(char **line, size_t *size, int fd)
{
	int n = 256, lp = 0, rt, c;
	static char buffer[BUFFSIZE];
	static int dp = 1, bs = 1;

	if (*line == NULL)
		*line = malloc(sizeof(char) * n);
	if (*line == NULL)
		return (-1);
	if (dp >=  bs)
	{
		bs = read(fd, buffer, BUFFSIZE - 1);
		if (bs <= 0)
		{
			(*line)[lp] = '\0';
			*size = lp;
			return (-1);
		}
		dp = 0;
	}
	c = buffer[dp++];
	while (c != '\n')
	{
		(*line)[lp++] = c;
		if (lp >= (n - 10))
		{
			n = n + 256;
			*line = realloc(*line, n);
			if (*line == NULL)
				return (-1);
		}
		rt = buf_overflow(&dp, &bs, buffer, &fd, *line, &lp, size);
		if (rt != -100)
			return (rt);
		c = buffer[dp++];
	}
	(*line)[lp++] = '\n';
	(*line)[lp] = '\0';
	*size = lp;
	return (*size);
}

/**
 * buf_overflow - check if buffer has overflowed
 * @d: data position
 * @b: byte size
 * @bf: buffer
 * @f: file descriptor
 * @l: line buffer
 * @lp: line position
 * @s: line buffer size
 * Return: integer
 */

int buf_overflow(int *d, int *b, char *bf, int *f, char *l, int *lp, size_t *s)
{
	if (*d >= *b)
	{
		*b = read(*f, bf, 1023);
		if (*b <= 0)
		{
			l[*lp] = '\0';
			*s = *lp;
			return (*s);
		}
		*d = 0;
	}

	/* just a random number */
	return (-100);
}


/**
 * preprocess_strtok - preprocess strtok before tokenizing it.
 * @b: buffer to preprocess
 * Return: pointer to the preprocess buffer
 */

char *preprocess_strtok(char *b)
{
	char *new_buf;
	int len, i, index;

	len = strlen(b);
	index = 0;
	new_buf = malloc(2 * len + 1);
	if (new_buf == NULL)
		return (NULL);
	for (i = 0; i < len; i++)
	{
		if (b[i] == '&' && i < len - 1 && b[i + 1] == '&')
		{
			new_buf[index++] = ' ';
			new_buf[index++] = '&';
			new_buf[index++] = '&';
			new_buf[index++] = ' ';
			i++;
		}
		else if (b[i] == '|' && i < len - 1 && b[i + 1] == '|')
		{
			new_buf[index++] = ' ';
			new_buf[index++] = '|';
			new_buf[index++] = '|';
			new_buf[index++] = ' ';
			i++;
		}
		else if (b[i] == ';' || b[i] == '|' || b[i] == '&')
		{
			new_buf[index++] = ' ';
			new_buf[index++] = b[i];
			new_buf[index++] = ' ';
		}
		else
			new_buf[index++] = b[i];
	}
	new_buf[index] = '\0';
	free(b);
	return (new_buf);
}
