#ifndef PIPEX_H
#define PIPEX_H
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "./get_next_line/get_next_line.h"

// static int word_len(const char *s, char c);
// static int ft_countwords(const char *s, char sep);
// static void *free_arr(char **arr, int j);
char **ft_split(char const *s, char c);
char *ft_substr(char const *s, unsigned int start, size_t len);

#endif