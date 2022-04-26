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

int do_env(struct linked_list *env)
{
    struct linked_list *env_cpy = env;

    while (env_cpy != NULL) {
        my_putstr(env_cpy->name);
        my_putstr("=");
        if (env_cpy->equal != NULL)
            my_putstr(env_cpy->equal);
        my_putstr("\n");
        env_cpy = env_cpy->next;
    }
    return 0;
}

void delete_env_var(struct linked_list *env, struct linked_list *env_cpy)
{
    free(env_cpy->name);
    if (env_cpy->equal != NULL)
        free(env_cpy->equal);
    delete_list(env, env_cpy);
}

char **get_var_unset(char *line)
{
    char **var = NULL;
    int nb_space = count_nb_char(line, ' ');
    int j = 1;
    int i = 0;

    if (nb_space == 0)
        return put_error_null("unsetenv: Too few arguments.\n");
    var = malloc(sizeof(char *) * (nb_space + 1));
    for (; i != nb_space; i++) {
        while (line[j - 1] != ' ' && line[j] != '\0')
            j++;
        var[i] = my_strdup_char(line + j, ' ');
        if (var[i] == NULL)
            return put_error_null("malloc error get_var_val_env 1\n");
        j++;
    }
    var[i] = NULL;
    return var;
}

int loop_unsetenv(char *var_env, struct linked_list *env)
{
    struct linked_list *env_cpy = env;

    while (env_cpy != NULL) {
        if (compare_str(var_env, env_cpy->name) == 0) {
            delete_env_var(env, env_cpy);
            return 0;
        }
        env_cpy = env_cpy->next;
    }
    return 0;
}

int do_unsetenv(char *line, struct linked_list *env)
{
    char **var_env = get_var_unset(line);

    if (var_env == NULL)
        return 84;
    for (int i = 0; var_env[i] != NULL; i++)
        loop_unsetenv(var_env[i], env);
    free_array_char(var_env);
    return 0;
}
