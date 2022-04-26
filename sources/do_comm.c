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

char *file_path(struct linked_list *env)
{
    struct linked_list *env_cpy = env;
    char *res;

    while (env_cpy != NULL) {
        if (compare_str(env_cpy->name, "PATH") == 0) {
            res = my_strdup(env_cpy->equal);
        }
        env_cpy = env_cpy->next;
    }
    return res;
}

void exec_comm(struct comm *comm)
{
    int pid = fork();

    if (pid != 0)
        wait(&pid);
    else
        execve(comm->path_comm, comm->arg, comm->env);
}

int do_exec_last_comm(char *line, struct linked_list *env)
{
    struct comm *comm = fill_comm(line, env);

    if (comm == NULL)
        return 0;
    if (comm->nb_input != 0 && comm->name_file_input == NULL) {
        put_error_int("syntax error no file input after the redirection\n");
        return 0;
    }
    if (comm->nb_output != 0 && comm->name_file_output == NULL) {
        put_error_int("syntax error no file output after the redirection\n");
        return 0;
    }
    if (comm->nb_output != 0 || comm->nb_input != 0)
        exec_change_put(comm);
    else
        exec_comm(comm);
    destroy_comm(comm);
    return 0;
}

int do_comm(char *line, struct linked_list *env)
{
    if (count_nb_char(line, '|') != 0)
        do_pipe(line, env, 0);
    else
        do_exec_last_comm(line, env);
    return 0;
}
