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

static int change_stdout(struct comm *comm, int *buff_stdout, int *f)
{
    *buff_stdout = dup(1);

    if (*buff_stdout == -1)
        return put_error_int("dup error change stdout 1\n");
    if (comm->nb_output == 1)
        *f = open(comm->name_file_output, O_CREAT | O_WRONLY, 0664);
    else {
        *f = open(comm->name_file_output,
        O_CREAT | O_WRONLY | O_APPEND, 0664);
    }
    if (*f < 0)
        return put_error_int("open error change stdout 1\n");
    close(1);
    if (dup(*f) == -1)
        return put_error_int("dup error change stdout 2\n");
    return 0;
}

static int change_stdin(struct comm *comm, int *buff_stdin, int *fd)
{
    *buff_stdin = dup(0);

    if (*buff_stdin == -1)
        return put_error_int("dup error change stdin 1\n");
    if (comm->nb_input == 1)
        *fd = open(comm->name_file_input, O_RDONLY);
    else
        *fd = open(comm->name_file_input, O_RDONLY);
    if (*fd < 0)
        return put_error_int("open error change stdin 1\n");
    close(0);
    if (dup(*fd) == -1)
        return put_error_int("dup error change stdin 2\n");
    return 0;
}

void exec_change_put(struct comm *comm)
{
    int buff_stdout = 0;
    int buff_stdin = 0;
    int fd_input = 0;
    int fd_output = 0;

    if (comm->nb_output != 0)
        if (change_stdout(comm, &buff_stdout, &fd_output) == 84)
            return;
    if (comm->nb_input != 0)
        if (change_stdin(comm, &buff_stdin, &fd_output) == 84)
            return;
    exec_comm(comm);
    if (comm->nb_output != 0) {
        close(fd_output);
        dup2(buff_stdout, 1);
    }
    if (comm->nb_input != 0) {
        close(fd_input);
        dup2(buff_stdin, 0);
    }
}
