#include "lists.h"

line_node *add_line_node_end(line_node *head, char *line)
{
  line_node *new_node, *current;

  new_node = malloc(sizeof(line_node));
  if (new_node == NULL)
    return (NULL);

  new_node->line = _strdup(line);
  new_node->next = NULL;

  if (head == NULL)
    return (new_node);

  current = head;
  while (current->next != NULL)
    current = current->next;

  current->next = new_node;
  return (head);
}

line_node *free_line_list(line_node *head)
{
  line_node *current = head;
  line_node *next;

  while (current != NULL)
  {
    next = current->next;
    free(current->line);
    free(current);
    current = next;
  }

  return (NULL);
}

void print_line_list(line_node *head)
{
  line_node *current = head;

  while (current != NULL)
  {
    printf("%s\n", current->line);
    current = current->next;
  }
}