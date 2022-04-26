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

void cd_home_help(struct linked_list *env_old_path,
struct linked_list *env_path, char *old_path)
{
    if_free(env_old_path->equal);
    env_old_path->equal = old_path;
    if_free(env_path->equal);
    env_path->equal = getcwd(NULL, 0);
}

int cd_home(struct linked_list *env)
{
    struct linked_list *env_home = env;
    struct linked_list *env_path = env;
    struct linked_list *env_old_path = env;
    char *old_path = getcwd(NULL, 0);

    if (old_path == NULL)
        return put_error_int("cd_home error getcwd\n");
    if ((env_home = get_list(env_home, "HOME")) == NULL)
        return put_error_int("cd_home error HOME not found\n");
    if (chdir(env_home->equal) == - 1)
        return chdir_error(my_strdup(env_home->equal));
    if ((env_path = get_list(env_path, "PWD")) == NULL)
        return put_error_int("cd_home error PWD not found\n");
    if ((env_old_path = get_list(env_old_path, "OLDPWD")) == NULL)
        return put_error_int("cd_home error OLDPWD not found\n");
    cd_home_help(env_old_path, env_path, old_path);
    if (env_path->equal == NULL)
        return put_error_int("cd_home error getcwd 2\n");
    return 0;
}

int cd_minus(struct linked_list *env)
{
    struct linked_list *env_path = env;
    struct linked_list *env_old_path = env;
    char *old_path = getcwd(NULL, 0);

    if (old_path == NULL)
        return put_error_int("cd_minus error getcwd\n");
    if ((env_old_path = get_list(env_old_path, "OLDPWD")) == NULL)
        return put_error_int("cd_minus error OLDPWD not found\n");
    if ((env_path = get_list(env_path, "PWD")) == NULL)
        return put_error_int("cd_minus error PWD not found\n");
    if (chdir(env_old_path->equal) == - 1)
        return chdir_error(my_strdup(env_old_path->equal));
    if_free(env_old_path->equal);
    env_old_path->equal = old_path;
    if_free(env_path->equal);
    env_path->equal = getcwd(NULL, 0);
    if (env_path->equal == NULL)
        return put_error_int("cd_minus error getcwd 2\n");
    return 0;
}

int cd_normal(char *pathname, struct linked_list *env)
{
    struct linked_list *env_path = env;
    struct linked_list *env_old_path = env;
    char *old_path = getcwd(NULL, 0);

    if (old_path == NULL)
        return put_error_int("cd_normal error getcwd\n");
    if (chdir(pathname) == - 1)
        return chdir_error(pathname);
    free(pathname);
    if ((env_old_path = get_list(env_old_path, "OLDPWD")) == NULL)
        return put_error_int("cd_normal error OLDPWD not found\n");
    if_free(env_old_path->equal);
    env_old_path->equal = old_path;
    if ((env_path = get_list(env_path, "PWD")) == NULL)
        return put_error_int("cd_normal error PWD not found\n");
    if_free(env_path->equal);
    env_path->equal = getcwd(NULL, 0);
    if (env_path->equal == NULL)
        return put_error_int("cd_normal error getcwd 2\n");
    return 0;
}

int do_cd(char *line, struct linked_list *env, int *oldpwd)
{
    char *pathname;
    int i = 0;

    if (count_nb_char(line, ' ') > 1)
        return put_error_int("cd: Too many arguments.\n");
    if (count_nb_char(line, ' ') == 0 || compare_str(line, "cd ~") == 0)
        return cd_home(env);
    if (compare_str(line, "cd -") == 0)
        return cd_minus(env);
    while (line[i - 1] != ' ')
        i++;
    pathname = my_strdup(line + i);
    if (pathname == NULL)
        return put_error_int("malloc error do_cd 1\n");
    return cd_normal(pathname, env);
}
