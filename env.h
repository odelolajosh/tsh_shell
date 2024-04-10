#ifndef ENV_H
#define ENV_H

char *_getenv(char *const *_environ, const char *name);
char **_setenv(char **_environ, const char *name, const char *value);
char **_unsetenv(char **_environ, const char *name);

#endif // ENV_H