#include "tsh.h"

int main(int argc, char **argv)
{
  (void)argc;
  tsh_t tsh;

  // Load config files, if any
  tsh_create(&tsh, argc, argv);

  // Run command loop
  tsh_repl(&tsh);

  // Perform any shutdown/cleanup.
  tsh_destroy(&tsh);

  return EXIT_SUCCESS;
}
