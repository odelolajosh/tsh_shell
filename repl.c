#include "tsh.h"
#include "parsers.h"
#include "utils.h"

/**
 * tsh_repl - Read-Eval-Print-Loop for the shell
 *
 * @tsh: tsh shell data
 */
void tsh_repl(tsh_t *tsh)
{
  int status;

  while (read_command(tsh) != (size_t)-1)
  {

    if (tsh->line_size)
    {
      tsh->command = parse_command(tsh->line);
      if (tsh->command == NULL)
        continue;

      status = tsh_execute(tsh);
      free_command(tsh->command);
    }

    if (status == TSH_EXIT)
      break;
  }

  exit(tsh->status);
}
