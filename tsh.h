#ifndef TSH_H
#define TSH_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define TSH_READ_BUFSIZE 1024
#define TSH_WRITE_BUFSIZE 64
#define TSH_BUF_FLUSH -1

#define TSH_TOK_BUFSIZE 64
#define TSH_TOK_DELIM " \t\r\n\a"

// Debug mode (0: off, 1: on)
#define DEBUG 1

// use tsh implementations for getline and strtok
#define TSH_IMPL 1

// The exit status of the shell
#define TSH_EXIT -1

/**
 * struct command - command
 * @name: name of the executable
 * @argv: arguments to pass to the executable
 * @redirects: IO redirections; redirect[i] should be used as fd i in the child.
 */
typedef struct command
{
  /** The name of the executable. */
  char *name;

  /** The arguments to pass to the executable. */
  char **argv;

  /** The number of arguments. */
  int argc;

  /**
   * IO redirections; redirect[i] should be used as fd i in the child.
   * A value of -1 indicates no redirect.
   */
  int redirects[2];
} command_t;

/**
 * struct pipeline - pipeline
 * @len: total number of commands
 * @commands: the commands themselves
 */
typedef struct pipeline
{
  /** The total number of commands. */
  int len;

  /* The commands themselves. */
  command_t **commands;
} pipeline_t;

/**
 * struct tsh - tsh
 *
 * @command: command
 * @line: line
 * @line_size: line size
 * @environ: environment
 * @name: name
 * @pid: pid
 * @exitcode: exit code
 */
typedef struct tsh
{
  char *line;
  size_t line_size;
  command_t *command;
  char sep;
  char **environ;
  char *name;
  char *pid;
  int status;
  FILE *fp;
} tsh_t;

/**
 * struct builtin - builtins
 *
 * @name: name of builtin
 * @handl: builtin handler
 */
typedef struct builtin
{
  char *name;
  int (*handl)(tsh_t *tsh);
} builtin_t;

extern char **environ;

/** lifecycle.c */
int tsh_create(tsh_t *tsh, int argc, char **argv);
int tsh_destroy(tsh_t *);

void tsh_repl(tsh_t *);
char **tsh_split_line(char *);
int tsh_execute(tsh_t *tsh);

// Builtins
int (*get_builtin(const char *name))(tsh_t *);
int tsh_exit(tsh_t *);
int tsh_cd(tsh_t *);
int tsh_pwd(tsh_t *);
int tsh_env(tsh_t *);
int tsh_setenv(tsh_t *);
int tsh_unsetenv(tsh_t *);

#endif /* TSH_H */
