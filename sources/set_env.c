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

char *get_var(char *line)
{
    char *var = NULL;
    int nb_space = count_nb_char(line, ' ');
    int i = 1;

    if (nb_space != 1 && nb_space != 2)
        return put_error_null("setenv: Too many arguments.\n");
    while (line[i - 1] != ' ')
        i++;
    var = my_strdup_char(line + i, ' ');
    if (var == NULL)
        return put_error_null("malloc error get_var_val_env 1\n");
    return var;
}

char *get_val(char *line)
{
    char *val = NULL;
    int nb_space = count_nb_char(line, ' ');
    int i = 1;

    while (line[i - 1] != ' ')
        i++;
    if (nb_space == 1)
        return NULL;
    i++;
    while (line[i - 1] != ' ')
        i++;
    val = my_strdup_char(line + i, ' ');
    return val;
}

int put_val_env(struct linked_list *env_cpy, char *val_env)
{
    if (env_cpy->equal == NULL) {
        env_cpy->equal = val_env;
        return 0;
    }
    free(env_cpy->equal);
    env_cpy->equal = val_env;
    return 0;
}

int add_new_env(char *var_env, char *val_env, int i, struct linked_list *env)
{
    struct linked_list *new = NULL;

    new = malloc(sizeof(struct linked_list));
    if (new == NULL)
        return put_error_int("malloc error get_var_val_env 3\n");
    new->name = var_env;
    new->equal = val_env;
    env = add_list(env, new, i);
    return 0;
}

int do_setenv(char *line, struct linked_list *env, int i)
{
    struct linked_list *env_cpy = env;
    char *var_env = NULL;
    char *val_env = NULL;

    if (compare_str(line, "setenv") == 0) {
        do_env(env);
        return 0;
    }
    var_env = get_var(line);
    if (var_env == NULL)
        return 84;
    val_env = get_val(line);
    for (; env_cpy != NULL; i++) {
        if (compare_str(env_cpy->name, val_env) == 0) {
            free(var_env);
            return put_val_env(env_cpy, val_env);
        }
        env_cpy = env_cpy->next;
    }
    return add_new_env(var_env, val_env, i, env);
}
