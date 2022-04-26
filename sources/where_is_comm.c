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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int count_nb_folder(char *path)
{
    int res = 0;

    for (int i = 0; path[i] != '\0'; i++) {
        if (path[i] == '/')
            res++;
    }
    return res;
}

char *cpy_path_comm_in_res(char *res, char *path, char *comm, int i)
{
    int i_res = 0;

    res[i_res] = '/';
    i_res++;
    for (int k = i; path[k] != '/' && path[k] != '\0'; k++, i_res++)
        res[i_res] = path[k];
    res[i_res] = '/';
    i_res++;
    for (int l = 0; comm[l] != '\0'; l++, i_res++)
        res[i_res] = comm[l];
    res[i_res - 1] = '\0';
    return res;
}

char *file_loc_and_comm(char *path, char *comm, int num_folder)
{
    int i = 0;
    int nb_fold = -1;
    char *res;

    while (nb_fold != num_folder) {
        if (path[i] == '/')
            nb_fold++;
        i++;
    }
    res = malloc(sizeof(char) * (my_strlen(comm) + 1 + my_strlen(path)));
    if (res == NULL)
        return NULL;
    res = cpy_path_comm_in_res(res, path, comm, i);
    return res;
}

char *find_where_is_comm(char *path, char *line, char *name_comm)
{
    char *path_with_comm;
    int fd = -1;
    int nb_folder_to_check = count_nb_folder(path);

    for (int i = 0; nb_folder_to_check != 0; i++, nb_folder_to_check--) {
        path_with_comm = file_loc_and_comm(path, name_comm, i);
        if (path_with_comm == NULL)
            return NULL;
        fd = open(path_with_comm, O_RDONLY);
        if (fd >= 0)
            return path_with_comm;
    }
    for (int i = 0; line[i] != '\0' && line[i] != ' '; i++)
        write(2, &line[i], 1);
    put_error_null(": Command not found.\n");
    return NULL;
}
