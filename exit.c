#include "tsh.h"
#include "strings.h"

int tsh_exit(tsh_t *tsh, command_t *command)
{
  int status = 0;

  if (command->argv[1] != NULL)
  {
    if (!_isdigit(command->argv[1]))
    {
      write(STDERR_FILENO, "exit: Illegal number: ", 22);
      write(STDERR_FILENO, command->argv[1], _strlen(command->argv[1]));
      write(STDERR_FILENO, "\n", 1);
      
      return (2);
    }
    status = _atoi(command->argv[1]);
    tsh->exitcode = status;

    return (TSH_EXIT);
  }

  return (TSH_EXIT);
}
