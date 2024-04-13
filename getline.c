#include "utils.h"
#include "strings.h"
#include "parsers.h"

/**
 * sigint_handler - handles the SIGINT signal
 * @signal_num: the signal number
 */
void sigint_handler(__attribute__((unused)) int signal_num)
{
	_puts("\n");
	prompt();
}

/**
 * read_command - Display the shell prompt and read a line of input
 * @line: pointer to the line buffer
 * @len: pointer to the line buffer size
 *
 * Return: number of characters read, or -1 on failure
 */
size_t read_command(tsh_t *tsh)
{
	static char *buffer;	// line buffer
	static size_t i, len; // i, len are position in and length of the buffer
	size_t rbytes, j;
	char sep;

	signal(SIGINT, sigint_handler);

	if (i >= len) // buffer is full consumed, reset
		i = len = 0;

	if (len)
	{
		if (can_traverse_command(tsh))
		{
			j = traverse_command(buffer + i, &sep);
			tsh->line = buffer + i;
			tsh->line_size = j;
			tsh->sep = sep;

			i += j + 1;
			return (j);
		}

		// free as we are done with the buffer - so buffer dont grow unbounded
		i = len = 0;
		free(buffer);
		buffer = NULL;
	}

	_putc(TSH_BUF_FLUSH);

	if (interactive(tsh))
		prompt();

#if TSH_IMPL
	rbytes = _getline(&buffer, &len, tsh->fp);
#else
	rbytes = getline(&buffer, &len, tsh->fp);
#endif

	if (rbytes == (size_t)-1) // EOF
		return (-1);

	// replace newline with null byte
	if (*(buffer + rbytes - 1) == '\n')
		*(buffer + rbytes - 1) = '\0', rbytes--;

	tsh->line = NULL;
	tsh->line_size = 0;
	tsh->sep = '\0';
	return (rbytes); // No command yet
}

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
