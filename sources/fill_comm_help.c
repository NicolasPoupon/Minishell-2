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

char **clear_last_space(char **array)
{
    if (array[0] == NULL)
        return array;
    if (array[1] == NULL) {
        array[0][my_strlen(array[0]) + 1] = '\0';
        array[0][my_strlen(array[0])] = '\n';
        return array;
    }
    for (int i = 1; array[i + 1] != NULL; i++)
        array[i][my_strlen(array[i]) - 1] = '\0';
    return array;
}

char *fill_path(struct linked_list *env)
{
    struct linked_list *path = get_list(env, "PATH");

    if (path == NULL)
        return put_error_null("can't find PATH file_path\n");
    if (path->equal == NULL)
        return NULL;
    return my_strdup(path->equal);
}

int check_redi(char *line, char redi)
{
    int nb_redi = count_nb_char(line, redi);
    int i = 0;

    if (nb_redi == 0)
        return 0;
    if (nb_redi == 1)
        return 1;
    if (nb_redi > 2)
        return -1;
    if (nb_redi == 2) {
        while (line[i] != redi && line[i] != '\0')
            i++;
        if (line[i + 1] != redi)
            return -1;
    }
    return 2;
}

char *fill_name_input(char *line, char put, char stop)
{
    int i = 0;
    char *res = NULL;

    while (line[i] != put)
        i++;
    while (line[i] == put || line[i] == ' ') {
        if (line[i] == '\0')
            return NULL;
        i++;
    }
    res = my_strdup_three_char(line + i, ' ', stop, stop);
    if (res == NULL)
        return NULL;
    return res;
}

char *my_strdup_three_charn(char const *src, char sa, char sb, char sc)
{
    char *dest;
    int s = 0;
    int i = 0;

    while (src[s] != '\0' && src[s] != sa && src[s] != sb && src[s] != sc)
        s++;
    dest = malloc(sizeof(char) * (s + 2));
    if (dest == NULL)
        return NULL;
    while (src[i] != '\0' && src[i] != sa && src[i] != sb && src[i] != sc) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\n';
    dest[i + 1] = '\0';
    return (dest);
}
