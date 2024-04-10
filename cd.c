#include "tsh.h"
#include "env.h"
#include "strings.h"
#include "cd.h"

/**
 * _getcwd - gets the current working directory
 *
 * Return: the current working directory. NULL if failed.
 * This function is a wrapper for getcwd(3) that allocates
 * memory for the buffer. This memory must be freed by the caller.
 */
char *_getcwd(void)
{
  long size;
  char *buf, *ptr;

  size = pathconf(".", _PC_PATH_MAX);
  if ((buf = (char *)malloc((size_t)size)) != NULL)
  {
    ptr = getcwd(buf, (size_t)size);
    if (ptr != NULL)
      return buf;
    free(buf);
  }

  return NULL;
}

/**
 * tsh_cd - changes the current working directory
 *
 * @tsh: shell data
 *
 * Return: 0 if successful otherwise 1
 */
int tsh_cd(tsh_t *tsh, command_t *command)
{
  char *dir = _getenv(tsh->environ, "HOME");
  char *oldpwd = _getenv(tsh->environ, "PWD");

  if (command->argc > 1)
    dir = command->argv[1];

  if (dir[0] == '-')
    dir = _getenv(tsh->environ, "OLDPWD");

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
int tsh_pwd(tsh_t *tsh, command_t *command)
{
  (void)command;
  char *dir = _getenv(tsh->environ, "PWD");

  if (dir == NULL)
  {
    perror("pwd");
    return 1;
  }

  printf("%s\n", dir);
  return 0;
}