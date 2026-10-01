#include <string.h>
#include "tsh.h"
#include "parser.h"
#include "tsh_strings.h"
#include "utils.h"

/**
 * try_delimiter - tries to identify and return a delimiter character from the given string.
 * Delimiter characters include ';', '||', and '&&'.
 *
 * @param s The string to check for a delimiter.
 * @return The delimiter character found, or -1 if no delimiter is found.
 */
char try_delimiter(char *s)
{
  if (*s == '\0')
    return '\0';

  if (*s == ';')
    return ';';

  if (*s == '|' && *(s + 1) == '|')
    return '|';

  if (*s == '&' && *(s + 1) == '&')
    return '&';

  return -1;
}

/**
 * traverse_command - extract command by delimiter
 * @line: line
 * @sep: pointer to the separator character
 * @size: pointer to the size of the command
 *
 * Return: the length of the isolated command
 */
size_t traverse_command(char *line, char *sep)
{
  size_t i = 0;
  char delimiter;

  while ((delimiter = try_delimiter(line + i)) == -1)
    i++;

  *(line + i) = '\0'; // replace delimiter with null byte

  if (delimiter == '|' || delimiter == '&')
  {
    i++;
    *(line + i) = '\0';
  }

  *sep = delimiter;

  return (i);
}

int can_traverse_command(tsh_t *tsh)
{
  if (tsh->sep == '|' && tsh->status == 0)
    return (0);

  if (tsh->sep == '&' && tsh->status != 0)
    return (0);

  return (1);
}

/**
 * parse_command - Parses a command string into a command_t struct.
 * Parses str into a freshly allocated cmd_struct and returns a pointer to it.
 * The redirects in the returned cmd_struct will be set to -1, ie no redirect.
 * @line: command string to parse
 *
 * Return: pointer to the command struct
 */
command_t *parse_command(char *line)
{
  command_t *command;

  command = malloc(sizeof(command_t));
  if (command == NULL)
  {
    write(STDERR_FILENO, ": allocation error\n", 18);
    exit(EXIT_FAILURE);
  }

  command->argv = tsh_split_line(line);
  if (command->argv == NULL)
  {
    free(command);
    return (NULL);
  }
  command->name = _strdup(command->argv[0]);
  if (command->name == NULL)
  {
    free(command->argv);
    free(command);
    return (NULL);
  }

  command->redirects[0] = command->redirects[1] = -1;

  command->argc = 0;
  while (command->argv[command->argc] != NULL)
    command->argc++;

  return command;
}

/**
 * free_command - frees the memory allocated for a command structure.
 *
 * @param command The command structure to free.
 */
void free_command(command_t *command)
{
  int i = 0;

  if (command == NULL)
    return;
  if (command->name)
    free(command->name);
  if (command->argv)
  {
    while (command->argv[i])
    {
      free(command->argv[i]);
      i++;
    }
    free(command->argv);
  }
  free(command);
}

/**
 * print_command - prints the command details.
 *
 * @param command A pointer to the command_t struct representing the command.
 */
void print_command(command_t *command)
{
  char **arg;
  int i;

  if (command == NULL)
  {
    _eputs("command is NULL\n");
    return;
  }

  arg = command->argv;
  _eputs("command->name: ");
  _eputs(command->name);
  _eputs("\n");

  for (i = 0, arg = command->argv; *arg; ++arg, ++i)
  {
    _eputs("  args[");
    _eputc(i + '0');
    _eputs("]: ");
    _eputs(*arg);
    _eputs("\n");
  }
  _putc(TSH_BUF_FLUSH);
}

char **tsh_split_line(char *line)
{
  char **argv;
  char *token;
  size_t bufsize, i;

  bufsize = TSH_TOK_BUFSIZE;
  argv = malloc(sizeof(char *) * (bufsize));
  if (!argv)
    return (NULL);

#if TSH_IMPL
  token = _strtok(line, TSH_TOK_DELIM);
#else
  token = strtok(line, TSH_TOK_DELIM);
#endif

  if (!token)
  {
    free(argv);
    return (NULL);
  }

  for (i = 0; token; i++)
  {
    if (i == bufsize)
    {
      bufsize += TSH_TOK_BUFSIZE;
      argv = _realloc2(argv, sizeof(char *) * i, sizeof(char *) * bufsize);
      if (argv == NULL)
      {
        write(STDERR_FILENO, ": allocation error\n", 18);
        return (NULL);
      }
    }
    argv[i] = _strdup(token);
    if (argv[i] == NULL)
    {
      write(STDERR_FILENO, ": allocation error\n", 18);
      return (NULL);
    }

#if TSH_IMPL
    token = _strtok(NULL, TSH_TOK_DELIM);
#else
    token = strtok(NULL, TSH_TOK_DELIM);
#endif
  }
  argv[i] = NULL;

  return (argv);
}
