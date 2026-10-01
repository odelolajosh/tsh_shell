#include "tsh_strings.h"

/**
 * _strdup - duplicates a string
 *
 * @s: the given string
 * Return: pointer to the duplicate
 */
char *_strdup(const char *s)
{
	size_t len;
	char *dup;

	len = _strlen(s);
	dup = malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);
	_memcpy(dup, s, len + 1);
	return (dup);
}

/**
 * _strlen - length of a string
 *
 * @s: the given string
 * Return: length of the string string
 */
size_t _strlen(const char *s)
{
	size_t i;

	for (i = 0; s[i]; i++)
		;

	return (i);
}

/**
 * _strcat - concatenates two strings
 *
 * @dest: the destination string
 * @src: string to concatenates
 * Return: pointer to the resulting string
 */
char *_strcat(char *dest, const char *src)
{
	int i;
	int j;

	for (i = 0; dest[i] != '\0'; i++)
		;

	for (j = 0; src[j] != '\0'; j++)
	{
		dest[i] = src[j];
		i++;
	}

	dest[i] = '\0';
	return (dest);
}

/**
 * _strcmp - Function that compares two strings.
 * @s1: type str compared
 * @s2: type str compared
 * Return: 0 if the strings are equal, 1 if s1 is greater, -1 if s2 is greater.
 */
int _strcmp(const char *s1, const char *s2)
{
	int i;

	for (i = 0; s1[i] == s2[i] && s1[i]; i++)
		;

	if (s1[i] > s2[i])
		return (1);
	if (s1[i] < s2[i])
		return (-1);
	return (0);
}

/**
 * _strncmp - Function that compares two strings.
 * @s1: type str compared
 * @s2: type str compared
 * @n: type int - the maximum number of characters to be compared.
 * Return: 0 if the strings are equal, 1 if s1 is greater, -1 if s2 is greater.
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	char *p1 = (char *) s1;
	char *p2 = (char *) s2;

	while (*p1 && *p1 == *p2 && n--)
		++p1, ++p2;
	
	return (*p1 - *p2);
}

/**
 * _strcpy - Copies the string pointed to by src.
 * @dest: Type char pointer the dest of the copied str
 * @src: Type char pointer the source of str
 * Return: the dest.
 */
char *_strcpy(char *dest, char *src)
{

	size_t i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	
	dest[i] = '\0';

	return (dest);
}

/**
 * _atoi - converts a string to an integer
 * @s: the string
 * Return: int
 */
int _atoi(char *s)
{
	unsigned int len = 0, size = 0, p = 1, res = 0, sign = 1, i = 0;

	while (*(s + len) != '\0')
	{
		if (size > 0 && (*(s + len) < '0' || *(s + len) > '9'))
			break;

		if (*(s + len) == '-')
			sign *= -1;

		if ((*(s + len) >= '0') && (*(s + len) <= '9'))
		{
			if (size > 0)
				p *= 10;

			size++;
		}
		len++;
	}

	for (i = len - size; i < len; i++)
	{
		res += ((*(s + i) - '0') * p);
		p /= 10;
	}

	return (sign * res);
}

/**
 * _intlen - get the length of an integer
 * @n: given integer
 * Return: length of integer
 */
int _intlen(int n)
{
	unsigned int len = 0, m;

	if (n < 0)
	{
		len++;
		m = n * -1;
	}
	else
	{
		m = n;
	}

	if (n == 0)
		return (1);

	for (; m != 0; m /= 10)
		len++;

	return (len);
}

/**
 * _itoa - convert integer to string
 * @n: given integer
 * Return: length of integer
 */
char *_itoa(int n)
{
	unsigned int m;
	int length = _intlen(n);
	char *buffer;

	buffer = malloc(sizeof(char) * (length + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + length) = '\0';

	if (n < 0)
	{
		m = n * -1;
		buffer[0] = '-';
	}
	else
	{
		m = n;
	}

	length--;
	do
	{
		*(buffer + length) = (m % 10) + '0';
		m = m / 10;
		length--;
	} while (m > 0);
	return (buffer);
}

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

/**
 * _strtok - tokenizes a string
 * @str: string to tokenize
 * @delim: delimiter to tokenize by
 *
 * Return: pointer to the next token
 */
char *_strtok(char *str, const char *delim)
{
	static char *last;
	char *token;

	if (str == NULL)
		str = last;

	/* skip leading delimiters */
	while (*str && _strchr((char *)delim, *str))
		str++;

	if (*str == '\0')
	{
		last = str;
		return (NULL);
	}

	token = str;
	/* find the end of the token */
	str = _strpbrk(token, delim);
	if (str == NULL)
		last = _strrchr(token, '\0');
	else
	{
		*str = '\0';
		last = str + 1;
	}

	return (token);
}

/**
 * _strrchr - locates the last occurrence of a character in a string
 * @s: string to search
 * @c: character to locate
 *
 * Return: pointer to the last occurrence of the character
 */
char *_strrchr(char *s, char c)
{
	char *last = NULL;

	while (*s)
	{
		if (*s == c)
			last = s;
		s++;
	}

	if (c == '\0')
		return (s);

	return (last);
}

/**
 * _strchr - locates the first occurrence of a character in a string
 * @s: string to search
 * @c: character to locate
 *
 * Return: pointer to the first occurrence of the character
 */
char *_strchr(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}

	return (NULL);
}

/**
 * _strpbrk - locates the first occurrence in a string of any character in a set
 * @s: string to search
 * @accept: set of characters to search for
 *
 * Return: pointer to the first occurrence of a character in accept
 */
char *_strpbrk(const char *s, const char *accept)
{
	char *a;
	while (*s)
	{
		a = (char *)accept;
		while (*a)
			if (*a++ == *s)
				return ((char *)s);

		++s;
	}

	return (NULL);
}

char *_strncat(char *dest, const char *src, size_t n)
{
  size_t i, j = _strlen(dest);
  
  for (i = 0; i < n && src[i]; i++)
    dest[j + i] = src[i];

  dest[j + i] = '\0';
  return (dest);
}

char *_strncpy(char *dest, const char *src, size_t n)
{
  size_t i;
  
  for (i = 0; i < n - 1 && src[i]; i++)
    dest[i] = src[i];

  for (; i < n; i++)
    dest[i] = '\0';

  return (dest);
}
