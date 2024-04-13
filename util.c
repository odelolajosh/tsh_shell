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
