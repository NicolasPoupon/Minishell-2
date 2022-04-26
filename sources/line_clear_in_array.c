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

static int free_buff_and_act_j(char *buff, char *line, int j)
{
    free(buff);
    if (line[j] != '\0')
        j++;
    while (line[j - 1] != ';' && line[j] != '\0')
        j++;
    return j;
}

char **line_clear_in_array(char *line, int j, int i)
{
    int nb_comm = count_nb_char(line, ';') + 1;
    char **array = malloc(sizeof(char *) * (nb_comm + 1));
    char *buff;

    if (array == NULL)
        return put_error_null("malloc error line_clear_in_array\n");
    for (; i < nb_comm; i++) {
        buff = my_strdup_char(line + j, ';');
        if (buff == NULL)
            return put_error_null("malloc error line_clear_in_array 1\n");
        if (buff[0] == '\0')
            array[i] = my_strdup("");
        else
            array[i] = clear_space(buff);
        if (array[i] == NULL)
            return put_error_null("malloc error line_clear_in_array 2\n");
        j = free_buff_and_act_j(buff, line, j);
    }
    array[i] = NULL;
    return array;
}
