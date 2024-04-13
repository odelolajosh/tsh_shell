#include "parsers.h"
#include "strings.h"
#include <string.h>

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

#if TSH_IMPL
  command = _strtok(cmd, "|");
#else
  command = strtok(cmd, "|");
#endif

  for (i = 0; command; i++)
  {
    pipeline->commands[i] = parse_command(command);
#if TSH_IMPL
    command = _strtok(NULL, "|");
#else
    command = strtok(NULL, "|");
#endif
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

void print_pipeline(pipeline_t *pipeline) {
  (void) pipeline;
}
