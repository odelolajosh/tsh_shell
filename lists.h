#ifndef _TSH_LISTS_H
#define _TSH_LISTS_H

#include "strings.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct str_node_s
{
  struct str_node_s *next;
  char *str;
} str_node;

typedef struct int_node_s
{
  struct int_node_s *next;
  int num;
} int_node;

str_node *add_str_node_end(str_node *head, char *str);
str_node *free_str_list(str_node *head);
void print_str_list(str_node *head);

int_node *add_int_node_end(int_node *head, char num);
int_node *free_int_list(int_node *head);
void print_int_list(int_node *head, int isChar);

#endif /* _TSH_LISTS_H */