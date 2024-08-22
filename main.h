#ifndef simple_shell
#define simple_shell
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
char *command_in_path(char *command);
char *_getenv(char *data);
char count_tok(char *line);
char **tokenizar(char *command);
int command_in_shell(char *line);
#endif
