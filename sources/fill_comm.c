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

char *clear_line_after(char *line, char clear, char not_clear)
{
    char *buff = my_strdup(line);
    char *res = NULL;
    int i = 0;

    if (buff == NULL)
        return NULL;
    while (buff[i] != clear)
        i++;
    while (buff[i] == clear || buff[i] == ' ') {
        buff[i] = ' ';
        i++;
    }
    while (buff[i] != ' ' && buff[i] != not_clear && buff[i] != '\0') {
        buff[i] = ' ';
        i++;
    }
    res = clear_space(buff);
    free(buff);
    free(line);
    return res;
}

struct comm *help_fill_comm(char *line, struct comm *comm, char *line_put)
{
    if (comm->nb_input != 0) {
        if ((line_put = clear_line_after(line_put, '<', '>')) == NULL)
            return put_error_null("clear_line_after error\n");
        comm->name_file_input = fill_name_input(line, '<', '>');
        if (comm->name_file_input == NULL)
            return put_error_null("malloc error fill_comm 3\n");
    }
    if (comm->nb_output != 0) {
        if ((line_put = clear_line_after(line_put, '>', '<')) == NULL)
            return put_error_null("clear_line_after error\n");
        comm->name_file_output = fill_name_input(line, '>', '<');
        if (comm->name_file_output == NULL)
            return put_error_null("malloc error fill_comm 4\n");
    }
    comm->arg = str_to_word_array(comm->arg, line_put, my_strlen(line_put));
    if (comm->arg == NULL)
        put_error_null("malloc error fill_comm 5\n");
    comm->arg = clear_last_space(comm->arg);
    free(line_put);
    return comm;
}

void destroy_comm(struct comm *comm)
{
    free_array_char(comm->env);
    free(comm->name);
    free(comm->path_comm);
    if (comm->nb_input != 0)
        free(comm->name_file_input);
    if (comm->nb_output != 0)
        free(comm->name_file_output);
    free(comm);
}

void print_comm(struct comm *comm)
{
    my_putstr("\nname :");
    my_putstr_e(comm->name);
    my_putstr("arguments :");
    print_array_char_e(comm->arg);
    my_putstr("\npath comm :");
    my_putstr_e(comm->path_comm);
    my_putstr("\nname input :");
    if (comm->nb_input != 0)
        my_putstr(comm->name_file_input);
    my_putstr("\nnb input :");
    my_put_nbr(comm->nb_input);
    my_putstr("\nname output :");
    if (comm->nb_output != 0)
        my_putstr(comm->name_file_output);
    my_putstr("\nnb output :");
    my_put_nbr(comm->nb_output);
    my_putstr("\n\n");
}

struct comm *fill_comm(char *line, struct linked_list *env)
{
    struct comm *comm = malloc(sizeof(struct comm));
    char *path = fill_path(env);
    char *line_no_put = my_strdup(line);

    if (comm == NULL || path == NULL || line_no_put == NULL)
        return put_error_null("malloc error fill_comm 1\n");
    comm->env = linked_list_to_array(env);
    comm->name = my_strdup_three_charn(line, ' ', '>', '<');
    if (comm->env == NULL || comm->name == NULL)
        return put_error_null("malloc error fill_comm 2\n");
    comm->path_comm = find_where_is_comm(path, line, comm->name);
    if (comm->path_comm == NULL)
        return NULL;
    comm->nb_input = check_redi(line, '<');
    comm->nb_output = check_redi(line, '>');
    if (comm->nb_input == -1 || comm->nb_output == -1)
        return put_error_null("Ambiguous intput / outpout redirect\n");
    return help_fill_comm(line, comm, line_no_put);
}
