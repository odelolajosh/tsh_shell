#include "tsh.h"
#include "tsh_strings.h"
#include "utils.h"

int (*get_builtin(const char *name))(tsh_t *)
{
  builtin_t builtins[] = {
		{ "exit", tsh_exit },
		{ "cd", tsh_cd },
		{ "pwd", tsh_pwd },
		{ "env", tsh_env },
		{ "setenv", tsh_setenv },
		{ "unsetenv", tsh_unsetenv },
		{ NULL, NULL }
	};
  int i = 0;

  while (builtins[i].name)
  {
    if (_strcmp(builtins[i].name, name) == 0)
      return (builtins[i].handl);
    i++;
  }

  return (NULL);
}

/**
 * tsh_exit - exits the shell
 * @tsh: shell data
 *
 * Return: TSH_EXIT if successful otherwise 2
 */
int tsh_exit(tsh_t *tsh)
{
  int status = 0;

  if (tsh->command->argv[1] != NULL)
  {
    if (!_isdigit(tsh->command->argv[1]))
    {
      _eputs("exit: Illegal number: ");
      _eputs(tsh->command->argv[1]);
      _eputc('\n');

      return (2);
    }
    status = _atoi(tsh->command->argv[1]);
    tsh->status = status;

    return (TSH_EXIT);
  }

  return (TSH_EXIT);
}

/**
 * tsh_cd - changes the current working directory
 * @tsh: shell data
 *
 * Return: 0 if successful otherwise 1
 */
int tsh_cd(tsh_t *tsh)
{
  char *dir = _getenv(tsh->environ, "HOME");
  char *oldpwd = _getenv(tsh->environ, "PWD");

  if (tsh->command->argc > 1)
    dir = tsh->command->argv[1];

  if (dir[0] == '-')
  {
    dir = _getenv(tsh->environ, "OLDPWD");
    write(STDOUT_FILENO, dir, _strlen(dir));
    write(STDOUT_FILENO, "\n", 1);
  }

  if (chdir(dir) == -1)
  {
    perror("cd");
    return 1;
  }

  dir = _getcwd();
  tsh->environ = _setenv(tsh->environ, "OLDPWD", oldpwd);
  tsh->environ = _setenv(tsh->environ, "PWD", dir);
  free(dir);
  return 0;
}

/**
 * tsh_pwd - prints the current working directory
 *
 * @tsh: shell data
 *
 * Return: 0 if successful otherwise 1
 */
int tsh_pwd(tsh_t *tsh)
{
  char *dir = _getenv(tsh->environ, "PWD");

  if (dir == NULL)
  {
    perror("pwd");
    return 1;
  }

  printf("%s\n", dir);
  return 0;
}

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
    _putc('\n');
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
