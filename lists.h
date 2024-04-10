#ifndef _TSH_LISTS_H
#define _TSH_LISTS_H

#include "strings.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct line_node_s
{
  struct line_node_s *next;
  char *line;
} line_node;

typedef struct sep_node_s
{
  struct sep_node_s *next;
  char sep;
} sep_node;

line_node *add_line_node_end(line_node *head, char *line);
line_node *free_line_list(line_node *head);
void print_line_list(line_node *head);

sep_node *add_sep_node_end(sep_node *head, char sep);
sep_node *free_sep_list(sep_node *head);
void print_sep_list(sep_node *head);

#endif /* _TSH_LISTS_H */