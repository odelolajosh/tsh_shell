#include "tsh.h"
#include <string.h>
#include "strings.h"
#include "env.h"

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
  int i = 0;

  while (path[i] != '\0')
  {
    if (path[i] == '.')
    {
      if (path[i + 1] == '/')
        i++;
      else if (path[i + 1] == '.' && path[i + 2] == '/')
        i += 2;
      else
        return 0;
    }

    i++;
  }

  return 1;
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
    return 0;

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
  char *paths, *path, *xpath;

  if (is_executable(name))
    return _strdup(name);

  if (PATH == NULL)
    return NULL;

  paths = _strdup(PATH);
  path = strtok(paths, ":");
  while (path)
  {
    xpath = malloc(strlen(path) + strlen(name) + 2);
    if (xpath == NULL)
      return NULL;

    xpath = _strdup(path);
    xpath = _strcat(xpath, "/");
    xpath = _strcat(xpath, name);
    xpath = _strcat(xpath, "\0");

    if (is_executable(xpath))
    {
      free(paths);
      return (xpath);
    }

    free(xpath);
    path = strtok(NULL, ":");
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
  int sys;

  if (child_pid == 0)
  {
    execve(file, argv, environ);
  }
  else if (child_pid < 0)
  {
    write(STDERR_FILENO, "omooo\n", 10);
    return -1;
  }
  else
  {
    do
    {
      waitpid(child_pid, &sys, WUNTRACED);
    } while (!WIFEXITED(sys) && !WIFSIGNALED(sys));
  }

  return (sys / 256);
}

/**
 * tsh_execute - Execute a command
 * @tsh: tsh shell data
 * @command: command to execute
 *
 * Return: 0 on success, -1 on failure
 */
int tsh_execute(tsh_t *tsh, command_t *command)
{
  int (*builtin_handl)(tsh_t *tsh, command_t *command);
  char *file;
  int exitcode;

  builtin_handl = get_builtin(command->name);
  if (builtin_handl != NULL)
    return builtin_handl(tsh, command);

  file = _which(tsh->environ, command->name);
  if (file)
  {
    exitcode = execute(file, command->argv, tsh->environ);
    free(file);
    return (exitcode);
  }

  write(STDERR_FILENO, "tsh: command not found\n", 24);
  return (127);
}