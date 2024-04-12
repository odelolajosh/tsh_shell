#include "tsh.h"
#include "utils.h"

int _putfd(char c, int fd)
{
	static int i;
	static char buf[TSH_WRITE_BUFSIZE];
	static int old_fd = -1;

	// if the file descriptor has changed, flush the buffer
	if (old_fd != fd)
	{
		if (old_fd != -1)
			write(old_fd, buf, i);
		i = 0;
		old_fd = fd;
	}

	// if the buffer is full, flush it
	if (c == TSH_BUF_FLUSH || i == TSH_WRITE_BUFSIZE)
	{
		write(fd, buf, i);
		i = 0;
		return (0);
	}

	buf[i++] = c;
	return (1);
}

int _putsfd(char *str, int fd)
{
	int i = 0;

	while (*str)
		i += _putfd(*str++, fd);

	return (i);
}

int _putchar(char c)
{
	return (_putfd(c, STDOUT_FILENO));
}

int _puts(char *str)
{
	return (_putsfd(str, STDOUT_FILENO));
}

int _eputchar(char c)
{
	return (_putfd(c, STDERR_FILENO));
}

int _eputs(char *str)
{
	return (_putsfd(str, STDERR_FILENO));
}
