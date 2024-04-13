#include "tsh.h"
#include <string.h>
#include "strings.h"
#include "utils.h"

/**
 * is_valid_path - Check if a path is valid
 * @path: path to check
 * Return: 1 if path is valid, 0 otherwise
 *
 * A path is valid if it contains at least one '/' character.
 * A valid path can have .. or . in it.
 */
int is_valid_path(const char *path)
{
  return (_strchr((char *)path, '/') != NULL);
}

/**
 * is_executable - Check if a file is executable
 * @path: path to file
 * Return: 1 if file is executable, 0 otherwise
 */
int is_executable(const char *path)
{
  struct stat sb; // stat buffer

  if (is_valid_path(path) == 0)
    return (0);

  return (stat(path, &sb) == 0 && sb.st_mode & S_IXUSR);
}

/**
 * _which - Find the full path of a command
 * @name: name of the command
 * Return: full path of the command
 */
char *_which(char *const *environ, const char *name)
{
  char *PATH = _getenv(environ, "PATH");
  char *paths, *path, *x;

  if (is_executable(name))
    return _strdup(name);

  if (PATH == NULL)
    return NULL;

  paths = _strdup(PATH);
  if (paths == NULL)
    return (NULL);

#if TSH_IMPL
  path = _strtok(paths, ":");
#else
  path = strtok(paths, ":");
#endif

  while (path)
  {
    x = malloc(_strlen(path) + _strlen(name) + 2);
    if (x == NULL)
    {
      free(paths);
      return (NULL);
    }

    _strcpy(x, path);
    _strcat(x, "/");
    _strcat(x, name);
    _strcat(x, "\0");

    if (is_executable(x))
    {
      free(paths);
      return (x);
    }

    free(x);
#if TSH_IMPL
    path = _strtok(NULL, ":");
#else
    path = strtok(NULL, ":");
#endif
  }

  free(paths);
  return (NULL);
}

/**
 * _execute - Execute a command
 * @tsh: tsh shell data
 * Return: 0 on success, -1 on failure
 */
int execute(const char *file, char *const *argv, char *const *environ)
{
  pid_t child_pid = fork();
  int sys = 0;

  if (child_pid == 0)
  {
    execve(file, argv, environ);
    perror("tsh: execve");
  }
  else if (child_pid < 0)
  {
    _eputs("tsh: omooo\n");
    return (-1);
  }
  else
  {
    do
    {
      waitpid(child_pid, &sys, WUNTRACED);
    } while (!WIFEXITED(sys) && !WIFSIGNALED(sys));
  }

  return WEXITSTATUS(sys);
}

/**
 * tsh_execute - Execute a command
 * @tsh: tsh shell data
 *
 * Return: 0 on success, -1 on failure
 */
int tsh_execute(tsh_t *tsh)
{
  int (*builtin_handl)(tsh_t *tsh);
  char *file;

  builtin_handl = get_builtin(tsh->command->name);
  if (builtin_handl != NULL)
    tsh->status = builtin_handl(tsh);
  else if ((file = _which(tsh->environ, tsh->command->name)))
  {
    tsh->status = execute(file, tsh->command->argv, tsh->environ);
    free(file);
  }
  else
  {
    _eputs("tsh: command not found\n");
    tsh->status = 127;
  }

  return (tsh->status);
}
