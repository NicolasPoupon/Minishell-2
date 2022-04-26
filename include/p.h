/*
** EPITECH PROJECT, 2021
** p.h
** File description:
** project .h
*/

#ifndef _P_H
    #define _P_H

struct linked_list {
    char *name;
    char *equal;
    struct linked_list *next;
};

struct comm {
    char **env;
    char *name;
    char *path_comm;
    char **arg;
    int nb_input;
    int nb_output;
    char *name_file_input;
    char *name_file_output;
};

// minishell 1
int minishell(int ac, char **av, char **env);
int check_prog_or_comm(char *line);

// do prog
int do_prog(char *line, struct linked_list *env, int *oldpwd);
int do_env(struct linked_list *env);
void if_free(char *str);
int chdir_error(char *pathname);

// do comm
int do_comm(char *line, struct linked_list *env);
void exec_comm(struct comm *comm);
char *fill_path(struct linked_list *env);

// find_where_is_comm
char *find_where_is_comm(char *path, char *line, char *name_comm);

// create_linked_list
struct linked_list *create_linked_env(char **env);

// set_env
int do_setenv(char *line, struct linked_list *env, int i);
char *get_var(char *line);

// unset_env
int do_unsetenv(char *line, struct linked_list *env);
int do_env(struct linked_list *env);

// do_cd
int do_cd(char *line, struct linked_list *env, int *oldpwd);

// linked_list_to_array
char **linked_list_to_array(struct linked_list *env);

// line_clear_in_array
char **line_clear_in_array(char *line, int j, int i);

// fill_comm_help
char *fill_name_input(char *line, char put, char stop);
int check_redi(char *line, char redi);
char **clear_last_space(char **array);
char *my_strdup_three_charn(char const *src, char sa, char sb, char sc);

// fill_comm
struct comm *fill_comm(char *line, struct linked_list *env);
void destroy_comm(struct comm *comm);
void print_comm(struct comm *comm);

// change_std
void exec_change_put(struct comm *comm);

// do_pipe
int do_pipe(char *line, struct linked_list *env, int nb_pipe);

#endif
