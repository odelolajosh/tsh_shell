#include "tsh_strings.h"

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

/**
 * _realloc - reallocates a memory block.
 * @ptr: pointer to the memory previously allocated.
 * @old_size: size, in bytes, of the allocated space of ptr.
 * @new_size: new size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);

	if (new_size < old_size)
		_memcpy(newptr, ptr, new_size);
	else
		_memcpy(newptr, ptr, old_size);

	free(ptr);
	return (newptr);
}

/**
 * _realloc2 - reallocates a memory block of a double pointer.
 * @ptr: double pointer to the memory previously allocated.
 * @old_size: size, in bytes, of the allocated space of ptr.
 * @new_size: new size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
char **_realloc2(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newptr;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(sizeof(char *) * new_size);
	if (newptr == NULL)
		return (NULL);

	for (i = 0; i < old_size; i++)
		newptr[i] = ptr[i];

	free(ptr);

	return (newptr);
}
