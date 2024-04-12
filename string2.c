#include "strings.h"

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
