#ifndef _STRINGS_H
#define _STRINGS_H

#include <unistd.h>
#include <stdlib.h>

/* string.c */
char *_strdup(const char *s);
size_t _strlen(const char *s);
char *_strcat(char *dest, const char *src);
int _strcmp(const char *s1, const char *s2);

/* string2.c */
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strcpy(char *dest, char *src);
int _atoi(char *s);
char *_itoa(int);

/* string3.c */
int _isdigit(char *str);
int _isspace(char c);
char *_substring(char *string, int start, int end);
char *_strtrim(char *str);

/* string4.c */
char *_strtok(char *str, const char *delim);
char *_strrchr(char *s, char c);
char *_strchr(char *s, char c);
char *_strpbrk(const char *s, const char *accept);

/* string5.c */
char *_strncat(char *dest, const char *src, size_t n);
char *_strncpy(char *dest, const char *src, size_t n);

/* mem.c */
void *_memcpy(void *dest, const void *src, size_t n);
int _memmove(char *dest, char *src, unsigned int n);

#endif /* _STRINGS_H */