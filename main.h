#ifndef simple_shell
#define simple_shell
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
char *command_in_path(const char *command);
#endif
