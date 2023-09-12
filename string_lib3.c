#include "shell.h"

/**
 * _getline - get a line of byte from a file
 * @buffer: where to store the data
 * @fd: where to read the data from
 * @size: size of buffer
 */

ssize_t _getline(char **line, size_t *size, int fd)
{
	int n = 256, line_pos = 0;
	char c;
	static char buffer[BUFFSIZE];
	static int data_pos = 0, byte_size = 0;

	if (*line == NULL)
		*line = malloc(sizeof(char) * n);
	if (*line == NULL)
		return (-1);
	if (data_pos >=  byte_size)
	{
		byte_size = read(fd, buffer, BUFFSIZE - 1);
		if (byte_size <= 0)
		{
			(*line)[line_pos] = '\0';
			*size = line_pos;
			return (-1);
		}
		data_pos = 0;
	}
	c = buffer[data_pos++];
	while (c != '\n')
	{
		(*line)[line_pos++] = c;
		if (line_pos >= (n - 10))
		{
			n = n + 256;
			*line = realloc(*line, n);
			if (*line == NULL)
				return (-1);
		}
		if (data_pos >= byte_size)
		{
			byte_size = read(fd, buffer, 1023);
			if (byte_size <= 0)
			{
				(*line)[line_pos] = '\0';
				*size = line_pos;
				return (*size - 1);
			}
			data_pos = 0;
		}
		c = buffer[data_pos++];
	}
	(*line)[line_pos++] = '\n';
	(*line)[line_pos] = '\0';
	*size = line_pos;
	return (*size - 1);
}
