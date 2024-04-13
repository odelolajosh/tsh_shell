#ifndef _UTILS_H
#define _UTILS_H

#include <unistd.h>
#include <limits.h>
#include <stdio.h>

#include "strings.h"
#include "tsh.h"

/* cd.c */
char *_getcwd(void);
char *_getcwdname(void);

/* env.c */
char *_getenv(char *const *_environ, const char *name);
char **_setenv(char **_environ, const char *name, const char *value);
char **_unsetenv(char **_environ, const char *name);

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
int _putcfd(char c, int fd);
int _putsfd(char *str, int fd);
int _putc(char c);
int _puts(char *str);
int _eputc(char c);
int _eputs(char *str);

/* util.c */
int interactive(tsh_t *tsh);
FILE *openfileorexit(const char *path, const char *progname);

#endif /* _UTILS_H */
