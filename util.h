#ifndef _UTIL_H
#define _UTIL_H

#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include "strings.h"

#define TSH_RL_BUFSIZE 1024

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_realloc2(char **ptr, unsigned int old_size, unsigned int new_size);
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t count);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

#endif