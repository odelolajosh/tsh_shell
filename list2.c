#include "lists.h"

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
