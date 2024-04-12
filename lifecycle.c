#include "tsh.h"
#include "strings.h"

/**
 * Creates a new Tsh instance and initializes its members.
 *
 * @param Tsh   Pointer to the Tsh instance to be created.
 * @param argv  Command-line arguments passed to the Tsh program.
 * @return      0 on success, -1 on failure.
 */
int tsh_create(tsh_t *Tsh, char **argv)
{
  unsigned int len;

  Tsh->line = NULL;
  Tsh->line_size = 0;
  Tsh->exitcode = 0;
  Tsh->name = argv[0];
  Tsh->pid = _itoa(getpid());

  for (len = 0; environ[len]; len++)
    ;

  Tsh->environ = malloc(sizeof(char *) * (len + 1));
  if (Tsh->environ == NULL)
    return (-1);

  for (len = 0; environ[len]; len++)
    Tsh->environ[len] = _strdup(environ[len]);
  Tsh->environ[len] = NULL;

  return (0);
}

/**
 * Frees the memory allocated for the Tsh structure and its associated data.
 *
 * @param Tsh A pointer to the Tsh structure to be destroyed.
 * @return 0 on success.
 */
int tsh_destroy(tsh_t *Tsh)
{
  unsigned int len;

  for (len = 0; Tsh->environ[len]; len++)
    free(Tsh->environ[len]);
  free(Tsh->environ);

  free(Tsh->pid);
  return (0);
}
