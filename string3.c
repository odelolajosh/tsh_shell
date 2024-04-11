#include "strings.h"

/**
 * _isdigit - checks if a char is a digit
 *
 * @str: string to check
 * Return: returns 1 if digit and 0 if not a digit
 */

int _isdigit(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
	}
	return (1);
}

/**
 * _isspace - checks if a char is a space
 * @c: char to check
 * Return: 1 if space, 0 if not
 */
int _isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

/**
 * _substring - extracts a substring from a string
 * @string: string to extract from
 * @start: starting index
 * @end: ending index
 *
 * Return: pointer to the substring
 */
char *_substring(char *string, int start, int end)
{
	int i;
	char *token = malloc(sizeof(char) * (end - start + 1));

	if (token == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	for (i = start; i < end; i++)
		token[i - start] = string[i];

	token[end - start] = '\0';

	return (token);
}

/**
 * _strtrim - trims leading and trailing whitespace from a string
 * @str: string to trim
 *
 * Return: pointer to the trimmed string
 */
char *_strtrim(char *str)
{
	char *end;

	// Trim leading space
	while (_isspace((unsigned char)*str))
		str++;

	if (*str == '\0') // All spaces
		return str;

	// Trim trailing space
	end = str + _strlen(str) - 1;
	while (end > str && _isspace((unsigned char)*end))
		end--;

	// Write new null terminator
	*(end + 1) = '\0';

	return str;
}
