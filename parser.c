#include <string.h>
#include "tsh.h"
#include "parser.h"
#include "strings.h"
#include "util.h"

/**
 * parse_line - Parse a line into commands and separators
 * @lines: pointer to the head of the line list
 * @seps: pointer to the head of the separator list
 * @line: line to parse
 */
void parse_line(line_node **lines, sep_node **seps, char *line)
{
  int start, end;
  char *token;

  // split the line into commands using ';', '||', '&&' as delimiters
  start = end = 0;
  while (line[end])
  {
    if (line[end] == ';' || (line[end] == '|' && line[end + 1] == '|') || (line[end] == '&' && line[end + 1] == '&'))
    {
      token = _substring(line, start, end);
      *lines = add_line_node_end(*lines, token);
      *seps = add_sep_node_end(*seps, line[end]);
      free(token);

      if (line[end] == '|' || line[end] == '&')
        end += 2;
      else
        end += 1;

      start = end;
    }
    else
      end++;
  }

  // add the last command
  token = _substring(line, start, end);
  *lines = add_line_node_end(*lines, token);
  free(token);
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
  command->redirects[0] = command->redirects[1] = -1;

  command->argc = 0;
  while (command->argv[command->argc] != NULL)
    command->argc++;

  return command;
}

void free_command(command_t *command)
{
  if (command == NULL)
    return;
  if (command->name)
    free(command->name);
  if (command->argv)
    free(command->argv);
  free(command);
}

pipeline_t *parse_pipeline(char *cmd)
{
  pipeline_t *pipeline = malloc(sizeof(pipeline_t));
  int i, n_commands = 0;
  char *command;

  if (pipeline == NULL)
  {
    write(STDERR_FILENO, ": allocation error\n", 18);
    exit(EXIT_FAILURE);
  }

  for (i = 0; cmd[i]; i++)
    if (cmd[i] == '|')
      ++n_commands;

  pipeline->len = ++n_commands;
  pipeline->commands = malloc(sizeof(command_t *) * (n_commands + 1)); // +1 for NULL

  if (pipeline->commands == NULL)
  {
    write(STDERR_FILENO, ": allocation error\n", 18);
    exit(EXIT_FAILURE);
  }

  // use strtok to split the pipeline into commands
  command = strtok(cmd, "|");
  for (i = 0; command; i++)
  {
    pipeline->commands[i] = parse_command(command);
    command = strtok(NULL, "|");
  }

  pipeline->commands[i] = NULL;

  return pipeline;
}

int (*assign_pipes(pipeline_t *pipeline))[2]
{
  int n_pipes = pipeline->len - 1, i;
  int(*pipes)[2] = malloc(sizeof(int) * n_pipes * 2);

  if (pipes == NULL)
  {
    write(STDERR_FILENO, ": allocation error\n", 18);
    exit(EXIT_FAILURE);
  }

  for (i = 1; i < pipeline->len; i++)
  {
    pipe(pipes[i - 1]);
    pipeline->commands[i - 1]->redirects[STDOUT_FILENO] = pipes[i - 1][1];
    pipeline->commands[i]->redirects[STDIN_FILENO] = pipes[i - 1][0];
  }

  return pipes;
}

void print_command(command_t *command)
{
  char **arg;
  int i;

  if (command == NULL)
  {
    fprintf(stderr, "command is NULL\n");
    return;
  }

  arg = command->argv;
  fprintf(stderr, "progname: %s\n", command->name);

  for (i = 0, arg = command->argv; *arg; ++arg, ++i)
  {
    fprintf(stderr, "  args[%d]: %s\n", i, *arg);
  }
}

void print_pipeline(pipeline_t *pipeline) {}

char *tsh_read_line(void)
{
  return NULL;
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

  token = strtok(line, TSH_TOK_DELIM);
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
        exit(EXIT_FAILURE);
      }
    }
    argv[i] = _strdup(token);
    token = strtok(NULL, TSH_TOK_DELIM);
  }
  argv[i] = NULL;

  return (argv);
}
