#include "tsh.h"
#include "parsers.h"
#include "util.h"
#include "cd.h"
#include "envs.h"

/**
 * tsh_repl - Read-Eval-Print-Loop for the shell
 *
 * @tsh: tsh shell data
 */
void tsh_repl(tsh_t *tsh)
{
  while (read_command(tsh) != -1)
  {
    command_t *command;

    if (tsh->line_size)
    {
      command = parse_command(tsh->line);
      if (command == NULL)
        break;

      tsh_execute(tsh, command);
      free_command(command);
    }

    if (tsh->exitcode == TSH_EXIT)
      break;
  }
}
