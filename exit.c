#include "tsh.h"
#include "strings.h"
#include "utils.h"

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
      _eputchar('\n');

      return (2);
    }
    status = _atoi(tsh->command->argv[1]);
    tsh->exitcode = status;

    return (TSH_EXIT);
  }

  return (TSH_EXIT);
}
