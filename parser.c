#include <string.h>
#include "tsh.h"
#include "parsers.h"
#include "strings.h"
#include "utils.h"

/**
 * try_delimiter - tries to identify and return a delimiter character from the given string.
 * Delimiter characters include ';', '||', and '&&'.
 *
 * @param s The string to check for a delimiter.
 * @return The delimiter character found, or -1 if no delimiter is found.
 */
char try_delimiter(char *s)
{
  if (*s == '\0')
    return '\0';

  if (*s == ';')
    return ';';

  if (*s == '|' && *(s + 1) == '|')
    return '|';

  if (*s == '&' && *(s + 1) == '&')
    return '&';

  return -1;
}

/**
 * traverse_command - extract command by delimiter
 * @line: line
 * @sep: pointer to the separator character
 * @size: pointer to the size of the command
 *
 * Return: the length of the isolated command
 */
size_t traverse_command(char *line, char *sep)
{
  size_t i = 0;
  char delimiter;

  while ((delimiter = try_delimiter(line + i)) == -1)
    i++;

  *(line + i) = '\0'; // replace delimiter with null byte

  if (delimiter == '|' || delimiter == '&')
  {
    i++;
    *(line + i) = '\0';
  }

  *sep = delimiter;

  return (i);
}

int can_traverse_command(tsh_t *tsh)
{
  if (tsh->sep == '|' && tsh->status == 0)
    return (0);

  if (tsh->sep == '&' && tsh->status != 0)
    return (0);

  return (1);
}
