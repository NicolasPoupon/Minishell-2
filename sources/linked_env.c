/*
** EPITECH PROJECT, 2021
** linked env.c
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

char *my_strncpy_after_char(char *dest, char const *src, char c)
{
    int i = 0;
    int size = 0;
    int j = 0;

    while (src[i] != c)
        i++;
    i++;
    size = i;
    while (src[size] != '\0')
        size++;
    dest = malloc(sizeof(char) * (size + 1));
    while (src[i] != '\0') {
        dest[j] = src[i];
        j++;
        i++;
    }
    dest[j] = '\0';
    return (dest);
}

struct linked_list *create_linked_env(char **env)
{
    struct linked_list *list_env;
    struct linked_list *env_cpy;
    int size = 0;

    while (env[size] != NULL)
        size++;
    list_env = create_linked_list(size);
    env_cpy = list_env;
    for (int i = 0; env_cpy != NULL; i++) {
        env_cpy->name = my_strncpy_char(env_cpy->name, env[i], '=');
        env_cpy->equal = my_strncpy_after_char(env_cpy->equal, env[i], '=');
        env_cpy = env_cpy->next;
    }
    return list_env;
}
