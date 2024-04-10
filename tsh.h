#ifndef TSH_H
#define TSH_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#define TSH_RL_BUFSIZE 1024
#define TSH_TOK_BUFSIZE 64
#define TSH_TOK_DELIM " \t\r\n\a"

#define DEBUG 1

// The exit status of the shell
#define EXIT_TSH -1

/**
 * struct command - command
 * @name: name of the executable
 * @argv: arguments to pass to the executable
 * @redirects: IO redirections; redirect[i] should be used as fd i in the child.
*/
typedef struct command {
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
typedef struct pipeline {
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
typedef struct tsh {
	char *line;
	size_t line_size;
	char **environ;
	char *name;
	char *pid;
	int exitcode;
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
	int (*handl)(tsh_t *tsh, command_t *command);
} builtin_t;

extern char **environ;

int tsh_create(tsh_t *, char **);
int tsh_destroy(tsh_t *);
void tsh_repl(tsh_t *);
char *tsh_read_line(void);
char **tsh_split_line(char *);
int tsh_execute(tsh_t *tsh, command_t *);

// Builtins
int (*get_builtin(const char *name))(tsh_t *, command_t *);
int tsh_exit(tsh_t *, command_t *);
int tsh_cd(tsh_t *, command_t *);
int tsh_pwd(tsh_t *, command_t *);
int tsh_env(tsh_t *, command_t *);
int tsh_setenv(tsh_t *, command_t *);
int tsh_unsetenv(tsh_t *, command_t *);

#endif /* TSH_H */