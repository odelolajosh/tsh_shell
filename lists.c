#include "lists.h"

str_node *add_str_node_end(str_node *head, char *line)
{
  str_node *new_node, *current;

  new_node = malloc(sizeof(str_node));
  if (new_node == NULL)
    return (NULL);

  new_node->str = _strdup(line);
  new_node->next = NULL;

  if (head == NULL)
    return (new_node);

  current = head;
  while (current->next != NULL)
    current = current->next;

  current->next = new_node;
  return (head);
}

str_node *free_str_list(str_node *head)
{
  str_node *current = head;
  str_node *next;

  while (current != NULL)
  {
    next = current->next;
    free(current->str);
    free(current);
    current = next;
  }

  return (NULL);
}

void print_str_list(str_node *head)
{
  str_node *current = head;

  while (current != NULL)
  {
    printf("%s\n", current->str);
    current = current->next;
  }
}

int_node *add_int_node_end(int_node *head, char num)
{
  int_node *new_node, *current;

  new_node = malloc(sizeof(int_node));
  if (new_node == NULL)
    return (NULL);

  new_node->num = num;
  new_node->next = NULL;

  if (head == NULL)
    return (new_node);

  current = head;
  while (current->next != NULL)
    current = current->next;

  current->next = new_node;
  return (head);
}

int_node *free_int_list(int_node *head)
{
  int_node *current = head;
  int_node *next;

  while (current != NULL)
  {
    next = current->next;
    free(current);
    current = next;
  }

  return (NULL);
}

void print_int_list(int_node *head, int isChar)
{
  int_node *current = head;

  while (current != NULL)
  {
    if (isChar)
      printf("%c\n", current->num);
    else
      printf("%d\n", current->num);
    current = current->next;
  }
}
