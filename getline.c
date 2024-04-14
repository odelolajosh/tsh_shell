#include "utils.h"
#include "strings.h"
#include "parsers.h"

/**
 * _getline - reads an entire line from stream, store the
 * address of the buffer containing the text int *lineptr. Can only
 * be used once at a time.
 *
 * @lineptr: output pointer
 * @n: the maximum number of char to read
 * @stream: the stream
 *
 * Return: pointer to the output string
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static char buffer[TSH_READ_BUFSIZE];
	static size_t i, len;
	char *line, *new_line, *newline;
	size_t m = 0, rbytes = 0, k;

	line = *lineptr;
	if (line && n)
		m = *n;

	if (i == len) // buffer is full consumed, reset
		i = len = 0;

	if (len == 0) // buffer is empty, read from stream
	{
		rbytes = read(fileno(stream), buffer, TSH_READ_BUFSIZE);
		if (rbytes == (size_t)-1 || rbytes == 0) // Error or EOF
			return (-1);

		len = rbytes;
	}

	newline = _strchr(buffer + i, '\n');
	k = newline ? 1 + (unsigned int)(newline - buffer) : len;

	new_line = _realloc(line, m, m + k + 1);
	if (!new_line)
		return (line ? free(line), -1 : -1);

	if (len)
		_strncat(new_line, buffer + i, k - i);
	else
		_strncpy(new_line, buffer + i, k - i);

	m += k - i;
	i = k;
	line = new_line;

	if (m)
		*n = m;
	*lineptr = line;
	return (m);
}
