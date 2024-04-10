#include "lists.h"

sep_node *add_sep_node_end(sep_node *head, char sep)
{
  sep_node *new_node, *current;

  new_node = malloc(sizeof(sep_node));
  if (new_node == NULL)
    return (NULL);

  new_node->sep = sep;
  new_node->next = NULL;

  if (head == NULL)
    return (new_node);

  current = head;
  while (current->next != NULL)
    current = current->next;

  current->next = new_node;
  return (head);
}

sep_node *free_sep_list(sep_node *head)
{
  sep_node *current = head;
  sep_node *next;

  while (current != NULL)
  {
    next = current->next;
    free(current);
    current = next;
  }

  return (NULL);
}

void print_sep_list(sep_node *head)
{
  sep_node *current = head;

  while (current != NULL)
  {
    printf("%c\n", current->sep);
    current = current->next;
  }
}