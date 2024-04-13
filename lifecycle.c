#include "tsh.h"
#include "strings.h"
#include "utils.h"

/**
 * tsh_create - Creates a new Tsh instance and initializes its members.
 *
 * @param tsh   Pointer to the Tsh instance to be created.
 * @param argv  Command-line arguments passed to the Tsh program.
 * @return      0 on success, -1 on failure.
 */
int tsh_create(tsh_t *tsh, int argc, char **argv)
{
  unsigned int len;

  if (argc == 2)
    tsh->fp = openfileorexit(argv[1], argv[0]);
  else
    tsh->fp = stdin;

  tsh->line = NULL;
  tsh->line_size = 0;
  tsh->status = 0;
  tsh->name = argv[0];
  tsh->pid = _itoa(getpid());

  for (len = 0; environ[len]; len++)
    ;

  tsh->environ = malloc(sizeof(char *) * (len + 1));
  if (tsh->environ == NULL)
    return (-1);

  for (len = 0; environ[len]; len++)
    tsh->environ[len] = _strdup(environ[len]);
  tsh->environ[len] = NULL;

  return (0);
}

/**
 * Frees the memory allocated for the Tsh structure and its associated data.
 *
 * @param tsh A pointer to the Tsh structure to be destroyed.
 * @return 0 on success.
 */
int tsh_destroy(tsh_t *tsh)
{
  unsigned int len;
  for (len = 0; tsh->environ[len]; len++)
    free(tsh->environ[len]);
  free(tsh->environ);

  free(tsh->pid);

  if (tsh->fp != STDIN_FILENO)
    fclose(tsh->fp);

  return (0);
}
