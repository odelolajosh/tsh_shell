#ifndef TSH_PARSER_H
#define TSH_PARSER_H

#include "tsh.h"

/* parser.c */
char try_delimiter(char *s);
size_t traverse_command(char *line, char *sep);
int can_traverse_command(tsh_t *tsh);
command_t *parse_command(char *cmd);
void free_command(command_t *command);
void print_command(command_t *command);
char **tsh_split_line(char *);

#endif /* TSH_PARSER_H */
