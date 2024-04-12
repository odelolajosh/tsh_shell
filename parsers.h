#ifndef PARSER_H
#define PARSER_H

#include "tsh.h"

/* parser.c */
char try_delimiter(char *s);
size_t traverse_command(char *line, char *sep);
int can_traverse_command(tsh_t *tsh);

/* parser2.c */
command_t *parse_command(char *cmd);
void print_command(command_t *command);
void free_command(command_t *command);

/* parser3.c */
pipeline_t *parse_pipeline(char *cmd);
void print_pipeline(pipeline_t *pipeline);

#endif /* PARSER_H */