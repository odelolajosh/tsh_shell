# TODO

`make test` currently reports 13 passed and 15 failed. Every failure maps to an item under Bugs.

## Bugs

Ordered by impact; fix the top ones first.

- [ ] **Every input line reads uninitialized memory** (`getline.c:41`).
  - `_realloc(NULL, …)` returns unset memory, and `_strncat` then searches it for a string end.
  - Because of this, `make test-asan` fails on every test.
  - Fix: allocate with `calloc`, or set the first byte to `'\0'`.
- [ ] **`_getline` reads past the end of its buffer** (`getline.c:38`).
  - `_strchr(buffer + i, '\n')` searches a buffer that has no terminating null byte.
  - It can read past the end, or match a newline left over from an earlier read.
- [ ] **`exit` always exits with 255** (`executor.c:137`).
  - The built-in's return value, `TSH_EXIT`, overwrites `tsh->status`.
  - Fix: signal the exit some other way, for example a flag on `tsh_t`.
- [ ] **A failed `execve` leaves a second shell running** (`executor.c:105`).
  - The child process doesn't exit when `execve` fails, so it carries on as a copy of the shell.
  - Fix: call `_exit(127)` in the child.
  - Related: `is_executable` (`executor.c:32`) accepts directories. Fix it with an `S_ISREG` check.
- [ ] **Output loses characters** (`put.c:20`). The character that arrives when the 64-byte buffer is full is dropped. Store it before flushing.
- [ ] **Output isn't flushed at exit**, so the last line can lose its newline.
- [ ] **`pwd` output comes out in the wrong order** (`builtins.c:108`). It uses `printf` while the rest of the shell uses its own buffered output. Switch it to `_puts`.
- [ ] **`&&` and `||` throw away the rest of the line** (`parser.c:62-66`).
  - `false && echo no; echo after` prints nothing.
  - Fix: skip only the next command.
- [ ] **Variable lookup matches on prefix** (`env.c:16`).
  - `setenv PATHX /nope` overwrites `PATH`.
  - Fix: check that `name[i] == '\0'` when the loop reaches `=`.
- [ ] **`cd` crashes when `HOME`, `PWD` or `OLDPWD` is unset** (`builtins.c:66-85`). Add NULL checks.
- [ ] **`_makeenv` appends to uninitialized memory** (`env.c:39`). `malloc` is followed directly by `_strcat`.
- [ ] **Lines longer than 1024 bytes are split into two commands.**
- [ ] **`_realloc2` units are inconsistent** (`parser.c:198`).
  - The call passes sizes in bytes, but `_realloc2` treats them as numbers of pointers.
  - With 64 or more arguments, it writes past the end of the array.
- [ ] **Unsetting the last variable writes out of bounds** (`env.c:132`). `_realloc2(…, 0)` returns a zero-length block, then one element is written into it.
- [ ] **`status` in `tsh_repl` is read before it's set** (`repl.c:12`).
- [ ] **`tsh_destroy` never runs** because `tsh_repl` calls `exit()` first (`repl.c:31`).
  - It also compares a `FILE *` with `STDIN_FILENO` (`lifecycle.c:56`), so it would close stdin if it did run.
- [ ] **Exit status after a signal is garbage** (`executor.c:121`). Return `128 + signal number` instead.
- [ ] **SIGINT handler is unsafe** (`input.c:13`).
  - It calls `prompt()`, which uses `malloc` and isn't safe inside a signal handler.
  - It also prints a prompt while a program is running in the foreground.
- [ ] **The flush marker `char c == -1` (`TSH_BUF_FLUSH`) is not portable.** It never matches on platforms where `char` is unsigned.

## Cleanup

- [ ] Remove or use the dead code:
  - `lists.c` / `lists.h`, `_memmove`, `_strncmp` (which also has an off-by-one) and `print_command`.
  - `DEBUG`, `RC_FLUSH` / `RC_NOFLUSH`, `pipeline_t`, `command_t.redirects` and `tsh->pid`.
- [ ] Replace the `TSH_BUF_FLUSH` character with a separate flush function.
- [ ] Include the command name in error messages, as `sh` does: `tsh: 1: foo: not found`.

## Features

- [ ] Variable expansion: `$VAR`, `$?` and `$$`. `tsh->pid` is already stored for `$$`.
- [ ] `#` comments.
- [ ] Quoting: `'…'` and `"…"`.
- [ ] Pipes: `|`. The `pipeline_t` type is already defined.
- [ ] Redirection: `>`, `>>` and `<`. The `command_t.redirects` field is already defined.
- [ ] `alias`.
- [ ] History.
- [ ] A startup file such as `~/.tshrc`.

## Infrastructure

- [ ] Run `make test` and `make test-asan` in CI on Linux and macOS.
- [ ] Add a regression test for each bug as it's fixed.
- [ ] Check for leaks with `leaks` or Valgrind once `tsh_destroy` runs.

## Done

- [x] Read–execute loop, with interactive and non-interactive modes.
- [x] Script mode (`./tsh file`), with `sh`-compatible exit codes 126 and 127.
- [x] `PATH` lookup, plus `fork` / `execve` / `waitpid`.
- [x] `;` separator. `&&` and `||` work for simple two-command cases.
- [x] Built-ins: `cd`, `cd -`, `pwd`, `env`, `setenv`, `unsetenv` and `exit` (all with the bugs listed above).
- [x] Ctrl-C doesn't kill the shell.
- [x] Makefile with `-Werror`, plus `asan`, `test` and `test-asan` targets.
- [x] 28-case regression suite (`tests/run.sh`).
- [x] Merged the split source files and organized the headers.
