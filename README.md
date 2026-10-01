# tsh

A small Unix shell written in C, as a hobby project.

## Build and run

```sh
make          # builds ./tsh
./tsh         # interactive
./tsh script  # run commands from a file
echo 'ls; pwd' | ./tsh
```

## Features

- Runs programs found in `PATH`, or by absolute/relative path
- Command separators: `;`, `&&`, `||`
- Built-ins: `exit [status]`, `cd [dir|-]`, `pwd`, `env`, `setenv NAME VALUE`, `unsetenv NAME`
- Ctrl-C does not kill the shell

Not supported yet: quoting, variable expansion, pipes, redirection, comments.

## Development

```sh
make test       # run the test suite (tests/run.sh)
make asan       # build ./tsh-asan with AddressSanitizer + UBSan
make test-asan  # run the test suite against the sanitizer build
make clean
```

Warnings are errors (`-Wall -Wextra -Werror`).

Tests in `tests/run.sh` pipe input into tsh under a fixed minimal environment
and compare stdout and exit status. Add a case with:

```sh
check "description" 'input line\n' 'expected stdout' expected_status
```

## Layout

| File            | Contents                                         |
| --------------- | ------------------------------------------------ |
| `main.c`        | entry point                                      |
| `lifecycle.c`   | shell state setup/teardown                       |
| `repl.c`        | read–execute loop                                |
| `input.c`       | reading input, splitting on `;` `&&` `\|\|`      |
| `getline.c`     | `_getline` implementation                        |
| `parser.c`      | tokenizing a command into `command_t`            |
| `executor.c`    | `PATH` lookup, fork/exec                         |
| `builtins.c`    | built-in commands                                |
| `env.c`         | environment get/set/unset helpers                |
| `prompt.c`      | prompt                                           |
| `put.c`         | buffered output                                  |
| `strings.c`     | string functions (`_strlen`, `_strtok`, …)       |
| `memory.c`      | `_memcpy`, `_realloc`, …                         |
| `lists.c`       | linked-list helpers                              |
| `util.c`        | misc helpers (cwd, interactive check, file open) |

Headers: `tsh.h` (core types, lifecycle/repl/executor/builtins),
`parser.h`, `utils.h` (env, I/O, misc), `tsh_strings.h` (strings and memory),
`lists.h`.
