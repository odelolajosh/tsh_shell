#include "utils.h"

int interactive(tsh_t *tsh)
{
  return (isatty(STDIN_FILENO) && tsh->fp == stdin);
}

FILE *openfileorexit(const char *path, const char *progname)
{
  FILE *fp = fopen(path, "r");

  if (fp == NULL)
  {
    if (errno == EACCES)
    {
      _eputs("tsh: Permission denied\n");
      exit(126);
    }
    if (errno == ENOENT)
    {
      _eputs((char *)progname);
      _eputs(": 0: Can't open ");
      _eputs((char *)path);
      _eputc('\n');
      _eputc(TSH_BUF_FLUSH);
      exit(127);
    }
    exit(EXIT_FAILURE);
  }

  return fp;
}

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
 * _getcwdname - gets the current working directory name
 * 
 * Return: the current working directory name. NULL if failed.
 * This function is a wrapper for getcwd(3) that allocates
 * memory for the buffer. This memory must be freed by the caller.
 */
char *_getcwdname(void)
{
  char *name, *cwd = _getcwd();
  char *cwdname = _strrchr(cwd, '/');
  if (cwdname == NULL)
    return cwd;
  
  name = _strdup(cwdname + 1);
  free(cwd);
  return name;
}
