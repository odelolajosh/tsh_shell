#include "strings.h"

/**
 * _memcpy - copy memory area
 *
 * @dest: destination memory
 * @src: source memory
 * @n: bytes to copy
 * Return: pointer to the destination memory
 */
void *_memcpy(void *dest, const void *src, size_t n)
{
	char *dest_ptr = (char *) dest;
	char *src_ptr = (char *) src;
	unsigned int i;

	for (i = 0; i < n; i++)
		dest_ptr[i] = src_ptr[i];

	return (dest_ptr);
}

/**
 * _memmove - copies n bytes from src to dest
 * @dest: destination
 * @src: source
 * @n: number of bytes
 */
int _memmove(char *dest, char *src, unsigned int n)
{
	char *temp = malloc(sizeof(char) * n);
	unsigned int i;

	if (temp == NULL)
		return (0);

	for (i = 0; i < n; i++)
		temp[i] = src[i];

	for (i = 0; i < n; i++)
		dest[i] = temp[i];

	free(temp);

	return (1);
}
