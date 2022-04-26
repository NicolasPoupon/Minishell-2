/*
** EPITECH PROJECT, 2021
** do_comm.c
** File description:
** do comm for minishell
*/

#include "../include/my.h"
#include "../include/p.h"
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static int len_data_list(struct linked_list *env)
{
    int len = 2 + my_strlen(env->name);

    if (env->equal == NULL)
        return len;
    return (len + my_strlen(env->equal));
}

static void cpy_in_array(char *str, char *name, char *equal, char c)
{
    int i = 0;

    while (name[i] != '\0') {
        str[i] = name[i];
        i++;
    }
    str[i] = c;
    i++;
    if (equal == NULL)
        str[i] = '\0';
    else {
        for (int j = 0; equal[j] != '\0'; j++, i++)
            str[i] = equal[j];
    }
    str[i] = '\0';
}

char **linked_list_to_array(struct linked_list *env)
{
    struct linked_list *env_cpy = env;
    char **array;
    int size = len_linked_list(env);
    int i = 0;

    array = malloc(sizeof(char *) * (size + 1));
    if (array == NULL)
        return put_error_null("malloc error linked_list_to_array 1\n");
    for (; env_cpy != NULL; i++) {
        array[i] = malloc(sizeof(char) * (len_data_list(env_cpy) + 1));
        if (array[i] == NULL)
            return put_error_null("malloc error linked_list_to_array 2\n");
        cpy_in_array(array[i], env_cpy->name, env_cpy->equal, '=');
        env_cpy = env_cpy->next;
    }
    array[i] = NULL;
    return array;
}
