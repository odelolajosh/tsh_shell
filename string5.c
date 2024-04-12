#include "strings.h"

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
