#ifndef PARSER_H
#define PARSER_H

#include "tsh.h"
#include "lists.h"

void parse_line(line_node **, sep_node **, char *);
command_t *parse_command(char *cmd);

/**
 * parse_pipeline - Parses a pipeline string into a pipeline_t struct.
 * Parses str into a freshly allocated pipeline_struct and returns a pointer to
 * it.  All cmd_structs in cmds will also be freshy allocated, and have their
 * redirects set to -1, ie no redirect.
 */
pipeline_t *parse_pipeline(char *cmd);

void free_command(command_t *command);

/* For debugging purposes. */
void print_command(command_t *command);
void print_pipeline(pipeline_t *pipeline);
int (*assign_pipes(pipeline_t *pipeline))[2];

#endif /* PARSER_H */