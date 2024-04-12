#include "strings.h"
#include "utils.h"

/**
 * _envcmp - compares a name with env key
 *
 * @env: env variable
 * @name: name to compare
 *
 * Return: 0 if not match else an integer
 */
int _envcmp(const char *env, const char *name)
{
  unsigned int i;

  for (i = 0; env[i] != '='; i++)
    if (env[i] != name[i])
      return (0);

  return (++i);
}

/**
 * _makeenv - creates an environment variable
 * 
 * @name: name of the environment variable
 * @value: value of the environment variable
 * 
 * Return: the environment variable
 */
char *_makeenv(const char *name, const char *value)
{
  char *env;

  env = malloc(sizeof(char) * (_strlen(name) + _strlen(value) + 2));
  if (env == NULL)
    return NULL;

  _strcat(env, name);
  _strcat(env, "=");
  _strcat(env, value);

  return env;
}

/**
 * _getenv - gets the value of an environment variable
 *
 * @_environ: environment variable
 * @name: name of the environment variable
 *
 * Return: the value of the environment variable
 */
char *_getenv(char *const *_environ, const char *name)
{
  unsigned int i, offset;

  for (i = 0; _environ[i]; i++)
  {
    offset = _envcmp(_environ[i], name);
    if (offset)
      return (_environ[i] + offset);
  }

  return (NULL);
}

/**
 * _setenv - modifies or adds an environment variable to the environment
 * 
 * @_environ: environment variable
 * @name: name of the environment variable
 * @value: value of the environment variable
 * 
 * Return: the modified environment
 */
char **_setenv(char **_environ, const char *name, const char *value)
{
  unsigned int i;
  char *env;

  for (i = 0; _environ[i]; i++)
    if (_envcmp(_environ[i], name))
      break;

  env = _makeenv(name, value);
  if (env == NULL)
    return NULL;

  if (_environ[i] == NULL)
  {
    _environ = _realloc2(_environ, i, sizeof(char *) * (i + 1));
    if (_environ == NULL)
      return NULL;

    _environ[i] = env;
    _environ[i + 1] = NULL;
  }
  else
  {
    free(_environ[i]);
    _environ[i] = env;
  }

  return (_environ);
}


/**
 * _unsetenv - removes an environment variable from the environment
 * 
 * @_environ: environment variable
 * @name: name of the environment variable
 * 
 * Return: the modified environment
 */
char **_unsetenv(char **_environ, const char *name)
{
  unsigned int i;

  for (i = 0; _environ[i]; i++)
    if (_envcmp(_environ[i], name))
      break;

  if (_environ[i])
  {
    free(_environ[i]);
    for (; _environ[i]; i++)
      _environ[i] = _environ[i + 1];

    // shrink the array by 1
    _environ = _realloc2(_environ, i, sizeof(char *) * (i - 1));
  }

  return (_environ);
}
