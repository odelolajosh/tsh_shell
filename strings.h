#ifndef __STRINGS_H
#define __STRINGS_H

#include <unistd.h>
#include <stdlib.h>

char *_strdup(const char *s);
size_t _strlen(const char *s);
char *_strcat(char *dest, const char *src);
int _strcmp(const char *s1, const char *s2);

int _strncmp(const char *s1, const char *s2, size_t n);
char *_strcpy(char *dest, char *src);
int _atoi(char *s);
char *_itoa(int);

int _isdigit(char *str);
int _isspace(char c);
char *_substring(char *string, int start, int end);
char *_strtrim(char *str);

char *_strtok(char *str, const char *delim);
char *_strrchr(char *s, char c);
char *_strchr(char *s, char c);
char *_strpbrk(const char *s, const char *accept);

void *_memcpy(void *dest, const void *src, size_t n);
int _memmove(char *dest, char *src, unsigned int n);

#endif