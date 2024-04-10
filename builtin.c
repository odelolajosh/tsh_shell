#include "tsh.h"
#include "strings.h"

int (*get_builtin(const char *name))(tsh_t *, command_t *)
{
  builtin_t builtins[] = {
		{ "exit", tsh_exit },
		{ "cd", tsh_cd },
		{ "pwd", tsh_pwd },
		{ "env", tsh_env },
		{ "setenv", tsh_setenv },
		{ "unsetenv", tsh_unsetenv },
		{ NULL, NULL }
	};
  int i = 0;

  while (builtins[i].name)
  {
    if (_strcmp(builtins[i].name, name) == 0)
      return (builtins[i].handl);
    i++;
  }

  return (NULL);
}