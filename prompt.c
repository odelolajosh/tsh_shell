#include "utils.h"

/**
 * prompt - Display the shell prompt
 */
void prompt(void)
{
  char *cwd = _getcwdname();
  char prompt_str[] = "> ";

  _puts(cwd);
  _puts(prompt_str);
  _putchar(TSH_BUF_FLUSH);

  free(cwd);
}
