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

int exec_pipe(char *line, struct linked_list *env, struct comm *comm,
struct comm *comm_n)
{
    int pip[2];
    int pid = 0;

    if (pipe(pip) == -1)
        return put_error_int("pipe failed 1\n");
    if ((pid = fork()) < 0)
        return put_error_int("fork failed 1\n");
    if (pid == 0) {
        close(pip[1]);
        dup2(pip[0], 0);
        close(pip[0]);
        execve(comm_n->path_comm, comm_n->arg, comm_n->env);
    } else {
        close(pip[0]);
        dup2(pip[1], 1);
        close(pip[1]);
        execve(comm->path_comm, comm->arg, comm->env);
    }
    return 0;
}

struct comm *fill_comm_after_pipe(char *line, int nb, struct linked_list *env)
{
    int j = 1;
    char *buff = NULL;
    char *curr_pipe = NULL;
    struct comm *res = NULL;

    for (int i = 0; i < nb; j++) {
        if (line[j] == '\0')
            return put_error_null("no more pipe\n");
        if (line[j - 1] == '|')
            i++;
    }
    buff = my_strdup_char(line + j, '|');
    if (buff == NULL)
        return put_error_null("malloc error fill_comm_after_pipe 1\n");
    curr_pipe = clear_space(buff);
    free(buff);
    res = fill_comm(curr_pipe, env);
    free(curr_pipe);
    return res;
}

int call_pipe(char *line, struct linked_list *env, struct comm *comm,
struct comm *comm_n)
{
    int pid = 0;

    pid = fork();
    if (pid != 0)
        wait(&pid);
    else {
        if (exec_pipe(line, env, comm, comm_n) == 84)
            return 84;
    }
    destroy_comm(comm);
    destroy_comm(comm_n);
    return 0;
}

int do_pipe(char *line, struct linked_list *env, int nb_pipe)
{
    char *buff = my_strdup_char(line, '|');
    char *line_no_pipe = NULL;
    struct comm *comm;
    struct comm *comm_n = fill_comm_after_pipe(line, 1, env);

    if (buff == NULL || comm_n == NULL)
        return put_error_int("malloc error do_pipe\n");
    line_no_pipe = clear_space(buff);
    free(buff);
    if (line_no_pipe == NULL)
        return put_error_int("malloc error do_pipe 2\n");
    comm = fill_comm(line_no_pipe, env);
    free(line_no_pipe);
    if (comm == NULL)
        return 84;
    return call_pipe(line, env, comm, comm_n);
}
