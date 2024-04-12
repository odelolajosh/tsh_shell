#ifndef _UTIL_H
#define _UTIL_H

#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include "strings.h"

#include "tsh.h"

/* realloc.c */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_realloc2(char **ptr, unsigned int old_size, unsigned int new_size);

/* getline.c */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
size_t read_command(tsh_t *tsh);
void sigint_handler(int signal_num);

/* prompt.c */
void prompt(void);

/* put.c */
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
int _putchar(char c);
int _puts(char *str);
int _eputchar(char c);
int _eputs(char *str);

#endif