#include "strings.h"
#include <stdio.h>

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
