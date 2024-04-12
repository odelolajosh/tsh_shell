#include "tsh.h"
#include "strings.h"
#include "utils.h"

/**
 * _setenv - modifies or adds an environment variable
 *
 * @shell: shell data
 * @name: variable name
 * @value: variable value
 * @overwrite: 0 to avoid change otherwise any other integer
 * Return: 0 if successful otherwise 1
 */
int tsh_env(tsh_t *tsh)
{
  unsigned int i;

  for (i = 0; tsh->environ[i]; i++)
  {
    _puts(tsh->environ[i]);
    _putchar('\n');
  }

  return (0);
}

/**
 * tsh_setenv - modifies or adds an environment variable
 * @tsh: shell data
 * @command: command data
 *
 * Return: 0 if successful otherwise 1
 */
int tsh_setenv(tsh_t *tsh)
{
  char **new_environ;

  if (tsh->command->argc != 3)
  {
    _eputs("Usage: setenv <NAME> <VALUE>\n");
    return (1);
  }

  new_environ = _setenv(
      tsh->environ,
      tsh->command->argv[1],
      tsh->command->argv[2]);
  if (new_environ)
  {
    tsh->environ = new_environ;
    return (0);
  }

  perror("setenv");
  return (1);
}

/**
 * tsh_unsetenv - removes an environment variable
 * @tsh: shell data
 *
 * Return: 0 if successful otherwise 1
 */
int tsh_unsetenv(tsh_t *tsh)
{
  char **new_environ;

  if (tsh->command->argc != 2)
  {
    _eputs("Usage: unsetenv <NAME>\n");
    return (1);
  }

  new_environ = _unsetenv(tsh->environ, tsh->command->argv[1]);
  if (new_environ)
  {
    tsh->environ = new_environ;
    return (0);
  }

  perror("unsetenv");
  return (1);
}
