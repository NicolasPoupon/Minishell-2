/*
** EPITECH PROJECT, 2021
** minishell.c
** File description:
** minishell1
*/

#include "../include/my.h"
#include "../include/p.h"
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int chdir_error(char *pathname)
{
    put_error_int(pathname);
    free(pathname);
    return put_error_int(": Not a directory.\n");
}

void if_free(char *str)
{
    if (str != NULL)
        free(str);
}

int do_prog(char *line, struct linked_list *env, int *oldpwd)
{
    int my_prog = check_prog_or_comm(line);

    if (my_prog == 3)
        return 84;
    if (my_prog == 2)
        do_env(env);
    if (my_prog == 4)
        do_setenv(line, env, 0);
    if (my_prog == 5)
        do_unsetenv(line, env);
    if (my_prog == 1)
        if (do_cd(line, env, oldpwd) == 0)
            oldpwd[0] = 1;
    return 0;
}
