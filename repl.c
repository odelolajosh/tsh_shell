#include "tsh.h"
#include "parser.h"
#include "util.h"
#include "cd.h"
#include "env.h"

/**
 * prompt - Display the shell prompt and read a line of input
 * @line: pointer to the line buffer
 * @len: pointer to the line buffer size
 *
 * Return: number of characters read, or -1 on failure
 */
size_t prompt(char **line, size_t *len)
{
  char *cwd = _getcwdname(), prompt_str[] = "> ";

  write(STDOUT_FILENO, cwd, _strlen(cwd));
  write(STDOUT_FILENO, prompt_str, 2);

  free(cwd);
  return getline(line, len, stdin);
}

/**
 * tsh_repl - Read-Eval-Print-Loop for the shell
 *
 * @tsh: tsh shell data
 */
void tsh_repl(tsh_t *tsh)
{
  while (prompt(&tsh->line, &tsh->line_size) != -1)
  {
    int status, i;
    line_node *line_head = NULL, *current_line;
    sep_node *sep_head = NULL, *current_sep;
    command_t *command;

    parse_line(&line_head, &sep_head, tsh->line);

    current_line = line_head;
    current_sep = sep_head;

    while (current_line != NULL)
    {
      command = parse_command(current_line->line);
      if (command == NULL)
        break;

      status = tsh_execute(tsh, command);

      free_command(command);

      if (current_sep != NULL)
      {
        if (current_sep->sep == '&' && status != EXIT_SUCCESS)
          break;

        if (current_sep->sep == '|' && status == EXIT_SUCCESS)
          break;

        current_sep = current_sep->next;
      }

      if (status == EXIT_TSH)
        break;

      current_line = current_line->next;
    }

    free_line_list(line_head);
    free_sep_list(sep_head);
    free(tsh->line);
    tsh->line = NULL;

    if (status == EXIT_TSH)
      break;
  }
}
