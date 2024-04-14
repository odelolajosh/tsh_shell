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

// line buffer
static char *buffer;
// track buffer current index (position) and length
static size_t buf_index, buf_len;

/**
 * input - Display the shell prompt and read a line of input
 * @line: pointer to the line buffer
 *
 * Return: number of characters read, or -1 on failure
 */
size_t input(tsh_t *tsh)
{
	size_t rbytes, j;
	char sep;

	signal(SIGINT, sigint_handler);

	if (buf_index >= buf_len) // buffer is full consumed, reset
		buf_index = buf_len = 0;

	if (buf_len)
	{
		if (can_traverse_command(tsh))
		{
			j = traverse_command(buffer + buf_index, &sep);
			tsh->line = buffer + buf_index;
			tsh->line_size = j;
			tsh->sep = sep;

			buf_index += j + 1;
			return (j);
		}

		// free as we are done with the buffer - so buffer dont grow unbounded
		buf_index = buf_len = 0;
		free(buffer);
		buffer = NULL;
	}

	_putc(TSH_BUF_FLUSH);

	if (interactive(tsh))
		prompt();

#if TSH_IMPL
	rbytes = _getline(&buffer, &buf_len, tsh->fp);
#else
	rbytes = getline(&buffer, &buf_len, tsh->fp);
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

void flush_input(void)
{
	if (buffer)
		free(buffer);
	buffer = NULL;
	buf_index = buf_len = 0;
}
