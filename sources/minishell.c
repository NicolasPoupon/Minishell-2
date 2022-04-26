/*
** EPITECH PROJECT, 2021
** minishell.c
** File description:
** minishell1
*/

#include "my.h"
#include "p.h"
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int check_prog_or_comm(char *line)
{
    if (compare_n_str(line, "cd ", 3) == 0 ||
        compare_str(line, "cd") == 0)
        return 1;
    if (compare_n_str(line, "env ", 4) == 0)
        return 2;
    if (compare_n_str(line, "exit ", 5) == 0 ||
        compare_str(line, "exit") == 0)
        return 3;
    if (compare_n_str(line, "setenv ", 7) == 0 ||
        compare_str(line, "setenv") == 0)
        return 4;
    if (compare_n_str(line, "unsetenv ", 9) == 0 ||
        compare_str(line, "unsetenv") == 0)
        return 5;
    return 0;
}

char **clear_line_minishell(char *line)
{
    char *buff = NULL;
    char *line_clear = NULL;

    buff = my_strdup(line);
    if (buff == NULL)
        return put_error_null("malloc err\n");
    if (my_strlen(buff) != 0)
        buff[my_strlen(buff) - 1] = '\0';
    line_clear = clear_space(buff);
    if (line_clear == NULL)
        return put_error_null("malloc err\n");
    free(buff);
    return line_clear_in_array(line_clear, 0, 0);
}

int loop_prog_comm(char *line_clear, struct linked_list *env, int *oldpwd)
{
    int err = 0;

    if (line_clear[0] == '\0')
        return 0;
    if (check_prog_or_comm(line_clear) == 0)
        err = do_comm(line_clear, env);
    else
        err = do_prog(line_clear, env, oldpwd);
    return err;
}

int my_minishell(struct linked_list *env, int err)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;
    int oldpwd = 0;
    char **line_clear = NULL;

    while ((read = getline(&line, &len, stdin)) != -1) {
        if (read == - 1)
            return put_error_int("read error my_minishell\n");
        line_clear = clear_line_minishell(line);
        if (line_clear == NULL)
            return put_error_int("error line_clear my_minishell\n");
        for (int i = 0; line_clear[i] != NULL; i++)
            err = loop_prog_comm(line_clear[i], env, &oldpwd);
        if (err == 84)
            return 84;
        free_array_char(line_clear);
        my_putstr("$> ");
    }
    return (0);
}

int minishell(int ac, char **av, char **env)
{
    struct linked_list *envi = create_linked_env(env);
    struct linked_list *new = envi;
    char **line_clear = NULL;

    if (envi == NULL)
        return put_error_int("malloc error linked env minishell\n");
    my_putstr("$> ");
    my_minishell(envi, 0);
    free_linked_list(envi);
}
