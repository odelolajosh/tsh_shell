#include "strings.h"

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
	int i, j;

	if (str == NULL)
		str = last;

	for (i = 0; str[i] != '\0'; i++)
	{
		for (j = 0; delim[j] != '\0'; j++)
		{
			if (str[i] == delim[j])
			{
				str[i] = '\0';
				last = str + i + 1;
				return str;
			}
		}
	}

	last = str + i;
	return str;
}

/**
 * _strchr - locates the last occurrence of a character in a string
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