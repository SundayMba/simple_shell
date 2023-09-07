#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void prompt_user(void);
int get_N_token(char *buffer, char *sep);
char **tokenize_buffer(char *buffer, char *sep);
#endif
